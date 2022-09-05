# AutoHotKey 改键

AutoHotKey 是 Windows 上的改键工具，主要用来做按键映射。

对于我来说，改键的主要需求是将键盘的 Caps Lock 键和 Left Ctrl 键做对调，因为使用 Emacs 时这样的按键更加舒适，
所以基本的 AutoHotKey 脚本如下

```ahk
CapsLock::LCtrl
LCtrl::CapsLock
```

最近发现这个方案存在一个问题：如果使用 Windows 本地机器连接远程的 Windows 机器的话，在本地机器上修改的按键
在远程机器上会失效，如果在远程机器上也打开了 AutoHotKey 并且使用上面的改键脚本的话，在远程窗口中两台机器上的按键会冲突。
所以 AutoHotKey 需要针对远程软件做一个特殊处理。

```ahk
; 在Windows 远程桌面中不使用快捷键
#IfWinNotActive ahk_class TscShellContainerClass
CapsLock::LCtrl
LCtrl::CapsLock
#IfWinNotActive
```
`#IfWinNotActive` 会对参数中的 `TscShellContainerClass` 远程桌面窗口做特殊处理，在除这个窗口外的其他窗口中才进行按键映射，
使得本地 Windows 机器上的改键在远程软件窗口中不生效了。为了保持按键映射一致，只要在远程机器中再打开 AutoHotKey 使用第一个按键映射脚本即可。