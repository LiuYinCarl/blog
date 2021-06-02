# z.lua 安装脚本

z.lua 在命令行下用来做目录跳转很方便，但是我自己使用的环境比较多，所以写了一个脚本来方便的快速安装 z.lua。



## Linux

因为我使用 fish shell 比较多，所以现在这个脚本只支持 fish shell，如果使用的是其他的 shell, 需要到[项目的 readme](https://github.com/skywind3000/z.lua/blob/master/README.cn.md) 里面去找下。



```bash
#!/bin/bash
# this is a script to auto install z.lua. Now, only support fish shell

function f_check_program_exist() {
    if ! type ${1} >/dev/null 2>&1; then
        return 1
    else
        return 0
    fi
}

function f_prepare() {
    cd

    if [ ! -d ~/.config ]; then
        mkdir ~/.config
    fi

    cd .config

    rm "z.lua" -rf

    git clone https://github.com/skywind3000/z.lua.git --depth=1

    return 0
}

function f_fish_install_zlua() {
    if [ ! -d ~/.config/fish/conf.d/ ]; then
        mkdir  ~/.config/fish/conf.d/
    fi

    touch ~/.config/fish/conf.d/z.fish

    echo "source (lua ~/.config/z.lua/z.lua --init fish | psub)" > ~/.config/fish/conf.d/z.fish
}

function f_main() {
    f_check_program_exist "lua"
    if [ $? -eq 1 ]; then
        echo "please install lua first"
        exit
    fi

    f_check_program_exist "fish"
    if [ $? -eq 1 ]; then
        echo "please install fish first"
        exit
    fi

    f_prepare

    f_fish_install_zlua

    echo "install z.lua success. reopen a terminal to use z.lua"
    echo "visit https://github.com/skywind3000/z.lua/blob/master/README.cn.md to see more info"
}

f_main
```



## Windows

Windows 下我一般使用 Power Shell，所以简单说下 Power Shell 下的 z.lua 的安装。

以下所有命令均在 Power Shell 下输入。

```powershell
# 检查配置文件的路径
$profile
# 检查在系统上是否创建了 PowerShell 配置文件
test-path $profile
# 如果没有创建的话，创建一下
new-item -path $profile -itemtype file -force
# 使用记事本打开配置文件
notepad $profile

# 将以下内容写入打开的配置文件
Invoke-Expression (& { (lua /path/to/z.lua --init powershell) -join "`n" })
```

然后重新启动一个 Power Shell，如果提示 “此系统上禁止运行脚本” 的话，说明当前 Windows 的执行策略设置的不对，不允许我们运行未签名的脚本。如果想要给给我们的配置文件签名的话，按照[官方指导](https://docs.microsoft.com/zh-cn/powershell/module/microsoft.powershell.core/about/about_signing?view=powershell-7.1)进行操作。

如果想偷懒的话，按如下步骤操作，首先以管理员权限打开 Power Shell

```powershell
# 查看 Windows 上的现用执行策略，应该是  Restricted
get-executionpolicy
# 修改执行策略
set-executionpolicy remotesigned
```

这里提一下几种允许的执行策略:

Restricted 执行策略不允许运行任何脚本。 AllSigned 和 RemoteSigned 执行策略阻止 PowerShell 运行没有数字签名的脚本。



```powershell
# （不建议，没有特殊需求不用管）若要创建其他配置文件之一，如适用于所有用户和所有 Power Shell 的配置文件
new-item -path $env:windir\System32\WindowsPowerShell\v1.0\profile.ps1 -itemtype file -force
```

