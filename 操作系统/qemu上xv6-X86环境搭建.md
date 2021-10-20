# qemu 上 xv6-X86 环境搭建

使用的操作系统为 Ubuntu20。


qemu 环境准备

```bash
apt-get install qemu-system
```

xv6 代码拉取编译

```bash
git clone https://github.com/mit-pdos/xv6-public
cd xv6-public
make
make qemu-nox # qemu-nox 是不使用 GUI 界面的，适合在终端下操作
# make qemu  # 如果有终端，使用 make qemu，具体区别看 Makefile 参数
```

## xv6-X86 资料

[xv6 book](https://iitd.github.io/os/nptel21/book.pdf)

[xv6 中文文档](http://staff.ustc.edu.cn/~chizhang/OS/Labs/MIT-XV6-%D6%D0%CE%C4%B7%AD%D2%EB%B0%E6.pdf)
