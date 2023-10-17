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

## 参考

1. https://andreasfertig.blog/2021/02/clang-and-gcc-on-macos-catalina-finding-the-include-paths/
2. https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc.pdf
3. https://clang.llvm.org/docs/UsersManual.html
