# elisp笔记

## 如何执行 elisp

两种方式
1. 在 Emacs 中执行 `M-x lisp-interaction-mode` 切换到 `lisp-interaction-mode`, 然后将光标移动到要执行的代码段之后，使用 `C-j` 执行光标前的 elisp 代码。

2. 将光标移动到要执行的代码段之后，使用 `C-x C-e` 执行光标前的 elisp 代码。`C-x C-e` 是一个全局的快捷键，所以不需要进入 `lisp-interaction-mode`。

## 函数

### 定义函数

```elisp
(defun function-name (arguments-list)
	"document string"
	body)
```

每个函数都有一个返回值，一般是函数定义中最后一个表达式的值。

在 Emacs 中，当光标放置在一个函数上的时候，可以使用 `C-h f` 查看这个函数的文档，也就是上面函数定义中的 `document string`。

### 使用函数

要使用一个函数，普通的方式是

```elisp
(function-name arguments-list)
```

## 变量

### 定义变量

```elisp
(setq foo "foo string")
(message foo)
```

在 Emacs 中，当光标放在一个变量上时，可以使用 `C-h v` 查看这个变量的文档。

```elisp
(defvar variable-name value
	"document string")
```

`defvar` 表达式也可以用来声明一个变量。它与 `setq` 的区别在于如果变量在声明之前已经有了一个值的话，用 `defvar` 声明的变量的值不会改变成声明中的值，以及 `defvar` 可以为变量提供文档字符串。

## 定义局部作用域的变量

使用 `let` 和 `let*` 进行局部变量的绑定。

```elisp
(let (bindings)
	body)
```

`bindings` 可以是类似 `(var value)` 这样对 `var` 赋初始值的形式。

```elisp
(defun circle-area (radix)
	(let ((pi 3.14)
		area)
		(setq area (* pi radix radix))
		(message "直径为 %.2f 的圆面积为 %.2f" radix area)))
(circle-area 3)
```

`let*` 和 `let` 的使用形式完全一致，唯一的区别在于 `let*` 声明中可以使用前面声明的变量。

```elisp
(defun circle-area (radix)
	(let* ((pi 3.14)
		   (area (* pi radix radix)))
	(message "直径为 %.2f 的圆面积为 %.2f" radix area)))
(circle-area 3)
```

## lambda 表达式

lambda 表达式的格式

```elisp
(lambda (arguments-list)
	"document string"
	body)
```

直接使用 lambda 表达式

```elisp
(funcall (lambda (name)
	(message "hello %s" name)) "Emacser")
```

将 lambda 表达式赋值给变量，然后用 `funcall` 调用

```elisp
(setq foo (lambda (name)
	        (message "hello %s" name)))
(funcall foo "Emacser")
```

## 控制结构

### 顺序执行

使用 `progn` 来顺序执行多个表达式

```elisp
(progn A B C ...)
```

```elisp
(progn
	(setq foo 3)
	(message "foo = %s" foo))
```

### 条件判断

elisp 有两种条件判断表达式，`if` 和 `cond`。

```elisp
(if condition
	then
	else)
	
(cond (case1 do-when-case1)
	  (case2 do-when-case2)
	  (t do-when-none-meet))
```

例子如下

```elisp
(defun my-max (a b)
	(if (> a b)
		a
		b))
(my-max 3 4)
```

```elisp
(defun fib (n)
	(cond ((= n 0) 0)
	      ((= n 1) 1)
		  (t (+ (fib (- n 1))
			    (fib (- n 2))))))
(fib 10)
```

### 循环

循环使用 `while` 表达式，格式如下。

```elisp
(while condition
	body)
```

```elisp
(defun factorial (n)
	(let ((res 1))
		(while (> n 1)
			(setq res (* res n)
				  n (- n 1)))
			res))
(factorial 10)
```

### 逻辑运算

使用 `and` `or` `not` 进行逻辑运算，`and` `or` 具有短路性质。

```elisp
(defun hello-world (&optional name)
	(or name (setq name "Emacser"))
	(message "hello %s" name))
(hello-world)
(hello-world "Carl")
```

