# `CMake` 编译 `Libevent`

之前粗略看完了 `libevent` 的文档，现在想深入学习一下它的代码。遇到的第一个问题是如何调试 `libevent` 源码。由于 `libevent` 不是一个单独的程序，所以需要自己写小例子，然后在调试小例子的过程中入 `libevent` 的内部去学习。

使用上面这种方法学习，我遇到了几个问题：

1. 编译 `libevent`
2. 在自己的小例子中使用和链接 `libevent` 的头文件和动态库

首先是第一个问题，虽然我电脑（ `Manjaro` ）之前在安装其他软件的时候已经安装了 `libevent` ，但是安装的是 `release` 版本(编译的时候没有带调试信息而且代码进行了优化)。也就是说如果使用它的话，那么我们在调试过程中是无法看到源代码，所以需要自己以 `debug` 模式编译一份库出来。

`libevent` 版本 ： `Libevent 2.2.0-alpha-dev` ，
使用的编译工具是 `cmake 3.13.1` ， `gcc 9.2`

操作系统 `manjaro`

如何直接按照 `READMD.md` 来编译的话，编译出来的是 `Relaese` 版本，要编译 `Debug` 版本的话需要修改下 `CMakeLists.txt` 在里面加上一行代码，然后按照要求编译就行。

``` cmake
SET(CMAKE_BUILD_TYPE Debug)  # 要添加的

# 原来的，添加的代码放在下面这个判断之前就可以了
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release
        CACHE STRING "Set build type to Debug or Release (default Release)" FORCE)
endif()
```

第二个问题是如何使用自己编译的 `libevent` 。如果使用 `g++` 直接编译的话, 搜索一下 `gcc` 的编译链接参数，编译的时候添加对应参数就行了。不过我使用的是 `CLion` + `CMake` 所以编译项目的时候需要配置一下项目的 `CMakeLists.txt` 。假设我的项目只有一个 `main.cpp` ，里面使用了 `libevent` 。那么项目的 `CMakeLists.txt` 文件如下：

 

``` cmake
# cmake 参考 https://blog.csdn.net/Haoran823/article/details/71657602

# cmake 版本要求
cmake_minimum_required(VERSION 3.5)
# 项目名字
project(LearnLibevent)
# C++ 版本
set(CMAKE_CXX_STANDARD 11)
# 自己编译的 libevent 头文件路径
include_directories(/home/carl/github/libevent/bulid/include)
# 自己编译的 libevent 依赖库路径
link_directories(/home/carl/github/libevent/bulid/lib)
# 依赖库，不加也行 下面target_link_libraries也写了
link_libraries(event)
# 先编译项目
add_executable(LearnLibevent main.cpp)
# 后链接动态库
target_link_libraries(LearnLibevent event)
```

做完这些， `debug` 的时候就可以成功进入 `libevent` 代码中了。

