# Emacs 配置及资料

## MacOS 安装 Emacs

### 下载安装
从 https://emacsformacosx.com/ 可以直接下载编译好的程序进行安装使用。

### homebrew 安装
使用 homebrew 安装的话，不建议直接使用 `brew install emacs` 因为这样子下载下来的 Emacs 是不带 GUI 的。

可以使用如下命令，下载带 GUI 的 Emacs 版本。

```bash
$ brew tap d12frosted/emacs-plus
$ brew install emacs-plus@29

# 配置软链接，以便可以在启动台打开 Emacs
$ ln -s /opt/homebrew/opt/emacs-plus@29/Emacs.app /Applications
```
这个方式其实就是自行下载编译对应版本的 Emacs。emacs-plus 可以使用一些可选项来优化 Emacs 使用体验，具体可以参考 `https://github.com/d12frosted/homebrew-emacs-plus`。

