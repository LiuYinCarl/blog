# OCaml 编译

Ocaml 的安装步骤比较简单，直接参照[官方文档](https://ocaml.org/docs/up-and-running)。但是我在 MacOS(M1) 下编译的时候遇到了一个问题，编译 OCaml 会失败，原因是编译器有错误，仔细看了下 `config.log` 发现是找不到 C 语言的标准头文件 `stdio.h` ，这也是我这台 Mac 的老问题了，系统里有好几个 clang，其中一个应该是搜索路径有问题，找不到标准库。知道了原因，解决起来也很方便，首先找到一个能用的 clang 编译器的路径 `/usr/bin/clang` ，然后执行 `export PATH="/usr/bin/:$PATH"` 把可用的编译器路径放在最前面即可。
