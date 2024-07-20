# OCaml 编译及开发环境配置

## OCaml 编译

Ocaml 的安装步骤比较简单，直接参照[官方文档](https://ocaml.org/docs/up-and-running)。但是我在 MacOS(M1) 下编译的时候遇到了一个问题，编译 OCaml 会失败，原因是编译器有错误，仔细看了下 `config.log` 发现是找不到 C 语言的标准头文件 `stdio.h` ，这也是我这台 Mac 的老问题了，系统里有好几个 clang，其中一个应该是搜索路径有问题，找不到标准库。知道了原因，解决起来也很方便，首先找到一个能用的 clang 编译器的路径 `/usr/bin/clang` ，然后执行 `export PATH="/usr/bin/:$PATH"` 把可用的编译器路径放在最前面即可。

## OCaml 开发环境配置

如果不想编译 OCaml 而是想配置 OCaml 的开发环境，可以参照 OCaml 的[安装文档](https://ocaml.org/install)进行。

在 Linux 下安装，主要步骤如下。

```bash
# 下载 opam (OCaml 包管理器)
bash -c "sh <(curl -fsSL https://raw.githubusercontent.com/ocaml/opam/master/shell/install.sh)"

# 初始化 opam 并安装默认版本 OCaml 编译器
opam init

# 激活默认环境（如果你第二步选择了 no）
eval $(opam env)

# 安装额外工具
opam install ocaml-lsp-server odoc ocamlformat utop
```

