# epoll 几个结构体的分析

epoll 涉及的几个函数和部分 man 手册解释

```c++
#include <sys/epoll.h>

int epoll_create(int size); 

```

> **epoll_create**() creates a new **epoll**(7) instance.  Since Linux 2.6.8, the size argument is ignored, but must be greater than zero; see NOTES below.
>        **epoll_create**() returns a file descriptor referring to the new epoll instance.  This file descriptor is used for all the subsequent calls to the **epoll** interface. When no longer required, the file descriptor returned by **epoll_create**() should be closed by using **close**(2).  When all file descriptors referring to an epoll instance have been closed, the kernel destroys the instance and releases the associated resources for reuse.
>
> On success, these system calls return a nonnegative file descriptor.  On error, -1 is returned, and errno is set to indicate the error.

```c++
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

> This  system  call is used to add, modify, or remove entries in the interest list of the **epoll**(7) instance referred to by the file descriptor epfd.  It requests that the operation op be performed for the target file descriptor, fd.
>
> Valid values for the op argument are:
> **EPOLL_CTL_ADD**
> 	Add fd to the interest list and associate the settings specified in event with the internal file linked to fd.
> **EPOLL_CTL_MOD**
> 	Change the settings associated with fd in the interest list to the new settings specified in event.
> **EPOLL_CTL_DEL**
> 	Remove (deregister) the target file descriptor fd from the interest list.  The event argument is ignored and can be NULL (but see BUGS below).
>
> When successful, **epoll_ctl**() returns zero.  When an error occurs, **epoll_ctl**() returns -1 and errno is set appropriately.

```c++
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout); 

```

> The  **epoll_wait**() system call waits for events on the **epoll**(7) instance referred to by the file descriptor epfd.  The memory area pointed to by events will contain the events that will be available for the caller.  Up to maxevents are returned by **epoll_wait**().  The maxevents argument must be greater than zero.
> The timeout argument specifies the number of milliseconds that **epoll_wait**() will block.  Time is measured against the  **CLOCK_MONOTONIC**  clock.   The  call  will block until either:
>
>    *  a file descriptor delivers an event;
>    *  the call is interrupted by a signal handler; or
>    *  the timeout expires.
>
> Note that the timeout interval will be rounded up to the system clock granularity, and kernel scheduling delays mean that the blocking interval may overrun by a small amount.  Specifying a timeout of -1 causes **epoll_wait**() to block indefinitely, while specifying a timeout equal to zero cause **epoll_wait**() to return immediately, even if no events are available.
>
> When  successful,  **epoll_wait**()  returns  the  number of file descriptors ready for the requested I/O, or zero if no file descriptor became ready during the requested timeout milliseconds.  When an error occurs, **epoll_wait**() returns -1 and errno is set appropriately.

看下这句：

>  **epoll_create**() returns a file descriptor referring to the new epoll instance.  

epoll_create() 返回的文件描述符的指向的是一个内核中的事件表 eventpoll，用文件表示。具体创建操作可以参考这篇文章的第一部分：

> [epoll--源码剖析](https://segmentfault.com/a/1190000014882854)

epoll_create() 的 size 参数为什么要大于 0, 在文章的代码中也一目了然。

接下来是 epoll_ctl():

> 在 epoll_ctl 中，主要分为以下几个步骤：
>
> - 判断需要操作的事件在事件表中是否存在
> - 判断需要进行的操作
> - 使用更底层的代码对事件表进行增删改
>
> epoll 比 poll 和 select 高效的地方，其实在这里就可以看出来，poll 的系统调用会把该进程“挂”到 fd 所对应的设备的等待队列上，select 和 poll 他们每一次都需要把 current "挂" 到 fd 对应设备的等待队列，同一个 fd 来说，你要不停监听的话，你就需要不停的进行 poll，那么 fd 太多的话，这样的 poll 操作其实是很低效的，epoll 则不同的是，每一个事件，它只在添加的时候调用 poll，以后都不用去调用 poll，避免了太多重复的 poll 操作，所以 epoll 对于 poll 和 select 来说是更高效的。[epoll--源码剖析](https://segmentfault.com/a/1190000014882854)

epoll_ctl() 参数中出现的 fd 和 event 分别指的是要操作的文件描述符和具体对该文件描述符的操作事件。event 的结构如下：

```c++
typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;

struct epoll_event {
    uint32_t     events;      /* Epoll events */
    epoll_data_t data;        /* User data variable */
};

```

接下来是 epoll_wait():

> 简单总结一下 epoll_wait：
>
> - 检查超时事件和用来存就绪事件的用户空间的大小
> - 循环等待就绪事件
> - 把就绪事件从内核空间 copy 到用户空间
>
> [epoll--源码剖析](https://segmentfault.com/a/1190000014882854)



再就是 ET 和 LT 实现的差异了

> 先说 LT 模式对于同一个就绪事件会重复提醒，从源码可以看出来是因为它又把依旧就绪且未设置 ET 标志的事件重新 copy 到了 rdllist 中，所以下一次 epoll_wait 还是会把该事件返回给用户。那么 ET 这里就很好解释了，尽管该事件未处理完，但是你只要设置了 ET 标志，我就不会再次把该事件返回给用户。这就是 ET 的实现。[epoll--源码剖析](https://segmentfault.com/a/1190000014882854)

[epoll--源码剖析](https://segmentfault.com/a/1190000014882854) 文章中有详细的源码分析。