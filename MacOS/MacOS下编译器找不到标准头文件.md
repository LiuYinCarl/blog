# MacOS下编译器找不到标准头文件的解决办法



如果找不到的是 C 头文件，可以按照如下办法进行解决。

```bash
# 1 获取 Xcode 的 SDK 位置
xcrun --show-sdk-path

# 2 在路径下找到头文件include 目录后进行 export
export CPATH=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
```



