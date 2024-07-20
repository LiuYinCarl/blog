# Linux 下 clang 找不到标准库头文件

有些时候，使用如 `apt install clang` 命令安装完成 clang 和 clang++ 后，
在编译时会有找不到标准库头文件，如 `iostream` 等的问题。
可以按照这里介绍的方法进行排查。

clang 和 clang++ 一般会使用 GCC 和 G++ 的标准库头文件，并且如果存在多个版本时，
会使用最新的版本。如果你安装了一个比较新的 GCC 版本而且没有安装对应的 G++
那么 clang 就会找不到对应版本的 C++ 头文件。

为了检查是否是这个原因导致的，需要先检查当前 clang++ 选择了哪个版本的 C++ 标准库。

```bash
kenshin:~$ clang++ -v -E
Ubuntu clang version 14.0.0-1ubuntu1.1
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
Found candidate GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/11
Found candidate GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/12
Selected GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/12
Candidate multilib: .;@m64
Selected multilib: .;@m64
```

从 `Selected GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/12` 这句
可以看到 clang++ 选择了 GCC12 版本的 C++ 的标准库。

接着再检查是否安装了这个版本的 C++ 标准库。

```bash
kenshin:~$ ls /usr/include/c++/
11/
```

可以看到，并没有安装 GCC12 版本的标准库，只有 GCC11 版本的，接着安装对应的 GCC 标准库即可解决这个问题。

```bash
kenshin:~$ sudo apt install libstdc++-12-dev
```

## 参考

1. [clang++ cannot find iostream](https://askubuntu.com/questions/1449769/clang-cannot-find-iostream)

