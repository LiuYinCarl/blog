# eglot 的配置

eglot 是一个 LSP 客户端实现。我使用 eglot 来实现 Emacs C/C++ 代码补全和跳转，使用 clangd 来作为 LSP 后端。

使用过程中发现 eglot 的配置还是具有一定复杂性的，所以这里记录一下。

## 安装 use-package

我使用 use-package 作为配置管理工具，所以下面列出的配置是基于 use-package 的，下面代码是检查 Emacs 是否安装了 use-package 插件的代码，如果没有安装，将会自动安装，将以下代码复制到 `~/.emacs`(Emacs 默认配置文件中即可)。

```lisp
(unless (package-installed-p 'use-package)
  (package-refresh-contents)
  (package-install 'use-package))
```

## 安装 clangd

如果使用的是 Ubuntu，可以直接执行 `sudo apt install clangd` 安装 clangd。其他 Linux 操作系统上 clangd 的安装方法基本相同，可以自行搜索。

## 安装 eglot

```lisp
;; 给 clangd 生成项目配置文件的工具 compile_commands.json
;; https://zhuanlan.zhihu.com/p/145430576
;; https://github.com/rizsotto/Bear

;; 下面的代码是使用 use-package 配置 eglot 的过程
(use-package eglot
  :config
  ;; 给 c-mode, c++-mode 配置使用 clangd-11 作为 LSP 后端
  ;; 需要主要的是，要根据上面你安装的 clangd 程序的名字填写这个配置
  ;; 我这里写成 clangd-11 是因为安装的 clangd 程序的名字为 clangd-11
  (add-to-list 'eglot-server-programs '((c-mode c++-mode) "clangd-11"))
  ;; 使用 c-mode 是，开启 eglot
  (add-hook 'c-mode-hook 'eglot-ensure)
  ;; 使用 c++-mode 是，开启 eglot
  (add-hook 'c++-mode-hook 'eglot-ensure))
```

## 使用 clangd



### 配置Compilation Database

