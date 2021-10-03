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


