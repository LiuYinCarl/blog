# WSL 与 Windows 共享目录

## 在 Windows 下访问 WSL 目录

一个简单的方式是在 Windows 的文件管理器的路径框中输入下面的命令，即可以立刻到达 WSL 的根目录了。

``` powershell
\\wsl$
```

## 在 WSL 中访问 Windows 目录

Windows 的所有盘的目录都在 WSL 的 `/mnt` 目录下。

```bash
➜  mnt cd /mnt
➜  mnt ls
c/  d/  e/
```

可以看到 , Windows 中的 C， D, E 三个盘都在 `/mnt` 目录下。

## 利用软链接在 WSL 下构建与 Windows 同步的开发环境

WSL 与 Windows 共享目录的需求是这样产生的：有些工程项目，同时有 Windows 编译选项和 Linux 编译选项，在 Windows 平台下进行开发和调试，最终在 Linux 平台运行。这样子我们就需要在 Windows 下测试通过后再检查一次 Linux 平台上能否通过编译和测试。

在开发期间，如果另外配置一台 Linux 开发机进行开发，在不同机器上进行项目的同步会很麻烦。这个时候可以选择使用 WSL，Windows 与 WSL 共享目录。在 Windows 上编译测试通过之后，切换到 WSL，再进行一次编译测试。当两个平台的编译测试都没有问题的时候，再提交到版本管理仓库中。

那么，如何让 WSL 与 Windows 共享目录呢？办法是在 WSL 下使用软链接。通过上面第二节的内容，我们已经知道了在 WSL 下如何访问 Windows 下的所有目录，所以只需要在 WSL 的开发目录下构建一个软链接即可以在避免直接访问 `/mnt` 目录的同时访问到 Windows 下的目录。

假设我们在 Windows 下的工程目录为 `E:\testProject`，WSL 中想在 `~/Dev` 目录下建立共享目录，在 WSL 下进行如下设置即可。

``` bash
➜  ~ mkdir Dev
➜  ~ cd Dev/
➜  Dev ln -s /mnt/e/testProject testProject
➜  Dev ls
testProject@
➜  Dev cd testProject/
➜  testProject pwd
/home/lzh/Dev/testProject
➜  testProject
```



