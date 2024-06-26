# Windows 实用命令

## MSDN bat 教程

[MSDN bat 教程](https://docs.microsoft.com/en-us/previous-versions/tn-archive/cc722477(v=technet.10)?redirectedfrom=MSDN)

## SS64 多脚本教程

[SS64 多脚本教程/查询工具](https://ss64.com/)

## 查看 CPU 温度

powershell 管理员权限下执行任意一条即可

```powershell
"CPU: $(((Get-CimInstance -Namespace root/WMI -ClassName MSAcpi_ThermalZoneTemperature)[0].CurrentTemperature - 2731.5) / 10) C"

"CPU: $(((Get-CimInstance -Namespace root/WMI -ClassName MSAcpi_ThermalZoneTemperature | where InstanceName -eq "ACPI\ThermalZone\TZ00_0").CurrentTemperature - 2731.5) / 10) C"
```

## Windows 查找目录下文件中包含某个字符串

可以使用 Windows 自带的 findstr.exe 来实现。

 `findstr.exe /s /i "string" *.* `

上面的命令表示，当前目录以及当前目录的所有子目录下的所有文件中查找 "string" 这个字符串。

`*.*` 表示所有类型的文件。

`/s` 表示当前目录以及所有子目录

`/i` 表示不区分大小写

可以参考 `help findstr` 的输出解释来使用此命令。

## 配置 ripgrep 来替代 findstr

如果安装了 VSCode, 直接搜索 rg.exe 就可以了，然后添加到系统路径。

[ripgrep用法](https://github.com/BurntSushi/ripgrep/blob/master/GUIDE.md)

## ripgrep 配合 powershell 的 grep 替代品  Select-String

使用 `ripgrep` 可以快速检索出需要的东西，如果需要对 `ripgrep` 的结果再次检索，可以使用 `powershell` 的 `Select-String`

```powershell
rg "a word" ./test.cpp | Select-String "another word"
```

[How to Use PowerShell’s Grep (Select-String)](https://adamtheautomator.com/powershell-grep/)

## Windows 下多个 lib 合并的方法

[# windows 下多个 lib 合并的方法|# 查看 lib 是导入库还是静态库](https://blog.csdn.net/bandaoyu/article/details/86604345)

 

```powershell
 # 开始-》所有程序-》Microsoft Visual studio 2010-》visual studio tools-》Visual studio 命令提示符。在出来的Dos窗口中，输入命令：
  lib.exe /out:objectlib.lib lib1.lib lib2.lib
 # 该目录下会生成合并后的lib库object.lib
（或lib.exe /out:D:\objectlib.lib   D:\mylib\*.lib   将D:\mylib目录下的lib合并为objectlib.lib)存在D目录下）
```

## CreateProcess 创建后台进程

``` c++
//  执行用户脚本
static char userCmd[300] = { 0 };
std::string s1 = "D:/SoftwareInstallDir/Python3.8.6/python.exe ";
std::string s2(userCmd);
std::string cmd = s1 + s2; // 用户命令和参数

STARTUPINFOA si;
PROCESS_INFORMATION* pi = new PROCESS_INFORMATION;
ZeroMemory(&si, sizeof(si));
si.cb = sizeof(si);
ZeroMemory(pi, sizeof(PROCESS_INFORMATION));

if (!CreateProcess(
    NULL,  // No module name
    (LPSTR)cmd.c_str(),        // Command line
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    FALSE,          // Set handle inheritance to FALSE
    CREATE_NO_WINDOW,  // don't show dos windows
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory 
    (LPSTARTUPINFOA)&si,            // Pointer to STARTUPINFO structure
    pi))           // Pointer to PROCESS_INFORMATION structure
{
    // process error
}
```

## bat 脚本批量修改文件名

```bat
@echo "文件批量重命名脚本"
@echo "使用方式：将本脚本放置在需要重命名文件的同级目录下"
@echo "将 prefix 改成需要添加的前缀"
@echo "将 suffix 修改成需要重命名的文件后缀"
@echo "WARN: if the file name is garbled, modify the file encoding to ANSI."
@echo "      see https://zhidao.baidu.com/question/555438747.html"
@echo.
@echo.
@echo "modify list:"
@echo.

@echo off
SET prefix="文件前缀"
SET suffix="txt"

for /f "delims=" %%n in ('dir /b *.%suffix%') do (
    ren "%%n" "%prefix%%%n"
    echo %%n "====>"  %prefix%%%n
)
```
