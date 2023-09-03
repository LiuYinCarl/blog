## IO 复用

应用程序通过 I/O 复用函数向内核注册一组事件，内核通过 I/O 复用函数把其中就绪的事件通知给应用程序。 Linux 常用的 I/O 复用函数是 `select` , `poll` , `epoll_wait` 。 I/O 复用函数本身是阻塞的，它们能提高程序效率的原因在于它们具有同时监听多个 I/O 事件的能力。

## SIGNO 型号

SIGNO 信号也能用来报告 I/O 事件。我们可以为一个目标文件描述符指定宿主进程，那么被指定的宿主进程将捕获到 SIGNO 信号。这样，当目标文件描述符上有事件发生时，SIGNO 信号的信号处理函数将被触发。

## Reactor 模式

同步 I/O 模型通常用来实现 Reactor 模式，异步 I/O 模型则用于实现 Proactor 模式，但是同步 I/O 方式也可以模拟出 Proactor 模式。

Reactor 模式要求主线程（I/O 处理单元）只负责监听文件描述符上是否有事件发生，如果有的话就立即将该事件通知工作线程（逻辑单元）。除此之外，主线程不做任何实质性的工作。读写数据、接受新的连接、以及处理客户请求均在工作线程中完成。

## Proactor 模式

Proactor 模式将所有 I/O 操作交给主线程和内核来处理，工作线程仅仅负责业务逻辑。

## 模拟 Proactor 模式

主线程执行数据读写操作，读写完成后，主线程向工作线程通知这一完成事件。那么从工作 i 线程的角度看，它们就直接获得了数据读写的结果

## select

```c++
#include <sys/socket.h>

int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout); 

```

用于操作 `fd_set` 结构体中的位的宏

```c++
#include <sys/select.h>

FD_ZERO(fd_set* fdset);
FD_SET(int fd, fd_set* fdset);
FD_CLR(int fd, fd_set* fdset);
int FD_ISSET(int fd, fd_set* fdset);
```

## poll

```c++
#include <poll.h>

int poll(struct pollfd* fds, nfds_t nfds, int timeout); 

struct pollfd {

    int fd;  		// 文件描述符
    short events;  	// 注册的事件
    short revents;  // 实际发生的事件，由内核填充

}; 

```

`fd` 指定文件描述符， `events` 告诉 poll 监听 `fd` 上的哪些事件，它是一系列事件的按位与。`revents` 则由内核修改，以通知应用程序 `fd` 上实际发生了哪些事件。

## epoll 

内核事件表

```c++
#include <sys/epoll.h>

int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);

struct epoll_event{
    __uint32_t events;  // epoll 事件
    epoll_data_t data;  // 用户数据
};
```

`epoll_create` 用来创建一个文件描述符来唯一标识内核内核中的内核事件表， `size` 参数目前并不起作用，只是给内核一个提示，告诉它事件表需要多大。

`eopll_ctl` 函数用来操作 `epoll` 的内核事件表

`fd` 是要操作的文件描述符， `op` 则指定操作类型。操作类型有如下 3 种

* EPOLL_CTL_ADD 往注册表上注册 `fd` 上的事件
* EPOLL_CTL_MOD 修改 `fd` 上的注册事件
* EPOLL_CTL_DEL 删除 `fd` 上的注册事件

```c++
#include <sys/epoll.h>

int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout); 
```

`epoll_wait` 在一段超时时间内等待一组文件描述符上的事件。该函数成功时返回就绪的文件描述符的个数，失败时返回 -1 并设置 `errno`

`epoll_wait` 函数如果检测到事件，就将所有就绪的事件从内核事件表(由 `epfd` 指定) 中复制到 `events` 指向的数组中。

**LT 和 ET 模式**

`epoll` 对文件描述符的操作有两种模式， LT（level trigger，电平触发）和 ET（edge trigger，边缘触发）LT 是默认的工作模式，这种模式下 `epoll` 相当于一个效率较高的 `poll` 。当往 `epoll` 内核事件表中注册一个文件描述符上的 EPOLLET 事件时， `epoll` 将以 ET 模式来操作该文件描述符，ET 模式是 `epoll` 的高效工作模式。

对于采用 LT 工作模式的文件描述符，当 `epoll_wait` 检测到其上有事件发生并将此事件通知应用程序后，应用程序可以不立即处理该事件。这样，当应用程序下一次调用 `epoll_wait` 时， `epoll_wait` 还会再次向应用程序通告此事件，直到该事件被处理。而对于采用了 ET 工作模式的文件描述符，当 `epoll_wait` 检测到其上有事件发生并将次事件通知应用程序后，应用程序必须立即处理该事件，因为后续的 `epoll_wait` 调用将不再向应用程序通知这一事件。可见， ET 模式在很大程度上降低了同一个 `epoll` 事件被重复触发的次数，因此，效率比 LT 模式高。
