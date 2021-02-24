# Git 服务器搭建



## 步骤

以下所有步骤最好使用 root 账户来操作，比较省事

``` bash
# 1 安装 git

# 2 创建一个账户(不一定要叫 git)，用来运行 git 服务
adduser git

# 3 修改 账户 git 的密码，等下拉仓库的时候需要账户密码
passwd git

# 4 在 git 账户的根目录下创建 authorized_keys 文件，用来保存所有用户的公钥
touch /home/git/.ssh/authorized_keys

# 5 将其他用户的公钥放到 authorized_keys 文件中来，一行一个, 如何生成公钥见下文

# 6 初始化 git 仓库，假设准备使用 /data/git/project1.git/ 作为仓库仓库地址
# project1.git 用 .git 做后缀其实可以可加可不加，但是一般都加
# --bare 参数用于创建裸仓库，裸仓库不包含工作区，不能再这个目录下执行一般的 git 命令
git init --bare /data/git/project1.git

# 7 修改仓库目录的所有者
# -R 参数是递归修改的意思，就是 /data/git/project1.git 目录和它的子目录都需要修改目录所有者
chowm -R git:git /data/git/project1.git

# 8 禁用登录 shell, 不允许上面创建的 git 这个账户登录服务器
# 编辑 /etc.passwd 文件
# 将这样一行 git:x:1001:1001:,,,:/home/git:/bin/bash
# 改成 git:x:1001:1001:,,,:/home/git:/usr/bin/git-shell

# 9 测试克隆仓库
git clone git@YouServerIp:/data/git/project1.git
```



## Windows 下生成 ssh 密钥

```powershell
# 使用 powershell cmd git_bash 等终端

# 1 进入 C:\Users\你的账户\.ssh\ 目录
cd c:
cd Users\你的账户\.ssh

# 2 生成公钥和私钥 命令执行后会要求你起个文件名，可以随便起，用默认的也可以，但是要防止覆盖之前生成的密钥文件
# 输入名字后之后要求输入密码/确认密码，直接按回车就好
ssh-keygen -t rsa

# 将公钥保存到上面提到的服务器的 authorized_keys 文件下,公钥文件的格式类似于 xxxx.pub
```



## Linux 下生成密钥

```bash
# 除了路径是 /home/.ssh, 其他和 Windows 操作一致
```



## 参考：

[搭建Git服务器 - 廖雪峰的官方网站 (liaoxuefeng.com)](https://www.liaoxuefeng.com/wiki/896043488029600/899998870925664)

[Git 本地仓库和裸仓库 | MoeLove](https://moelove.info/2016/12/04/Git-本地仓库和裸仓库/)