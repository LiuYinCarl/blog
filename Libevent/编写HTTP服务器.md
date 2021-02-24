# 编写 HTTP 服务器

## 介绍

研究 HTTP 服务器的目的是因为在看 libevent-book 的时候，编译出的版本是 HTML 版本，不是 PDF 版本的，看起来比较麻烦，所以干脆想写个 HTTP 服务器，将程序和 libevent-book 文档放到服务器上去运行。之前写过一版 Go 语言的，不过最近正好在看 libevent，所以试试看做一版 C 语言的。

## libevent 安装脚本

服务器上没有装 libevent, 所以找了个安装脚本。

``` bash
wget https://github.com/libevent/libevent/releases/download/release-2.1.11-stable/libevent-2.1.11-stable.tar.gz
tar -zxvf libevent-2.1.11-stable.tar.gz
cd libevent-2.1.11-stable
./configure --prefix=/usr
make
make install
```

## 代码

``` c
// website.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for getopt, fork
#include <string.h> //for strcat
//for struct evkeyvalq
#include <sys/queue.h>
#include <event.h>
//for http
#include <evhttp.h>
#include <signal.h>

#include <fcntl.h>

#define MYHTTPD_SIGNATURE "myhttpd v 0.0.1"
#define BUFF_LEN 1024 * 1024

//处理模块
void httpd_handler(struct evhttp_request *req, void *arg)
{
    // char buffer[BUFF_LEN] = "\0";
    char *buffer = malloc(BUFF_LEN);
    buffer[0] = '\0';
    //输出的内容
    struct evbuffer *buf;
    buf = evbuffer_new();

    //获取客户端请求的URI(使用evhttp_request_uri或直接req->uri)
    const char *uri;
    uri = evhttp_request_uri(req);

    FILE *fp = fopen(uri+1, "r");
    if (fp == NULL)
    {
        return;
    }

    while(fgets(buffer, BUFF_LEN, fp) != NULL) {
        evbuffer_add_printf(buf, "%s\n", buffer);
    }
    
    if (fgets(buffer, BUFF_LEN, fp) != NULL)
    {
        int len = strlen(buffer);
        buffer[len - 1] = '\0';
    }

    /* 输出到客户端 */

    //HTTP header
    evhttp_add_header(req->output_headers, "Server", MYHTTPD_SIGNATURE);
    evhttp_add_header(req->output_headers, "Content-Type", "text/html; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Connection", "close");

    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}
void show_help()
{
    char *help = "written by Min (http://54min.com)\n\n"
                 "-l <ip_addr> interface to listen on, default is 0.0.0.0\n"
                 "-p <num>     port number to listen on, default is 1984\n"
                 "-d           run as a deamon\n"
                 "-t <second>  timeout for a http request, default is 120 seconds\n"
                 "-h           print this help and exit\n"
                 "\n";
    fprintf(stderr, help);
}
//当向进程发出SIGTERM/SIGHUP/SIGINT/SIGQUIT的时候，终止event的事件侦听循环
void signal_handler(int sig)
{
    switch (sig)
    {
    case SIGTERM:
    case SIGHUP:
    case SIGQUIT:
    case SIGINT:
        event_loopbreak(); //终止侦听event_dispatch()的事件侦听循环，执行之后的代码
        break;
    }
}

int main(int argc, char *argv[])
{
    //自定义信号处理函数
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    //默认参数
    char *httpd_option_listen = "127.0.0.1";
    int httpd_option_port = 8081;
    int httpd_option_daemon = 0;
    int httpd_option_timeout = 120; //in seconds

    //获取参数
    int c;
    while ((c = getopt(argc, argv, "l:p:dt:h")) != -1)
    {
        switch (c)
        {
        case 'l':
            httpd_option_listen = optarg;
            break;
        case 'p':
            httpd_option_port = atoi(optarg);
            break;
        case 'd':
            httpd_option_daemon = 1;
            break;
        case 't':
            httpd_option_timeout = atoi(optarg);
            break;
        case 'h':
        default:
            show_help();
            exit(EXIT_SUCCESS);
        }
    }

    //判断是否设置了-d，以daemon运行
    if (httpd_option_daemon)
    {
        pid_t pid;
        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid > 0)
        {
            //生成子进程成功，退出父进程
            exit(EXIT_SUCCESS);
        }
    }

    /* 使用libevent创建HTTP Server */
    //初始化event API
    event_init();

    //创建一个http server
    struct evhttp *httpd;
    httpd = evhttp_start(httpd_option_listen, httpd_option_port);
    evhttp_set_timeout(httpd, httpd_option_timeout);

    //指定generic callback
    evhttp_set_gencb(httpd, httpd_handler, NULL);

    //循环处理events
    event_dispatch();

    evhttp_free(httpd);
    return 0;
}
```

编译命令： `gcc -g -O0 website.c -o website -levent` 。 

主要是将网上的代码改了下，使得能够读取同目录下的 HTML 文件，当然，没有做什么错误处理。

[测试地址/libevent-book 阅读地址](http://47.93.196.173:7878/TOC.html)

## 参考

> [ubuntu 下安装 libevent](https://blog.csdn.net/qq_19004627/article/details/79919341)
> [使用 libevent 编写高并发 HTTP server](https://www.cnblogs.com/keepsimple/archive/2013/05/06/3063251.html)
