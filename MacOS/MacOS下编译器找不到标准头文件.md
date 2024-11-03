# MacOS下编译器找不到标准头文件的解决办法

如果找不到的是标准头文件，可以按照如下办法进行解决。

```bash
# xcrun --show-sdk-path 获取 Xcode 的 SDK 位置
# export CPATH 将头文件目录写入 CPATH
export CPATH=`xcrun --show-sdk-path`/usr/include

# 也可以另外设置一个 SDKPATH, 这是 Clang 和 GCC 都接受的一个设置，
# 不过在 GCC 13.2 和 Clang 18.0.0 的手册中没有找到这个设置,
# 但是设置之后确实是可以生效的
export SDKROOT="`xcrun --show-sdk-path`"
```

如果是找不到 C++ 的标准头文件，则可以参考如下方式进行处理。

```bash
# 首先查看以下 clang 或 gcc 的头文件查找路径
$ clang++ -E -x c++ - -v < /dev/null
#include "..." search starts here:
#include <...> search starts here:
 /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1
 /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/16/include
 /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
 /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include
 /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks (framework directory)
```

里面展示的第一行就是 MacOS 安装的C++ 头文件的路径，只需要将这个路径配置到 `~/.bashrc` 即可。

```bash
# 因为这个路径会在 SDK 路径下，所以可以直接使用 SDK 路径进行拼接
export CPLUS_INCLUDE_PATH=`xcrun --show-sdk-path`/usr/include/c++/v1
```


## 参考

1. https://andreasfertig.blog/2021/02/clang-and-gcc-on-macos-catalina-finding-the-include-paths/
2. https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc.pdf
3. https://clang.llvm.org/docs/UsersManual.html
