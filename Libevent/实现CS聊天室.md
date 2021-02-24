# 实现 CS 模式聊天室

## 介绍

这个项目是在学习 libevent 过程中用来联系的，所以实现的比较粗糙。程序是由 [基于 epoll 机制的高并发聊天室](https://github.com/jwzh222/epoll) 这个项目修改而来。原项目中包含一个辅助头文件，一个客户端程序，一个服务端程序。我将服务端程序做了一点修改，原程序中直接使用了 epoll 相关的函数，我使用 libevent 做了替换。客户端程序也作了一点点修改，不过没有修改程序结构。

## 辅助头文件

这个是直接复制过来的，没有做修改。里面的 `sendBroadcastmessage()` 函数比较重要。服务端程序中用一个链表保存各个客户端，这个程序的作用就是当一个客户端发送消息后，遍历链表，将这个消息转发给其他客户端。

```c++
// utility.h

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std; 

// clients_list save all the clients's socket
list<int> clients_list; 

/**********************   macro defintion **************************/
// server ip
#define SERVER_IP "127.0.0.1"

// server port
#define SERVER_PORT 8888

//epoll size
#define EPOLL_SIZE 5000

//message buffer size
#define BUF_SIZE 0xFFFF

#define SERVER_WELCOME "Welcome you join  to the chat room! Your chat ID is: Client #%d"

#define SERVER_MESSAGE "ClientID %d say >> %s"

// exit
#define EXIT "EXIT"

#define CAUTION "There is only one int the char room!"

/**********************   some function **************************/
/**

  + @param sockfd: socket descriptor
  + @return 0

**/
int setnonblocking(int sockfd)
{
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)| O_NONBLOCK);
    return 0;
}

/**

  + @param epollfd: epoll handle
  + @param fd: socket descriptor
  + @param enable_et : enable_et = true, epoll use ET; otherwise LT

**/
void addfd( int epollfd, int fd, bool enable_et )
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    setnonblocking(fd);
    printf("fd added to epoll!\n\n");
}

/**

  + @param clientfd: socket descriptor
  + @return : len

**/
int sendBroadcastmessage(int clientfd)
{
    // buf[BUF_SIZE] receive new chat message
    // message[BUF_SIZE] save format message
    char buf[BUF_SIZE], message[BUF_SIZE];
    bzero(buf, BUF_SIZE);
    bzero(message, BUF_SIZE);

    // receive message
    printf("read from client(clientID = %d)\n", clientfd);
    int len = recv(clientfd, buf, BUF_SIZE, 0);

    if(len == 0)  // len = 0 means the client closed connection
    {
        close(clientfd);
        clients_list.remove(clientfd); //server remove the client
        printf("ClientID = %d closed.\n now there are %d client in the char room\n", clientfd, (int)clients_list.size());

    }
    else  //broadcast message
    {
        if(clients_list.size() == 1) { // this means There is only one int the char room
            send(clientfd, CAUTION, strlen(CAUTION), 0);
            return len;
        }
        // format message to broadcast
        sprintf(message, SERVER_MESSAGE, clientfd, buf);

        list<int>::iterator it;
        for(it = clients_list.begin(); it != clients_list.end(); ++it) {
           if(*it != clientfd){
                if( send(*it, message, BUF_SIZE, 0) < 0 ) { perror("error"); exit(-1);}
           }
        }
    }
    return len;

}
#endif // UTILITY_H_INCLUDED
```

## 服务端代码

```c++
// server.cpp

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <event.h>
#include "utility.h"

// 创建全局的 event_base
struct event_base *base = event_base_new();

// 处理客户端发送来的信息的回调函数
void message_cb(evutil_socket_t fd, short what, void *arg)
{
    {
        // 将消息发送到客户端链表上所有其他的客户端
        int ret = sendBroadcastmessage(fd);
        if (ret < 0) 
        {
            perror("message_cb error\n");
            exit(-1);
        }
    }
}

// 服务端调用此回调函数 accept 客户端请求
void accept_cb(evutil_socket_t fd, short event, void *arg) 
{
    struct sockaddr_in remote_addr;
    int sin_size = sizeof(struct sockaddr_in);
    int new_fd = accept(fd, (struct sockaddr*)&remote_addr, (socklen_t*)&sin_size);

    if (new_fd < 0)
    {
        printf("accept error\n");
        return;
    }
    
    // 设置关注客户端读事件的 event
    struct event* read_ev = (struct event*)malloc(sizeof(struct event));
    event_set(read_ev, new_fd, EV_READ|EV_PERSIST, message_cb, NULL);
    event_base_set(base, read_ev);
    event_add(read_ev, NULL);

    // 服务端用list保存用户连接
    clients_list.push_back(new_fd);
    printf("Add new clientfd = %d to epoll\n", new_fd);
    printf("Now there are %d clients int the chat room\n", (int)clients_list.size());
}

int main(int argc, char *argv[])
{
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    int listener = socket(PF_INET, SOCK_STREAM, 0);
    if (listener < 0) 
    {
        perror("create socket error\n");
        exit(-1);
    }

    // 设置监听端口的 SO_REUSEADDR 属性，主要是为了减去测试时 TIMEOUT 的影响
    int optval = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));

    if (bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("bind error\n");
        exit(-1);
    }

    int ret = listen(listener, 5);
    if (ret < 0) 
    {
        perror("listen error\n");
        exit(-1);
    }

    // 设置关注监听端口读事件的 event
    struct event listener_ev;
    event_set(&listener_ev, listener, EV_READ|EV_PERSIST, accept_cb, NULL);
    event_base_set(base, &listener_ev);
    event_add(&listener_ev, NULL);
    event_base_dispatch(base);
    
    return 0;
}
```

由于是在 Linux 下测试的，所以上面代码中会默认使用 epoll 作为 event_base 的后端。当然了，可以使用如下如下代码来控制 event_base 的行为来禁用某些后端方法以达到测试其他后端方法的目的。

```c++

    struct event_config *cfg = event_config_new();
    // 需要禁用的后端方法
    const char* disable_epoll = "epoll";
    // 后端禁用 epoll
    event_config_avoid_method(cfg, disable_epoll);
    base = event_base_new_with_config(cfg);
    // 检查一下后端使用的方法
    const char *used_method = event_base_get_method(base);
    printf("%s\n", used_method);

```

## 客户端代码

```c++
// client.cpp
#include "utility.h"

int main(int argc, char *argv[])
{
    //用户连接的服务器 IP + port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 创建socket
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0) { perror("sock error"); exit(-1); }
    // 连接服务端
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("connect error");
        exit(-1);
    }

    // 创建管道，其中fd[0]用于父进程读，fd[1]用于子进程写
    int pipe_fd[2];
    if(pipe(pipe_fd) < 0) { perror("pipe error"); exit(-1); }

    // 创建epoll
    int epfd = epoll_create(EPOLL_SIZE);
    if(epfd < 0) { perror("epfd error"); exit(-1); }
    static struct epoll_event events[2];
    //将sock和管道读端描述符都添加到内核事件表中
    addfd(epfd, sock, true);
    addfd(epfd, pipe_fd[0], true);
    // 表示客户端是否正常工作
    bool isClientwork = true;

    // 聊天信息缓冲区
    char message[BUF_SIZE];

    // Fork
    int pid = fork();
    if(pid < 0) { perror("fork error"); exit(-1); }
    else if(pid == 0)      // 子进程
    {
        //子进程负责写入管道，因此先关闭读端
        close(pipe_fd[0]);
        printf("Please input 'exit' to exit the chat room\n");

        while(isClientwork){
            bzero(&message, BUF_SIZE);
            fgets(message, BUF_SIZE, stdin);

            // 客户输出exit,退出
            if(strncasecmp(message, EXIT, strlen(EXIT)) == 0){
                isClientwork = 0;
            }
            // 子进程将信息写入管道
            else {
                if( write(pipe_fd[1], message, strlen(message) - 1 ) < 0 )
                 { perror("fork error"); exit(-1); }
            }
        }
    }
    else  //pid > 0 父进程
    {
        //父进程负责读管道数据，因此先关闭写端
        close(pipe_fd[1]);

        // 主循环(epoll_wait)
        while(isClientwork) {
            int epoll_events_count = epoll_wait( epfd, events, 2, -1 );
            //处理就绪事件
            for(int i = 0; i < epoll_events_count ; ++i)
            {
                bzero(&message, BUF_SIZE);

                //服务端发来消息
                if(events[i].data.fd == sock)
                {
                    //接受服务端消息
                    int ret = recv(sock, message, BUF_SIZE, 0);

                    // ret= 0 服务端关闭
                    if(ret == 0) {
                        printf("Server closed connection: %d\n", sock);
                        close(sock);
                        isClientwork = 0;
                    }
                    else printf("%s\n", message);

                }
                //子进程写入事件发生，父进程处理并发送服务端
                else {
                    //父进程从管道中读取数据
                    int ret = read(events[i].data.fd, message, BUF_SIZE);

                    // ret = 0
                    if(ret == 0) isClientwork = 0;
                    else{   // 将信息发送给服务端
                      send(sock, message, BUF_SIZE, 0);
                    }
                }
            }//for
        }//while
    }

    if(pid){
       //关闭父进程和sock
        close(pipe_fd[0]);
        close(sock);
    }else{
        //关闭子进程
        close(pipe_fd[1]);
    }
    return 0;
}
```

## 思考

我将客户端代码子进程部分的代码改了下，不再使用子进程去读取屏幕输入，而是直接给 message 字符数组赋值，造成子进程不停地给父进程发消息，但不知道为什么一旦开启超过一个客户端就会造成所有客户端和服务端卡死。

```c++
if (pid == 0)  // 子进程
{
    close(pipe_fd[0]);
    printf("Please input 'exit' to exit the chat room\n");

    while (client_work)
    {     
        bzero(message, BUF_SIZE);
        //fgets(message, BUF_SIZE, stdin);
        sprintf(message, "hello");

        if (strncasecmp(message, EXIT, strlen(EXIT)) == 0)
        {
            client_work = false;
        }
        else
        {   // 将信息写到管道
            if (write(pipe_fd[1], message, strlen(message)-1) < 0)
            {
                perror("write error\n");
                exit(-1);
            }   
        }
    }
}
```

## 参考

> [网络编程中的 SO_REUSEADDR 和 SO_REUSEPORT 参数详解](https://zhuanlan.zhihu.com/p/37278278)
> [使用 libevent 进行多线程 socket 编程 demo](https://www.cnblogs.com/james6176/p/4285018.html)
> [基于 epoll 机制的高并发聊天室](https://github.com/jwzh222/epoll)

