# go mod 模式无法编译UTF8BOM格式的源代码

使用 go mod 模式编译代码的时候发现会出现编译失败，报找不到包的错误。

使用一个 Demo 来复现。Demo 工程结构如下。

```bash
$tree
.
├── go.mod
├── main.go   # UTF8-BOM 格式文件
└── mypkg
    └── mypkg.go
```



``` go
// main.go
package main

import (
	"fmt"
	"testbom/mypkg"
)

func SayHi() {
	fmt.Println("hi")
}

func main() {
	SayHi()
	mypkg.SayHello()
}
```



```go
//  mypkg.go
package mypkg

import "fmt"

func SayHello() {
	fmt.Println("Hello")
}
```



```go
// go.mod
module testbom

go 1.14
```

编译该工程的时候会报如下错误：`main.go:5:2: cannot find package`

通过调试 go 的源代码，发现错误在下面这个地方.

``` go
func scanFiles(files []string, tags map[string]bool, explicitFiles bool) ([]string, []string, error) {
	imports := make(map[string]bool)
	testImports := make(map[string]bool)
	numFiles := 0
Files:
	for _, name := range files {
		r, err := os.Open(name)
		if err != nil {
			return nil, nil, err
		}
               
         // I add these code to check if the source code is with BOM
		var fheader = make([]byte, 3)
		_, err = r.Read(fheader)
		if err != nil {
			fmt.Println("error: ", err)
		}
		if fheader[0] == 0xef && fheader[1] == 0xbb && fheader[2] == 0xbf {
			r.Seek(3, 0)
		} else {
			r.Seek(0, 0)
		}
         ///////////////////////////////////////////

		var list []string
                // if a file is with BOM, the return list is empty
		data, err := ReadImports(r, false, &list)
		r.Close()
		if err != nil {
			return nil, nil, fmt.Errorf("reading %s: %v", name, err)
		}
// ... ...
}
```

在该函数内添加了一段代码来处理 UTF8 BOM 格式的文件。如果没有添加这段代码，在调用函数 `ReadImports` 的过程中就会由于文件开头多余的 BOM 字符导致解析失败。

这个错误产生的根本原因是 go 编译器没有使用统一的处理流程来对需要处理的文件做预处理。比如上面代码中直接使用 `os.Open` 来读取文件就是不合理的，很容易导致处理特殊编码的文件失败进而给出一个意义不明的错误提示。

[Issue](https://github.com/golang/go/issues/46290)



