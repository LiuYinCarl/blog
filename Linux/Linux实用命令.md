## 查看动态库导出函数列表

**1、objdump**

``` bash
# 查看动态库有哪些符号，包括数据段、导出的函数和引用其他库的函数
objdump -tT xxx.so
objdump -x xxx.a

# 查看动态库依赖项
objdump -x xxx.so | grep "NEEDED" 

# 查看动态符号表
objdump -T xxx.so
## 假如想知道 xxx.so 中是否导出了符号 yyy ，那么命令为 objdump -T xxx.so | grep "yyy" 。

# 查看动态符号表
objdump -t xxx.so
## -T 和 -t 选项在于 -T 只能查看动态符号，如库导出的函数和引用其他库的函数，而 -t 可以查看所有的符号，包括数据段的符号。
```

**2、nm**

``` bash
# 查看静态库或动态库定义了哪些函数
nm -n --defined-only xxxx.a
nm -g -C --defined-only xxxx.so
nm -D xxxx.so

# 显示hello.a 中的未定义符号，需要和其他对象文件进行链接.
nm -u hello.o

# 在 ./ 目录下找出哪个库文件定义了close_socket函数. 
nm -A ./* 2>/dev/null | grep "T close_socket"
```

-D 或 -dynamic 选项表示：显示动态符号。该选项仅对于动态库有意义。

**3、readelf**

```bash
# 查看静态库定义的函数
readelf -c xxx.a

# 查看静态库定义的函数
readelf -A xxx.so 
```

## linux 查看磁盘负载

```bash
df -h
```

## 递归删除文件

```bash
find . -name "*.log" | xargs rm -f
```

## 查看目录下各文件夹的大小

```bash
du -h --max-depth=1
```

## awk 获取最后几列

```bash
# 方法1 将前几列置空
awk '{$1="";$2="";$3="";print $0}'  filename > newfile
# 方法2 只输入后几列
awk '{for(i=4;i<NF;i++)printf("%s ",$i);print $NF}'  filename >newfile
```

## Linux 多个静态库打包成一个静态库

[Linux 多个静态库打包成一个静态库](https://blog.csdn.net/listener51/article/details/104400299)

``` bash
# 将libabc.a libxyz.a 打包成libaz.a
ar -rcT libaz.a libabc.a libxyz.a
```

## GCC 解析符号名工具

``` bash
c++filt 符号名
```

## 端口查看

``` bash
# 查看端口的使用的情况

## lsof 命令 比如查看 80 端口的使用的情况。

lsof -i tcp: 80
# 列出所有的端口
netstat -ntlp
# 查看端口的状态
 /etc/init.d/iptables status
```

## gcore

给运行中的进程创建一个 core 文件。

[gcore manual](https://www.linux.org/docs/man1/gcore.html)

``` bash
NAME
       gcore - Generate a core file of a running program

SYNOPSIS
       gcore [-o filename] pid

DESCRIPTION
       Generate a core dump of a running program with process ID pid.  Produced file is equivalent to a kernel
       produced core file as if the process crashed (and if "ulimit -c" were used to set up an appropriate core dump
       limit).  Unlike after a crash, after gcore the program remains running without any change.

OPTIONS
       -o filename
           The optional argument filename specifies the file name where to put the core dump.  If not specified, the
           file name defaults to core.pid, where pid is the running program process ID.
```



## gstack

打印正在运行的进程的堆栈。可以用来查看进程死锁的位置。

[gstack manual](https://linux.die.net/man/1/gstack)

```bash
Name
	gstack - print a stack trace of a running process

Synopsis
	gstack pid

Description
	gstack attaches to the active process named by the pid on the command line, and prints out an execution stack trace. If ELF symbols exist in the binary (usually the case unless you have run strip(1)), then symbolic addresses are printed as well.

If the process is part of a thread group, then gstack will print out a stack trace for each of the threads in the group.
```

## 杀掉所有含有关键字的进程

```bash
ps -ef | grep 关键字 | awk '{print $3}' | xargs kill

# 示例 有时候 vscode 会卡死服务器,杀掉所有 vscode 相关进程
ps -ef | grep vscode | awk '{print $3}' | xargs kill
```


## jobs bg fg

当需要在一个终端处理多个任务的时候，可以使用这几个命令将任务在前后台进行切换。

```bash
cmd &  在启动程序的时候将程序放到后台执行，cmd 表示任意一个命令
Ctrl+z 停止进程并放入后台
jobs   显示当前暂停的进程
bg %N  使第N个任务在后台运行（%前有空格，经过测试，在 MacOS 下 % 可带可不带）
fg %N  使第N个任务在前台运行
```



```bash
# 执行 top 程序
bash-3.2$ top

# 按 Ctrl+z 快捷键将 top 程序暂停并放到后台
[1]+  Stopped                 top

# 使用 jobs 命令查看后台任务，1 代表这个 job 的 ID
bash-3.2$ jobs
[1]+  Stopped                 top

# 执行 htop 程序
bash-3.2$ htop

# 按 Ctrl+z 快捷键将 htop 程序暂停并放到后台
[2]+  Stopped                 htop

bash-3.2$ jobs
[1]-  Stopped                 top
[2]+  Stopped                 htop

# 后台执行 emacs 程序
bash-3.2$ emacs &
[4] 36906
[3]   Exit 127                em

bash-3.2$ jobs
[1]-  Stopped                 top
[2]+  Stopped                 htop
[4]   Running                 emacs &

# 将 htop 程序切换到前台
bash-3.2$ fg 2
htop
```

