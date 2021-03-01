# GDB 调试 Libevent



## 测试代码

``` c
// signal_test.c
#include <event2/event.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sig_cb(int fd, short events, void *arg) {
    printf("%s\n", __func__);
}

int main() {
    struct event_base *base = event_base_new();
    struct event *ev = evsignal_new(base, SIGINT, sig_cb, NULL);
    
    event_add(ev, NULL);
    printf("pid: %d\n", getpid());
    event_base_dispatch(base);

    return 0;
}
```



## 编译脚本

``` shell
source='signal_test.c'
target='test'
cc='gcc'

clear
rm $target

$cc $source -g -o $target -I /home/carl/github/libevent/include -L /home/carl/github/libevent/cmake-build-debug/lib -levent
```



## 遇到的问题

程序能够正常执行，但是使用 GDB 调试的时候无法单步进入 libevent 库的函数内部。

``` bash
(gdb) b main
Breakpoint 1 at 0x11c5: file signal_test.c, line 12.
(gdb) r
Starting program: /home/carl/code/test
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, main () at signal_test.c:12
12          struct event_base *base = event_base_new();
(gdb) s
13          struct event *ev = evsignal_new(base, SIGINT, sig_cb, NULL);
(gdb) s
15          event_add(ev, NULL);
(gdb) s
16          printf("pid: %d\n", getpid());
(gdb)
```



## 排查思路

无法调试动态库，考虑的第一个可能性就是编译的 libevent 动态库是否是 release 版本，没有带调试符号，重新编译了一般 debug 版本后问题没有解决，**而且 libevent  test 目录下自带的测试用例编译后可以用 GDB 进入 libevent 动态库**。

调试 libevent 自带的 bench.c 测试例子

``` bash
Reading symbols from bench...
(gdb) b main
Breakpoint 1 at 0x15e1: file /home/carl/github/libevent/test/bench.c, line 143.
(gdb) r
Starting program: /home/carl/github/libevent/cmake-build-debug/bin/bench
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, main (argc=1, argv=0x7fffffffdef8)
at /home/carl/github/libevent/test/bench.c:143
143     {
# ... ...
(gdb)
185             if (events == NULL || pipes == NULL) {
(gdb)
190             event_init();
(gdb) s
event_init () at /home/carl/github/libevent/event.c:507
507             struct event_base *base = event_base_new_with_config(NULL);
(gdb)
```

通过上面自己写的测试例子和 libevent 自带的测试例子的对比，现在可以排除掉如下可能性：

1. GDB 程序有问题
2. 系统有问题
3. libevent 动态库编译出现问题

那么问题就应该出在编译条件或者运行条件不一致这两个方向上。动态库的使用和编译测试程序每什么关系，所以先不考虑，那么先想一下运行条件会有哪里不一致。

首先考虑测试用例运行时使用的动态库到底是不是我们编译出来的，使用 `info sharedlibrary` 命令查看程序链接的动态库。

``` bash
# test 程序链接的动态库
(gdb) info sharedlibrary
From                To                  Syms Read   Shared Object Library
0x00007ffff7fd4100  0x00007ffff7ff2c04  Yes (*)     /lib64/ld-linux-x86-64.so.2
0x00007ffff7f45020  0x00007ffff7f7abef  Yes (*)     /usr/lib/libevent-2.1.so.7
0x00007ffff7d97670  0x00007ffff7ee233f  Yes (*)     /usr/lib/libc.so.6
0x00007ffff7d57b30  0x00007ffff7d66995  Yes (*)     /usr/lib/libpthread.so.0
(*): Shared library is missing debugging information.
```

