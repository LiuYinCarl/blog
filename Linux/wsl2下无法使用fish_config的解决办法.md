# wsl2 下无法使用 fish_config 的解决办法



## 版本信息

wsl:

```bash
➜  tmp cat /etc/lsb-release
DISTRIB_ID=Ubuntu
DISTRIB_RELEASE=20.04
DISTRIB_CODENAME=focal
DISTRIB_DESCRIPTION="Ubuntu 20.04.2 LTS"
```

fish:

```bash
➜  tmp fish -v
fish, version 3.1.0
```



## 问题

在 wsl2 使用 `fish_config` 命令无法打开 fish 的 配置网页。



## 解决办法

在当前版本的 fish，每次执行 `fish_config` ，都会在 `/tmp` 目录下建立一个临时的配置文件。命名类似如下：

``` bash
➜  tmp ls -a
./  ../ web_configrmjqe8lt.html
```

在这种情况下，只要直接在 Windows 中访问这个文件即可打开 fish 的 web 配置界面。

那么如何找到这个文件呢？

首先得在 Windows  下找到 Ununtu 子系统的目录路径，可以打开资源管理器，在路径栏输入如下命令：

``` bash
\\wsl$
```

即可看到 Ubuntu 子系统的路径，然后找到 `/tmp` 目录，随便在一个浏览器中访问 `web_configrmjqe8lt.html` 文件即可。

