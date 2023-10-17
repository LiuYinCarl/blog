## 步骤

## 前置准备

假设使用的是阿里云或者腾讯云等云服务器上的服务器，预计要给 jupyter notebook 使用的端口号为 23333。
那么需要先在云服务器供应商的控制台开启 23333 端口的外部访问权限。

使用的操作系统为 Linux

## 步骤

1. 安装 jupyter

```bash
pip3 install jupyter
```

2. 添加一个普通用户,名字取为 jupyter

```bash
# 添加用户
useradd -m jupyter
# 设置密码
passwd jupyter
```

3. 切换到 jupyter 用户

```bash
su jupyter
```

4. 生成配置

```bash
jupyter notebook --generate-config
```

5. 设置密码

```bash
$ python
>>> from notebook.auth import passwd
>>> passwd()
Enter password:
Verify password:
'argon2:$argon2id$v=19$m=10240,t=10,p=8$tqGFl+OfW15zyFxCF....'
>>> exit()
```

6. 修改配置文件 

```bash
$ vim /home/jupyter/.jupyter/jupyter_notebook_config.py
# 修改下面几项
c.NotebookApp.ip = '0.0.0.0' #设置能访问服务器的IP
c.NotebookApp.port = 23333 # 设置 jupyter 服务的端口，默认是8888
c.NotebookApp.open_browser = False # 打开 jupyter 不自动打开浏览器
c.NotebookApp.notebook_dir = '/home/jupyter/jupyter_dir' # 设置Jupyter 服务器的根目录
```

7. 启动 jupyter 服务器

```bash
$ jupyter notebook

# 使用下面的命令让服务后台运行
nohup jupyter notebook > jupyter.log 2>&1 &
```
