# Linux 根据进程 PID 找到需要的进程信息

下面以 python 解释器程序作为例子，找到进程启动目录，二进制程序，日志文件位置等信息。

```sh
$ ps -ef | grep "./python"
kenshin     5331    5187  0 15:02 pts/1    00:00:00 ./python

# 进入 /proc 下对应目录
$ cd /proc/5331

# 列出进程信息 'll' 或者 'ls -l'
kenshin:/proc/5331$ ls -l
total 0
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 arch_status
dr-xr-xr-x  2 kenshin kenshin 0 Apr 24 15:02 attr
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 autogroup
-r--------  1 kenshin kenshin 0 Apr 24 15:02 auxv
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 cgroup
--w-------  1 kenshin kenshin 0 Apr 24 15:02 clear_refs
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 cmdline
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 comm
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 coredump_filter
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 cpu_resctrl_groups
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 cpuset
lrwxrwxrwx  1 kenshin kenshin 0 Apr 24 15:02 cwd -> /home/kenshin/cpython
-r--------  1 kenshin kenshin 0 Apr 24 15:02 environ
lrwxrwxrwx  1 kenshin kenshin 0 Apr 24 15:02 exe -> /home/kenshin/cpython/python
dr-x------  2 kenshin kenshin 0 Apr 24 15:02 fd
dr-xr-xr-x  2 kenshin kenshin 0 Apr 24 15:02 fdinfo
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 gid_map
-r--------  1 kenshin kenshin 0 Apr 24 15:02 io
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 limits
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 loginuid
dr-x------  2 kenshin kenshin 0 Apr 24 15:02 map_files
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 maps
-rw-------  1 kenshin kenshin 0 Apr 24 15:02 mem
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 mountinfo
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 mounts
-r--------  1 kenshin kenshin 0 Apr 24 15:02 mountstats
dr-xr-xr-x 57 kenshin kenshin 0 Apr 24 15:02 net
dr-x--x--x  2 kenshin kenshin 0 Apr 24 15:02 ns
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 numa_maps
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 oom_adj
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 oom_score
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 oom_score_adj
-r--------  1 kenshin kenshin 0 Apr 24 15:02 pagemap
-r--------  1 kenshin kenshin 0 Apr 24 15:02 patch_state
-r--------  1 kenshin kenshin 0 Apr 24 15:02 personality
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 projid_map
lrwxrwxrwx  1 kenshin kenshin 0 Apr 24 15:02 root -> /
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 sched
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 schedstat
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 sessionid
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 setgroups
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 smaps
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 smaps_rollup
-r--------  1 kenshin kenshin 0 Apr 24 15:02 stack
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 stat
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 statm
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 status
-r--------  1 kenshin kenshin 0 Apr 24 15:02 syscall
dr-xr-xr-x  3 kenshin kenshin 0 Apr 24 15:02 task
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 timens_offsets
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 timers
-rw-rw-rw-  1 kenshin kenshin 0 Apr 24 15:02 timerslack_ns
-rw-r--r--  1 kenshin kenshin 0 Apr 24 15:02 uid_map
-r--r--r--  1 kenshin kenshin 0 Apr 24 15:02 wchan
```
其中 `cwd -> /home/kenshin/cpython` 是进程启动目录。`exe -> /home/kenshin/cpython/python`
是进程的二进制文件。`cmdline` 是进程启动的参数。`fd/` 目录下保存了文件所有打开的句柄。

```sh
kenshin:/proc/5331/fd$ ll
total 0
dr-x------ 2 kenshin kenshin  0 Apr 24 15:02 ./
dr-xr-xr-x 9 kenshin kenshin  0 Apr 24 15:02 ../
lrwx------ 1 kenshin kenshin 64 Apr 24 15:11 0 -> /dev/pts/1
lrwx------ 1 kenshin kenshin 64 Apr 24 15:11 1 -> /dev/pts/1
lrwx------ 1 kenshin kenshin 64 Apr 24 15:11 2 -> /dev/pts/1
```