```elisp
(defun square-number-p (n)
	(and (>= n 0)
		 (= (/ n (sqrt n)) (sqrt n))))
(square-number-p -1)
(square-number-p 25)
```

## 数据类型：数字

elisp 的数字类型有两种，整数和浮点数。

整数的范围可以从 `most-positive-fixnum` 和 `most-negative-fixnum` 两个变量得到。

### 测试函数

可以通过如下函数来测试其参数是否是某个数字类型。

```elisp
(integerp 1)  ; 测试整数
(floatp 1.1)  ; 测试浮点数
(numberp 1)   ; 测试数字类型
(zerop 1)     ; 测试是否是 0
(wholenump 1) ; 测试非负整数
(eql 1.0 1)   ; 测试两个参数是否类型相同且值相同
```

### 数字的转换

- `folat` 整数向浮点数转换
- `truncate` 浮点数转换成靠近 0 的整数
- `floor` 浮点数向下取整
- `ceiling` 浮点数向上取整
- `round` 四舍五入取整

## 数据类型：字符和字符串

elisp 种的字符串是字符数组，但是 elisp 的字符串可以包含任何字符，包括 `\0`。

构造字符串的字符其实是一个个整数。字符的读入语法是在字符前加一个问号，例如 `?A` 代表字符 `A`。

```elisp
?A  ; 65
?a  ; 97
```