``` bash
# bench 程序链接的动态库
(gdb) info sharedlibrary
From                To                  Syms Read   Shared Object Library
0x00007ffff7fd4100  0x00007ffff7ff2c04  Yes (*)     /lib64/ld-linux-x86-64.so.2
0x00007ffff7f1b020  0x00007ffff7f66117  Yes (*)     /usr/lib/libssl.so.1.1
0x00007ffff7ca3000  0x00007ffff7e3b780  Yes (*)     /usr/lib/libcrypto.so.1.1
0x00007ffff7c12b30  0x00007ffff7c21995  Yes (*)     /usr/lib/libpthread.so.0
0x00007ffff7bf4020  0x00007ffff7c01270  Yes (*)     /usr/lib/libz.so.1
0x00007ffff7bcbcb0  0x00007ffff7be64eb  Yes         /home/carl/github/libevent/cmake-build-debug/lib/libevent_extra-2.1.so.7
0x00007ffff7b8be70  0x00007ffff7bb4853  Yes         /home/carl/github/libevent/cmake-build-debug/lib/libevent_core-2.1.so.7
0x00007ffff79df670  0x00007ffff7b2a33f  Yes (*)     /usr/lib/libc.so.6
0x00007ffff79b6210  0x00007ffff79b6fe9  Yes (*)     /usr/lib/libdl.so.2
(*): Shared library is missing debugging information.
```

可以发现，test 程序使用的 libevent 动态库的位置是 `/usr/lib/libevent-2.1.so.7` ，确实不是自己编译的 libevent 的动态库，所以问题就应该是出在这里。那么编译时使用的 `-L /home/carl/github/libevent/cmake-build-debug/lib` 参数是没有用吗？查一下 `-L` 参数的含义：

> -Ldir
>
> 制定编译的时候，搜索库的路径。比如你自己的库，可以用它制定目录，不然编译器将只在标准库的目录找。这个 dir 就是目录的名称。

所以是我理解错了，之前以为  -L 也可以指定程序运行时链接的动态库的位置。



## 解决问题

那么如何指定程序运行时链接的动态库的位置呢？

在使用 GDB 调试时，使用如下命令可以设定动态库的搜索路径

``` bash
# 使用 set 命令设置环境变量 LD_LIBRARY_PATH
(gdb) set env LD_LIBRARY_PATH /home/carl/github/libevent/cmake-build-debug/lib
(gdb) b main
Breakpoint 1 at 0x11c5: file signal_test.c, line 12.
(gdb) r
Starting program: /home/carl/code/test
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, main () at signal_test.c:12
12          struct event_base *base = event_base_new();
(gdb) s
event_base_new () at /home/carl/github/libevent/event.c:522
522             struct event_base *base = NULL;
(gdb)
```

如果要在编译期指定动态库搜索路径，可以增加 gcc 参数:

``` bash
-Wl,-rpath='/home/carl/github/libevent/cmake-build-debug/lib'
```

如果要在程序编译后，运行前指定搜索路径（这个方法只是临时修改，适用于测试程序）：

``` bash
export LD_LIBRARY_PATH=/home/carl/github/libevent/cmake-build-debug/lib
```

在编译期指定动态库搜索路径后，如何查看编译好的程序的 rpath 信息呢？

方法 1： 使用 readelf

``` bash
[carl@carl-pc code]$ readelf -d test

Dynamic section at offset 0x2dd8 contains 28 entries:
标记        类型                         名称/值
0x0000000000000001 (NEEDED)             共享库：[libevent-2.1.so.7]
0x0000000000000001 (NEEDED)             共享库：[libc.so.6]
0x000000000000000f (RPATH)              Library rpath: [/home/carl/github/libevent/cmake-build-debug/lib]
0x000000000000000c (INIT)               0x1000
# ... ...
```

方法 2：使用 objdump

``` bash
[carl@carl-pc code]$ objdump -x test | grep event
NEEDED               libevent-2.1.so.7
RPATH                /home/carl/github/libevent/cmake-build-debug/lib
0000000000000000       F *UND*  0000000000000000              event_base_new
0000000000000000       F *UND*  0000000000000000              event_new
0000000000000000       F *UND*  0000000000000000              event_add
0000000000000000       F *UND*  0000000000000000              event_base_dispatch
```



## 总结

出现错误的原因是对 GCC， GDB，Linux 环境变量不熟悉。



## 参考

[GCC 编译时指定动态库搜索路径](https://blog.csdn.net/qiuxin315/article/details/81771630)

[Linux 下获取 binary 中的 rpath 信息](https://blog.csdn.net/yasi_xi/article/details/45242113)

[Linux 运行时动态库搜索路径优先级](https://blog.csdn.net/value_he/article/details/84403828)

[gdb 显示共享链接库信息](https://wizardforcel.gitbooks.io/100-gdb-tips/info_sharedlibrary.html)