clangd 的工作原理与代码编译过程联系紧密，需要为目标项目配置`Compilation Database`。clangd 依赖编译器前端提供索引和 AST 信息，这也注定了 clangd 在提供高准确跳转/补全的同时，也要用户配置好项目的“编译说明”，这个“编译说明”便被称为 [Compilation Database](https://link.zhihu.com/?target=https%3A//clang.llvm.org/docs/JSONCompilationDatabase.html)。

在 clangd 看来，Compilation Database 是一个名为`compile_commands.json`的 JSON 文件，它会记录每个`.c/.cpp`文件的编译依赖和编译选项。如果一个项目源码文件较多，可以借助`bear`等工具在项目编译过程中记录相关编译选项。

作者：「已注销」
链接：https://zhuanlan.zhihu.com/p/139480735

这里介绍一下如何使用 [Bear](https://github.com/rizsotto/Bear) 工具来生成 `compile_commands.json` 文件。

**更新：在新版本的 bear，例如 3.0.18 中，生成 compile_commands.json 的默认参数有了变化。**

```bash
$ bear --help
Usage: bear [--output <arg>] [--verbose] -- ...

  --output <arg>       path of the result file (default: compile_commands.json)
  --verbose            run in verbose mode
  -- ...               command to execute
```

根据使用提示，新版本的 bear 需要至少使用 `bear -- make` 才可以生成默认配置文件，相比之前多了一个 `--` 参数. 



如果使用的是 Ubuntu, 使用 `apt install bear` 安装 Bear。

#### 以 [Lua 项目](https://github.com/lua/lua)为例子，介绍如何使用 Bear 为 make 工程生成  compile_commands.json

```bash
$ ls
Makefile  README  doc  src
$ bear make
$ ls
Makefile  README  compile_commands.json  doc  src
```

生成的 `compile_commands.json` 文件格式

```json
[
    {
        "arguments": [
            "gcc",
            "-c",
            "-std=gnu99",
            "-O2",
            "-Wall",
            "-Wextra",
            "-DLUA_COMPAT_5_3",
            "-DLUA_USE_LINUX",
            "-o",
            "ldump.o",
            "ldump.c"
        ],
        "directory": "/home/lzh/github/src_read/lua-5.4.3/src",
        "file": "ldump.c"
    },
    {
        "arguments": [
            "gcc",
            "-c",
            "-std=gnu99",
            "-O2",
            "-Wall",
            "-Wextra",
            "-DLUA_COMPAT_5_3",
            "-DLUA_USE_LINUX",
            "-o",
            "lvm.o",
            "lvm.c"
        ],
        "directory": "/home/lzh/github/src_read/lua-5.4.3/src",
        "file": "lvm.c"
    },
// 省略 ... ...
]
```



#### 以  [googletest 项目](https://github.com/google/googletest)为例子，介绍如何使用 Bear 为 CMake 工程生成 compile_commands.json

``` bash
$ ls
BUILD.bazel  CMakeLists.txt  CONTRIBUTING.md  CONTRIBUTORS  LICENSE  README.md  WORKSPACE  ci  compile_commands.json  docs  googlemock  googletest  library.json
$ bear cmake .
$ bear make
$ ls
BUILD.bazel     CMakeFiles      CONTRIBUTING.md  CTestTestfile.cmake  Makefile   WORKSPACE  ci                   compile_commands.json  googlemock  lib
CMakeCache.txt  CMakeLists.txt  CONTRIBUTORS     LICENSE              README.md  bin        cmake_install.cmake  docs                   googletest  library.json
```

生成的 `compile_commands.json` 文件格式

``` json
[
    {
        "arguments": [
            "/usr/bin/c++",
            "-c",
            "-I/home/lzh/test/googletest/googletest/include",
            "-I/home/lzh/test/googletest/googletest",
            "-Wall",
            "-Wshadow",
            "-Werror",
            "-Wno-error=dangling-else",
            "-DGTEST_HAS_PTHREAD=1",
            "-fexceptions",
            "-Wextra",
            "-Wno-unused-parameter",
            "-Wno-missing-field-initializers",
            "-o",
            "CMakeFiles/gtest.dir/src/gtest-all.cc.o",
            "src/gtest-all.cc"
        ],
        "directory": "/home/lzh/test/googletest/googletest",
        "file": "src/gtest-all.cc"
    },
    {
        "arguments": [
            "/usr/bin/c++",
            "-c",
            "-I/home/lzh/test/googletest/googlemock/include",
            "-I/home/lzh/test/googletest/googlemock",
            "-isystem",
            "/home/lzh/test/googletest/googletest/include",
            "-isystem",
            "/home/lzh/test/googletest/googletest",
            "-Wall",
            "-Wshadow",
            "-Werror",
            "-Wno-error=dangling-else",
            "-DGTEST_HAS_PTHREAD=1",
            "-fexceptions",
            "-Wextra",
            "-Wno-unused-parameter",
            "-Wno-missing-field-initializers",
            "-o",
            "CMakeFiles/gmock.dir/src/gmock-all.cc.o",
            "src/gmock-all.cc"
        ],
        "directory": "/home/lzh/test/googletest/googlemock",
        "file": "src/gmock-all.cc"
    },
    {
        "arguments": [
            "/usr/bin/c++",
            "-c",
            "-isystem",
            "/home/lzh/test/googletest/googletest/include",
            "-isystem",
            "/home/lzh/test/googletest/googletest",
            "-Wall",
            "-Wshadow",
            "-Werror",
            "-Wno-error=dangling-else",
            "-DGTEST_HAS_PTHREAD=1",
            "-fexceptions",
            "-Wextra",
            "-Wno-unused-parameter",
            "-Wno-missing-field-initializers",
            "-o",
            "CMakeFiles/gtest_main.dir/src/gtest_main.cc.o",
            "src/gtest_main.cc"
        ],
        "directory": "/home/lzh/test/googletest/googletest",
        "file": "src/gtest_main.cc"
    },
    {
        "arguments": [
            "/usr/bin/c++",
            "-c",
            "-isystem",
            "/home/lzh/test/googletest/googlemock/include",
            "-isystem",
            "/home/lzh/test/googletest/googlemock",
            "-isystem",
            "/home/lzh/test/googletest/googletest/include",
            "-isystem",
            "/home/lzh/test/googletest/googletest",
            "-Wall",
            "-Wshadow",
            "-Werror",
            "-Wno-error=dangling-else",
            "-DGTEST_HAS_PTHREAD=1",
            "-fexceptions",
            "-Wextra",
            "-Wno-unused-parameter",
            "-Wno-missing-field-initializers",
            "-o",
            "CMakeFiles/gmock_main.dir/src/gmock_main.cc.o",
            "src/gmock_main.cc"
        ],
        "directory": "/home/lzh/test/googletest/googlemock",
        "file": "src/gmock_main.cc"
    }
]
```

生成 `compile_commands.json` 文件之后，打开 Emacs 即可使用 eglot 来体验 C/C++ 代码项目索引、代码跳转、变量重命名、代码补全、提示信息、格式化代码 等功能。