对于特殊符号，可以使用相同的语法，但是对于有歧义的字符需要加上转义字符 `\`。

```elisp
?\a => 7                 ; control-g, `C-g'
?\b => 8                 ; backspace, <BS>, `C-h'
?\t => 9                 ; tab, <TAB>, `C-i'
?\n => 10                ; newline, `C-j'
?\v => 11                ; vertical tab, `C-k'
?\f => 12                ; formfeed character, `C-l'
?\r => 13                ; carriage return, <RET>, `C-m'
?\e => 27                ; escape character, <ESC>, `C-['
?\s => 32                ; space character, <SPC>
?\\ => 92                ; backslash character, `\'
?\d => 127               ; delete character, <DEL>
```

控制字符可以有多种表示方式，如下都表示 `C-i`。

```elisp
?\^I
?\^i
?\C-I
?\C-i
```

Meta 字符格式

Meta 字符就是将它修饰的字符的第 27 个二进制位由 0 变为 1。

```elisp
?\M-A
(logior (lsh 1 27) ?A) ; A 第27位由 0 改成 1
```

其他修饰字符原理类似。

### 测试函数

```elisp
(stringp "hello") ; 测试字符串
```

实现判断字符串是否为空的函数

```elisp
(defun string-empty-p (str)
	(not (string< "" str)))
(string-empty-p "")
(string-empty-p "hello")
```

### 构造字符串

构造一个字符串可以使用 `make-string`,生成的字符串种包含的字符都是一样的，使用 `string` 可以构造包含不同字符的字符串。

`concat` 字符可以用来连接字符串。

```elisp
(make-string 5 ?x)
(string ?a ?b ?c)
(concat "abc" "def")
```

### 字符串比较函数

```elisp
(char-equal ?A ?A) ; 比较字符
(string= "hello" "hello") ; 比较字符串
(string-equal "hello" "hi") ; 比较字符串，string= 的别名
(string< "hi" "hello") ; 按字典序比较两个字符串
```

### 转换函数

```elisp
(char-to-string ?A) ; 字符转换为字符串
(string-to-char "hello") ; 字符串转换为字符，只返回字符串的第一个字符
(string-to-number "A" 16) ; 字符串转换为数字，第三个参数指定输入字符串的进制
(number-to-string 100) ; 数字转换为字符串，只能转换为 10进制的数字
(format "%#o" 256) ; 数字转换为 8 进制字符串
(format "%#x" 256) ; 数字转换为 16 进制字符串
(concat '(?a ?b ?c)) ; 字符列表转换成字符串
(concat [?a ?b ?c])  ; 字符向量转换成字符串
(vconcat "abc")      ; 把一个字符串转换成一个向量
(append "abc" nil)   ; 把一个字符串转换成一个列表
(downcase "HELLO")   ; 将字符或字符串变为小写
(upcase "hello")     ; 将字符或字符串变为大写
(capitalize "hello world") ; 将字符串每个单词首字母大写
(upcase-initials "hello world") ; 将字符串或字符首字母大写
```

### 查找和替换

```elisp
(string-match "23" "012345" 1) ; 从指定的位置对字符串进行正则匹配，返回匹配的起点位置
```

`string-match` 的第一个参数是一个正则表达式，如果需要查找在正则表达式中有特殊含义的字符串，可以先用 `regexp-quote` 进行处理。

```elisp
(string-match "2*" "132*456") ; => 0
(string-match (regexp-quote "2*") "132*456") ; => 2
```

`string-match` 在查找匹配的字符串的时候，会记录下每个要捕捉的字符串的位置，这个位置可以在匹配后使用 `match-data` `match-beginning` `match-end` 来获得。

```elisp
(progn
	(string-match "abc" "abcabcabc")
	(match-data)) ; => (0 3)
```

上面的代码段即返回 `abc` 第一次出现在 `abcabcabc` 中的起始位置的结束位置。

```elisp
(let ((start 0))
	(while (string-match "abc" "abcabcabc" start)
		(princ (format "find at %s\n" (match-data)))
		(setq start (match-end 0))))
```

上面的代码打印 `abc` 的所有出现位置。

字符串的替换使用 `replace-match` 函数。

```elisp
(let ((str "abcabcabc"))
	(string-match "a" str)
	(princ (replace-match "xy" nil nil str 0)))
```

上面的代码段打印 `xybcabcabc`。`replace-match` 返回替换后的新字符串，不修改原字符串。

## 数据类型：cons cell 和列表

[Lists and Cons Cells](https://www.gnu.org/software/emacs/manual/html_node/elisp/Cons-Cells.html)

cons cell 的读入语法是用 `.` 分开两个部分。

```elisp
'(1 . 2)
'(1 . "hello")
```

`eval-last-sexp` 函数包含两个步骤，第一个步骤是读入前一个 S 表达式，第二个步骤是对读入的表达式进行求值。如果读入的 S 表达式时一个 cons cell 的话，求职的时候就会把 cons cell 的第一个元素作为一个函数来调用。上面写的两个 cons cell 的第一个元素都不是函数，如果调用的话就会出错，所以我们需要告诉 elisp 这件事，于是就在 cons cell 前加上一个 `'` 符号，表示这是一类特殊的 S 表达式，它们求值前和求值前是相同的，称为自求值表达式(self evaluating form)。`'` 是一个特殊的函数 `quote`，它的作用是将它的参数返回。`'(1 . 2)` 等价于 `(quote (1 . 2))`。

按列表类型最后一个 cons cell 的 `cdr` 部分的类型来进行分类，可以将列表分为 3 类。如果为 `nil`，这个列表被称为真列表(true list)。如果既不是 `nil` 也不是 cons cell，则称为点列表(dotted list)，如果它指向列表中其他的 cons cell，则称为环形列表(circular list)。

```elisp
'(1 2 3)
'(1 2 . 3)
'(1 . #1=(2 3 . #1#))
```

空表(`nil`, `'()`) 不是一个 cons cell，因为它没有 car 和 cdr 部分，为了程序上的方便，可以认为 nil 的 car 和 cdr 都是 nil。

```elisp
nil       ; => nil
'()       ; => nil
(car '()) ; => nil
(cdr '()) ; => nil
```

### 构造函数

使用 `cons` 函数生成一个 cons cell。

```elisp
(cons 1 2)

(setq foo '(a b))
(cons 'x foo)
```

使用 `list` 函数生成一个列表。

```elisp
(list 1 2 3)
```

### 测试函数

```elisp
(consp '(1 . 2)) ; 测试一个对象是否是 cons cell
(listp '(1 . 2)) ; 测试一个对象是否是 list
(null '())       ; 测试一个对象是否是 nil
```

### 访问列表

```elisp
(nth 3 '(0 1 2 3 4 5)) ; 访问列表下标为 3 的元素
(nthcdr 2 '(0 1 2 3 4)) ; 返回列表下标为 2 处及之后的元素
(last '(0 1 2 3 4) 2)   ; 返回末尾 2 个元素组成的列表
(butlast '(0 1 2 3 4) 2) ; 返回除了末尾 2 个元素之外其他元素组成的列表
```

### 修改 cons cell

`setcar` 和 `setcdr` 函数可以修改一个 cons cell 的 car 和 cdr 部分。

```elisp
(setq foo '(a b c))
(setcar foo 'x)
foo  ; => (x b c)
(setcdr foo '(y z))
foo  ; => (x y z)
```

`push` 和 `pop` 函数可以往列表头部插入和删除元素。

```elisp
(setq foo nil)
(push 'a foo) ; => (a)
(pop foo)     ; => a
```

`reverse` 函数返回一个逆序的列表，不修改原列表。`nreverse` 也返回一个逆序的列表，但是它修改原列表。 

```elisp
(setq foo '(a b c))
(reverse foo)  ; => (c b a)
(nreverse foo) ; => (c b a)
foo            ; => (a)
```

最后一句 `foo` 返回 `(a)` 的原因和 C 语言里面的列表是一样的。`foo` 只是指向原列表 `(a b c)` 的第一个元素，原列表反序后，如果 `foo` 还是指向 `a`，返回的自然是 `(a)`。

### 遍历列表

遍历列表常用的是 `mapc` 和 `mapcar` 函数，这两个函数的第一个参数是一个函数，第二个参数是一个列表。每次处理一个列表中的元素，差别在于，`mapc` 返回的还是输入的列表，`mapcar` 返回的是经过函数计算的结果。

```elisp
(setq foo '(1 2 3))
(mapc '1+ foo)    ; => (1 2 3)
foo               ; => (1 2 3)
(mapcar '1+ foo)  ; => (2 3 4)
foo               ; => (1 2 3)
```

另一个常用的函数是 `dolist`。格式如下

```elisp
(dolist (var list [result]) body)
```

其中 `var` 是一个局部变量，用来在 `body` 部分·1获得正在遍历的列表元素。

```elisp
(setq bar nil)
(dolist (val '(1 2 3) bar)
	(push (+ 1 val) bar))   ; => (4 3 2)
```

### 分割合并字符串

`split-string` 把字符串按分隔符分解，`mapconcat` 将多个字符串用分隔符连接起来。

```elisp
(split-string "key=value" "\\s-*=\\s-*") ; => ("key" "value")
(mapconcat 'identity '("a" "b" "c") "-") ; => “a-b-c”
```

`identity` 是一个特殊的函数，会直接返回参数。`mapconcat` 函数需要第一个参数是一个函数，所以我们这里使用 `identity` 来避免额外的操作。

## 数据类型：数组和序列

数组的特性

- 数组内的元素可以在常数时间内访问，可以用 `aref` 来访问，用 `aset` 来设置
- 数组在创建之后就无法改变长度
- 数组是自求值的

vector 可以看成一种通用的数组，它的元素可以是任意的对象。

### 测试函数

```elisp
(sequencep '(a b)) ; 测试一个对象是否是一个序列
(arrayp [1 2 3])   ; 测试一个对象是否是一个数组
(vectorp [1 2 3])  ; 测试一个对象是否是一个向量
```

### 数组操作

使用 `vector` 函数创建向量。

```elisp
(vector 'foo 23 [bar baz] "hello")
```

使用 `make-vector` 生成元素相同的向量。

```elisp
(make-vector 5 'a) ; => [a a a a a]
```

使用 `fillarray` 将整个数组用相同元素填充。

```elisp
(fillarray (make-vector 3 'a) 'z) ; => [z z z]
```

使用 `vconcat` 将多个真列表连接成一个向量。

```elisp
(vconcat [a b c] "aa" '(foo (1 2))) ; => [a b c 97 97 foo (1 2)]
```

## 数据类型：符号

符号是有名字的对象，类似于 C 语言中的指针，通过符号可以得到和这个对象关联的信息。

符号的命名规则是可以使用任何字符，如果有需要，可以在名字前加上 `\` 表示符号。

```elisp
(symbolp '+1)      ; => nil
(symbolp '\+1)     ; => t
(symbol-name '\+1) ; "+1"
```

## 求值规则



## 变量

elisp 中有两种变量，全局变量和 let 绑定的局部变量。当一个变量名即是局部变量又是全局变量，或者用 let 进行了多层绑定，在使用变量名是，指代的是最里层的变量，而不影响外层的同名变量。

局部变量的绑定不能超过一定的层数，限制层数的变量由 `max-specpdl-size` 定义。

### buffer-local 变量

Emacs 的一种特殊的局部变量。

声明一个 buffer-local 变量可以使用 `make-variable-buffer-local` 或者 `make-local-variable`。这两个函数的区别在于前者是在所有 buffer 中申明一个 buffer-local 变量，后者只是在当前 buffer 中声明一个 buffer-local 变量。

如果一个变量时 buffer-local 变量，那么在这个缓冲区中使用 `setq` 就只能改变这个缓冲区里这个变量的值。`setq-default` 可以修改全局变量符号的值，而不会修改到当前 buffer 中同名的 buffer-local 变量的值。

```elisp
(with-current-buffer buffer body)
```

其中 `buffer` 可以是一个缓冲区对象，也可以是一个缓冲区的名字。这个函数的作用是使 `body` 中的表达式在指定的缓冲区中执行。

```elisp
(get-buffer buffer-name)
```

使用缓冲区名字获取缓冲区对象。

```elisp
(with-current-buffer "*Message*"
	(buffer-local-value 'foo (get-buffer "*scratch*")))
```

在 `*Meaasge*` buffer 中获取 `*scratch*` buffer 中的 buffer-local 变量 `foo` 的值。`buffer-local-value` 函数用来在当前缓冲区中获取其他缓冲区中的 buffer-local 变量。

### 测试函数

测试一个变量是不是 buffer-local 变量可以使用 `local-variable-p`。

```elisp
(local-variable-p 'foo)     ; => nil
(make-local-variable 'foo)
(local-variable-p 'foo)     ; => t
```

### 变量的作用域

elisp 的变量作用域是动态作用域。所以一个符号在使用之前可能为空。可以使用 `boundp` 来测试一个变量是否有定义。对于一个 buffer-local 变量，它的缺省值可能没有定义，直接使用会出错，可以先用 `default-boundp` 进行测试。使一个变量的值变为空，可以使用 `makunbound`，消除一个 buffer-local 变量，可以使用 `kill-local-variable`。消除所有 buffer-local 变量可以使用 `kill-all-local-variables`，但是有属性的 permanent-local 不会消除。

```elisp
(make-local-variable 'foo)
(setq foo "local variable")
foo
(boundp 'foo)
(default-boundp 'foo)
(makunbound 'foo)
foo
(kill-local-variable 'foo)
```

### 常见变量命名规则

- hook                一个在特定情况下调用的函数列表，比如关闭缓冲区时，进入某个模式时
- function            值为一个函数
- functions           值为一个函数列表
- flag                值为 nil 或 non-nil
- predicate           值是一个作判断的函数，返回 nil 或 non-nil
- program 或 -command 一个程序或 shell 命令名
- form                一个表达式
- forms               一个表达式列表。
- map                 一个按键映射(keymap)

## 函数和命令

参数列表的语法

```elisp
(required-vars...
	[&optional optional-vars...]
	[&rest rest-vars])
```

把必须提供的参数放在前面，可选的参数放在后面，最后用一个符号表示剩余的所有参数。

```elisp
(defun foo (var1 var2 &optional opt1 opt2 &rest rest)
	(list var1 var2 opt1 opt2 rest))
	
(foo 1 2)         ; => (1 2 nil nil nil)
(foo 1 2 3)       ; => (1 2 3 nil nil)
(foo 1 2 3 4 5 6) ; => (1 2 3 4 (5 6))
```

从上面的例子可以看出，当调用函数时如果没有提供可选参数，则可选参数为 nil，当没有提供剩余参数时，剩余参数也为 nil，如果提供了剩余参数，剩余参数表现为列表的形式。

### 调用函数

函数调用一般使用 `funcall` 和 `apply` 函数。这两个函数都是将第一个参数作为要调用的函数名，其余参数作为函数参数。区别在于 `funcall` 直接将其余参数传入要调用的函数，而 `apply` 的最后一个参数是作为列表，会将列表进行一次平铺(将列表解为多个参数)后再传给函数。

```elisp
(funcall 'list 'x '(y) '(a b)) ; => (x (y) (a b))
(apply 'list 'x '(y) '(a b))   ; => (x (y) a b)
```

### 宏

传给宏的参数会出现在最后拓展后的表达式中，所以可能会出现副作用，例子如下。可以使用 `macroexpand` 函数来看宏拓展后代码。

```elisp
(defmacro foo (arg)
	(require 'cl) ; to import incl function
	(list 'message "%d %d" arg arg))
	
(defun bar (arg)
	(message "%d %d" arg arg))
	
(let ((i 1))
	(bar (+ 1 i))) ; => "2 2"
	
(let ((i 1))
	(foo (incf i))) ; => "2 3"

(macroexpand '(foo (incf i))) ; => (message "%d %d" (incf i) (incf i))
```

### 命令

elisp 编写的命令都含有一个 `interactive` 表达式，用来指明这个命令的参数。

```elisp
(defun hello (name)
	(interactive "sWhat's your name:")
	(message "hello, %s" name))
```

`interactive` 表达式的参数的第一个字符 `s` 叫做代码字符，表示参数是一个字符串。如果命令有多个参数，可以使用换行符将多个提示字符串分开。

```elisp
(defun hello (name age)
	(interactive "sWhat's your name: \nnWhat's your age:")
	(message "hello, %d years old's %s" age name))
```
其他的代码字符可以通过 `C-h f` 查看。

## 操作对象：缓冲区

缓冲区是用来保存文本的对象。通常缓冲区和文件关联，但是也有些缓冲去没有对应的文件，Emacs 可以同事打开多个文件，同时存在多个缓冲区，但是只有一个缓冲区被称为当前缓冲区。

可以用 `buffer-name` 函数获得缓冲区对象的名字，如果不指定参数，则返回当前缓冲区的名字。可以用 `rename-buffer` 对缓冲区重命名，如果指定的名字与当前存在的缓冲区名字冲突，则会产生一个错误。也可以用 `generate-new-buffer-name` 来产生一个唯一的缓冲区名。

### 当前缓冲区

当前缓冲去不一定是光标所在的那个缓冲区，可以用 `set-buffer` 来指定当前缓冲区。但是需要注意，当返回到命令循环时，光标所在的缓冲区会自动成为当前缓冲区。可以参考下面这个例子。

```elisp
(set-buffer "*Messages*")
(message (buffer-name))  ;=> not *Messages* buffer

(progn
	(set-buffer "*Messages*")
	(message (buffer-name))) ; => *Messages* buffer
```

但是我们在编写 elisp 代码的时候，最好不要使用 `set-buffer` 来设置 current-buffer，因为 `set-buffer` 不能处理错误或退出情况。正确的做法是使用 `save-current-buffer` `with-current-buffer` `save-excursion` 等方法。`save-current-buffer` 的作用是保存当前缓冲区，执行其中的表达式，最后恢复为原来的缓冲区，如果原来的缓冲区被关闭了，则使用最后一次被设置为当前缓冲区的缓冲区。elisp 中很多以 `with` 开头的宏都是在不改变当前状态的情况下，临时用另一个变量代替现有变量执行语句。

```elisp
(with-current-buffer BUFFER-OR-NAME
	body)
```

相当于

```elisp
(save-current-buffer
	(set-buffer BUFFER-OR-NAME)
	body)
```

`save-excursion` 与 `save-current-buffer` 不同之处在于，它不仅保存当前缓冲区，还保存了当前的位置和 mark。

### 创建和关闭缓冲区

`get-buffer-create` 参数为一个表示缓冲区的名字，如果这个缓冲区已经存在，则返回这个缓冲区对象，否则新建一个缓冲区。

`generate-new-buffer` 参数为一个表示缓冲区的名字，如果这个缓冲区已经存在，则使用名字加一个后缀 n(n 为整数，从 2 开始) 的新名字创建一个新缓冲区。

`kill-buffer` 关闭一个缓冲区，如果要用户确认，可以加到 `kill-buffer-query-functions` 中，如果需要执行关联操作，可以使用 `kill-buffer-hook`。

`buffer-live-p` 检查一个缓冲区是否存在。

`buffer-list` 获取包含所有缓冲区的列表。

`with-temp-buffer` 使用一个临时缓冲区。

### 在缓冲区中移动

位置(position) 和标记(marker) 的概念。

位置是指某个字符在缓冲区中的下标，从 1 开始。标记和位置的区别在于位置会随文本插入和删除而改变位置。一个标记包含了缓冲区和位置两个信息。在插入和删除缓冲区里的文本时，所有的标记都会检查一遍，并重新设置位置。这对于含有大量标记的缓冲区处理是很花时间的，所以当你确认某个标记不用的话应该释放这个标记。

`make-marker` 创建标记，创建的标记不指向任何位置，需要使用 `set-market` 来设置标记的缓冲区和位置。

`point-marker` 得到 point 处的标记，point 是当前缓冲区中光标所在位置的标记。

`copy-marker` 复制或产生一个标记。

```elisp
(setq foo (make-marker))
(set-marker foo (point))

(copy-marker 20)
(copy-marker foo)
```

`marker-position` `marker-buffer` 得到一个 mark 的位置以及缓冲区信息。

``` elisp
(marker-position (point-marker))
(marker-buffer (point-marker))
```

和 point 类似，有一个特殊的标记称为 "the mark"。它指定了一个区域的文本用于某些命令，比如  `kill-region`，`indent-region`。可以用 `mark` 函数返回当前 mark 的值。如果使用  `transient-mark-mode`，而且 `mark-even-if-inactive` 值是 `nil` 的话，在 mark 没有激活时（也就是  `mark-active` 的值为 `nil`），调用 `mark` 函数会产生一个错误。如果传递一个参数 `force` 才能返回当前缓冲区 mark 的位置。`mark-marker` 能返回当前缓冲区的 mark，这不是 mark 的拷贝，所以设置它的值会改变当前 mark 的值。`set-mark` 可以设置 mark 的值，并激活 mark。每个缓冲区还维护一个 `mark-ring`，这个列表里保存了 mark 的前一个值。当一个命令修改了 mark 的值时，通常要把旧的值放到 `mark-ring` 里。可以用 `push-mark` 和 `pop-mark` 加入或删除 `mark-ring` 里的元素。当缓冲区里 mark 存在且指向某个位置时，可以用 `region-beginning` 和 `region-end` 得到 point 和 mark 中较小的和较大的值。当然如果使用 `transient-mark-mode` 时，需要激活 mark，否则会产生一个错误。

按单个字符位置来移动的函数主要使用 `goto-char` 和 `forward-char`、`backward-char`。前者是按缓冲区的绝对位置移动，而后者是按 point 的偏移位置移动。

```elisp
(goto-char (point-min)) ; 光标跳到缓冲区开始位置

(forward-char 10)       ; 光标向前移动 10 个字符
(backward-char 10)      ; 光标向后移动 10 个字符

(forward-word 1)        ; 光标向前移动 1 个单词
(backward-word 1)       ; 光标向后移动 1 个单词

(forward-line 1)        ; 光标向下移动 1 行，移动到下一行的行首
(forward-line 0)        ; 光标移动到当前行的行首

(line-beginning-position) ; 得到行首位置
(line-end-position)       ; 得到行尾位置
(line-number-at-pos)      ; 得到当前行的行号
```

### 获取缓冲区的内容

```elisp
(buffer-string)              ; 获取当前缓冲区的内容
(buffer-substring START END) ; 获取当前缓冲区一个区域内的文本
```

### 修改缓冲区的内容

- `insert` 插入一个或多个字符串到当前缓冲区的 point 后面
- `insert-char` 插入单个字符到当前缓冲区的 point 后面
- `insert-buffer-substring` 插入内容到另一个缓冲区
- `delete-char` 删除 point 后的一个或多个字符
- `delete-backward-char` 删除 poing 前的一个或多个字符
- ` delete-region` 删除一个区间
- `delete-and-extract-region` 删除一个区间并返回被删除的区间
- `re-search-forward` 向后查找内容
- `re-search-backward` 向前查找内容

## 操作对象：窗口

Window 是屏幕中用来显示一个缓冲区的部分。Frame 是 Emacs 能够使用的屏幕的部分。Emacs 可以有多个 Frame，每个 Frame 中可以容纳多个 Window。

### 分割窗口

```elisp
(split-window &optional window size horizontal)
```
`split-window` 函数的功能是将指定窗口进行分割，分割后的两个窗口里的缓冲区是同一个缓冲区，使用这个函数后，光标仍然在原窗口，函数返回新窗口对象。

### 删除窗口

删除窗口使用 `delete-window` 函数，默认删除当前选中的窗口，如果要删除除了当前窗口之外的其他窗口，可以使用 `delete-other-windows`。

### 配置窗口

窗口配置(window configuration) 包含了 frame 中所有窗口的位置信息：窗口 大小，显示的缓冲区，缓冲区中光标的位置和 mark，还有 fringe，滚动条等等。 用 `current-window-configuration` 得到当前窗口配置，用 `set-window-configuration` 来设置。

### 选择窗口

使用 `selected-window` 来获取当前被选中的窗口。使用 `select-window` 来选中某个窗口。

`save-selected-window` 和 `with-selected-window` 两个宏可以不修改当前窗口执行语句。它们的作用是在执行语句结束后选择的窗口仍留在执行 语句之前的窗口。`with-selected-window` 和 `save-selected-window` 几乎相同， 只不过 `save-selected-window` 选择了其它窗口。这两个宏不会保存窗口的位置信息，如果执行语句结束后，保存的窗口已经消失，则会选择z之前最后一个被选中的窗口。

```elisp
(save-selected-window
	(select-window (next-window))
	(goto-char (point-min))) ; 让另一个窗口光标移动到缓冲区开头
```

当前 frame 中的所有窗口可以通过 `window-list` 得到。可以用 `next-window` 来得到 `window-list` 中排在某个 window 后面的 window，用 `previous-window` 得到排在某个 window 之前的 window。`walk-window` 可以遍历窗口，`get-window-with-predicate` 可以查找符合某个条件的 window。

### 窗口大小信息

窗口的高表示窗口可以容纳的行数，窗口的宽指每一行可以容纳的字符数。mode line 和 header line 包含在窗口的高度中，所以有 `window-height` 和 `window-body-height` 用来获取包含即不包含 mode line/header line 的窗口高度。

`window-width` 返回窗口的宽度。`window-edges` 返回窗口各个顶点的坐标信息。`window-inside-edges` 返回窗口的文本区域的各个顶点的坐标信息。

### 窗口对应的缓冲区

`window-buffer` 用来获取窗口对应的缓冲区。`get-buffer-window` 用来获取缓冲区对应的窗口，如果多个窗口显示同一个缓冲区，则只返回其中的一个，如果要得到所有显示该缓冲区的窗口，使用 `get-buffer-window-list`。

`set-window-buffer` 用来让某个窗口i希纳是某个缓冲区。`switch-to-buffer` 让被选中的窗口显示某个缓冲区。`set-buffer` 让某个缓冲区成为当前缓冲区。

让一个缓冲区可见可以用 `display-buffer`。默认的行为是当缓冲区已经显示在某 个窗口中时，如果不是当前选中窗口，则返回那个窗口，如果是当前选中窗口， 且如果传递的 `not-this-window` 参数为 `non-nil` 时，会新建一个窗口，显示缓 冲区。如果没有任何窗口显示这个缓冲区，则新建一个窗口显示缓冲区，并返回这个窗口。

### 改变窗口显示区域

每个窗口会保存一个显示缓冲区的起点位置，这个位置对应于窗口左上角光标在 缓冲区里的位置。可以用 `window-start` 函数得到某个窗口的起点位置。可以通过 `set-window-start` 来改变显示起点位置。可以通过 `pos-visible-in-window-p` 来检测缓冲区中某个位置是否是可见的。 但是直接通过 `set-window-start` 来控制显示比较容易出现错误，因为 `set-window-start` 并不会改变 point 所在的位置，在窗口调用 `redisplay` 函数之后 point 会跳到相应的位置。如果你确实有这个需要，建议还是用 `(with-selected-window window (goto-char pos))` 来代替。

## 操作对象：文件
