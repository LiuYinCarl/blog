# Linux下使用SVN的一些技巧

## diff 工具
Linux 下 SVN 默认使用的 diff 工具没有语法高亮，看代码很不方便，所以可以考虑使用 colordiff 替代默认的 diff 工具。

以 CentOS 兄系统为例子

```bash
# 安装 colordiff
apt install colordiff

# 修改 SVN 的配置文件，修改或者添加下列这行
# diff-cmd = colordiff
vim ~/.subversion/config
```

## SVN 命令速查

```bash
# 查看本地文件的修改
svn diff filename

# 比较本地文件和任意版本号 A 的区别
svn diff -rA

# 比较任意两个版本号 A 和 B 的区别
svn diff -rA:B

# 查看 SVN 的 log
svn log ur1

# 或者进入 SVN 版本库的目录，执行
svn log

# 回退文件的本地修改
svn revert filename

# 查看本地目录的修改
svn diff dirname

# 查看本地目录中修改过的文件
svn diff dirname | grep Index

# 查看所有的分支
svn ls http://xxxx/branches

# 更新代码库, dir 代表目录，如果不添加这个参数，表示更新当前目录及子目录到最新版本
svn update dir
```