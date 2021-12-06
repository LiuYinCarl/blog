# blog

## Markdown 排版规范

1. 中英文之前，中文与数字之前非特殊情况必须要带有一个空格
2. 专有名字必须规范写法，比如 HTTP 不能写成 Http, http
3. 代码必须符合markdown 语法规范
4. 如果代码段内容不属于是伪代码或者不是代码，那么语言类型保持为空
5. 段标题与上一段的内容之间保持一行空行
6. 链接说明不允许为空，不允许为链接，必须要有实际意义
7. 每段的行首不需要有空格
8. 多余空格和不可见符号需要删除（通过格式检查脚本）
9. 每次提交之前，需要用 VSCode 插件 Markdown Padding 和 markdown-formatter 调整格式



## 图片规范

1. 图片放置在当前目录下的 `images` 目录下，图片命名必须含有实际意义并且只能包含中文和英文字母
2. 能用表格，就不要用图片



## 内容规范

1. 文件名不能和目录名无关，文件内容不能和文件无关，这样子自己找起来很麻烦



## 目录规范

1. 目录深度最多为两层，如 `/Linux/shell 脚本规范`
2. 文件名和目录名不能包含空格和特殊字符，如果没有特殊情况，最好只含有中文和英文字母
3. 每个目录内需要包含一个 `README.md` 来介绍该目录的内容
4. 在该工程中不要存放任何代码图片，代码，文档之外的任何内容，尤其是可执行文件，以减小目录大小



## Git 规范

1. commit 不需要任何内容，通过执行自动提交脚本来进行代码提交

