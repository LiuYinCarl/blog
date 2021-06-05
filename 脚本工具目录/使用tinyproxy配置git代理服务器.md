# 使用 tinyproxy 配置 git 代理服务器

## 原因和目的

由于国内网络的原因，很多时候在使用 git 从 github 拉代码以及提交代码的时候，都会网络错误，对个人开发工作影响比较大。所以一直希望能够能配置一条本地本地电脑与 github 的稳定链路。

经过比较，决定使用 git 代理的方式来实现这个目标。网上有一些其他人提供的免费 git，但考虑到不稳定以及不安全，不予考虑。于是决定自己搭建一个 git 代理服务器。

这个代理服务器只是用来提高访问 github 仓库的速度以及保证稳定性，所以实现一个最简单的配置即可。于是选择了 tinyproxy。



## 条件

测试服务器：阿里云香港轻量服务器 Ubuntu20

测试客户端：Winsows wsl Ubuntu20, Windows 10



## 部署

安装 tinyproxy

```bash
# 安装 tinyproxy
sudo apt install tinyproxy
```



修改 tinyproxy 配置文件

```bash
# 修改配置文件
vim /etc/tinyproxy/tinyproxy.conf
```



打开配置文件后需要修改的是如下几个配置

```bash
# 修改端口号，尽量将该端口号修改为大于 1024，不然需要使用 root 权限才可以启动 tinyproxy
Port 8888

# 修改允许连接到 tinyproxy 的地址，如果没有特殊需求，可以直接将改行注释掉，允许所有 IP 访问
#Allow 127.0.0.1

# 账号与密码设置，这个设置建议打开，不然 tinyproxy 可能被其他人利用，消耗服务器的流量，
# 第二列填写要设置的用户名，第三列填写要设置的密码，设置账号密码的时候建议不要使用特殊符号，
# 使用字母和数字组合即可，不然等下给 git 设置代理服务器地址的时候需要对密码做转义
BasicAuth username password
```



停启代理服务器

```bash
# 启动代理服务器
service tinyproxy start

# 关闭代理服务器
service tinyproxy stop

# 重启代理服务器
service tinyproxy stop
```



需要注意的是，如果使用的服务器是一些供应商如阿里云提供的，可能还得需要在服务器供应商的防火墙中将配置的代理端口开放。



## 客户端 git 代理的配置

客户端需要先安装 git。



配置 git http 代理

```bash
# 如果上面配置了 tinyproxy 的密码，使用如下命令配置代理
git config --global http.proxy http://username:password@ip:port

# 如果上面没有配置 tinyproxy 的密码，使用如下命令配置代理
git config --global http.proxy http://ip:port

# 取消 git 代理配置
git config --global --unset http.proxy
```



配置 git https 代理

```bash
# 如果上面配置了 tinyproxy 的密码，使用如下命令配置代理
git config --global https.proxy https://username:password@ip:port

# 如果上面没有配置 tinyproxy 的密码，使用如下命令配置代理
git config --global https.proxy https://ip:port

# 取消 git 代理配置
git config --global --unset https.proxy
```



### 如果使用的是 LInux 客户端，可以使用如下脚本进行快速的配置开关操作

```bash
# git_proxy.sh
#!/bin/bash

if [ $# = 0 ]; then
    echo "script arguments error"
    exit
fi

if [ $1 = "set" ]; then
	# 下面这行配置你的 git http 代理
    git config --global http.proxy http://username:password@ip:port
    echo "set git proxy success"

elif [ $1 = "unset" ]; then
    git config --global --unset http.proxy
    echo "unset git proxy success"

else
    echo "script arguments error"
fi
```

配置好之后，使用的时候只需要执行 如下命令即可。

```bash
# 配置 git 代理
bash git_proxy.sh set

# 取消 git 代理配置
bash git_proxy.sh unset
```



## 如何确定 git 是否使用了代理

在服务器中安装 iftop 工具，客户端在配置了 git 代理之后下载一个比较大的 git 项目，然后查看总流量以及实时流量的情况

```bash
# 安装 iftop
sudo apt install iftop

# 查看流量情况
iftop
```



![image-20210605111516085](E:\blog\脚本工具目录\images\使用tinyproxy配置git代理服务器\image-20210605111516085.png)

最后一列即为总流量。



## 参考

[4个Linux下的网络流量实时监控工具](https://idoseek.com/1612)

[使用Tinyproxy搭建透明代理](https://sparkydogx.github.io/2018/11/20/tinyproxy/)