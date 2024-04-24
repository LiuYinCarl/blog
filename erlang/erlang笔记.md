## 在 erlang shell 中编译代码

```erlang
c(module_name).
```

## 在 erlang shell 外编译代码

```bash
# 编译
erlc module.erl
# 执行
erl -noshell -s module funcname -s init stop
```

## 管理 shell

无论在任何情况下，都可以按下 Ctrl+G 来中断当前的 shell, 然后对 job 进行管理。

```erlang
--> h % 列出帮助命令
```

## 调用 spawn 的两种形式

```erlang
spawn(Fun).

spawn(MFA). % MFA 表示 mod_name func_name arguments
```

如果代码需要动态升级，需要使用第二种用法，运行中的进程会在模块升级之后调用最新的代码，
如果不考虑函数动态升级，可以使用第一种用法。

## f().

`f()` 命令可以让 erlang shell 清空之前设置的任何绑定，在这个命令之后，所有变量都变成未绑定的。

## 4.7.1 节 关于guard(关卡)语法的设计摘抄

合法的关卡表达式是所有合法 Erlang 表达式的一个子集。之所以限制关卡表达式只能是 Erlang 表达式子集，是想要确保关卡表达式的执行是无副作用的。关卡是模式匹配的一种拓展，而因为模式匹配无副作用，所以我们不希望关卡的执行带有副作用。另外，关卡不能掉用用户定义的函数，因为要确保它们没有副作用并能正常结束。

## 关卡表达式中一些符号的含义
关卡表达式中 `,` 符号表示 `and`, `;` 符号表示 `or`。

## 关卡表达式中 andalso, orelse 操作符的引入原因

允许布尔表达式用于关卡是为了使关卡在语法上类似于其他的表达式。`orelse`, `andalso` 操作符存在的原因是布尔操作符 `and`, `or` 原本的定义是两侧参数都需要求值。

这里我的理解是 `and`, `or` 操作符的语义是设计为先计算操作符两侧的结果，然后再进行 `and`, `or` 运算。这导致 `and`, `or` 不能表达短路操作的含义（操作符左侧计算成功或者失败后不计算右侧表达式），所以才需要引入 `andalso`, `orelse` 操作符。

## 记录与元组的关系

记录其实就是元组。
在 shell 中使用 rf() 函数可以证明这一点。

```erlang
21> X2.
#todo{status = done,who = joe,text = "Fix"}
22> rf(todo).
ok
23> X2.
{todo,done,joe,"Fix"}
```

可以看到，如果使用 rf() 函数取消了 todo 记录的定义，打印 X2 的时候 X2 会表现为一个元组。


## 14.3.2 节的客户端在一个节点，服务器在相同主机的另一个节点的例子在 MacOS 上执行有问题

```erlang
% 服务器
➜  socket_dist git:(main) ✗ erl -sname point1
Erlang/OTP 24 [erts-12.2] [source] [64-bit] [smp:8:8] [ds:8:8:10] [async-threads:1] [dtrace]

Eshell V12.2  (abort with ^G)
(point1@192)1> kvs:start().
true

% 客户端
➜  socket_dist git:(main) ✗ erl -name point2
Erlang/OTP 24 [erts-12.2] [source] [64-bit] [smp:8:8] [ds:8:8:10] [async-threads:1] [dtrace]

Eshell V12.2  (abort with ^G)
(point2@192.168.0.108)1> rpc:call(point1@192, kvs, store, [weather, fine]).
=ERROR REPORT==== 12-Jan-2022::13:46:24.374398 ===
** System running to use fully qualified hostnames **
** Hostname 192 is illegal **

{badrpc,nodedown}
(point2@192.168.0.108)2> rpc:call('point1@192', kvs, store, [weather, fine]).
=ERROR REPORT==== 12-Jan-2022::13:46:34.958235 ===
** System running to use fully qualified hostnames **
** Hostname 192 is illegal **

{badrpc,nodedown}
(point2@192.168.0.108)3> rpc:call('point1@192.168.0.108', kvs, store, [weather, fine]).
{badrpc,nodedown}
```

可以看到客户端无法连接到服务器，错误提示是 HostName 不合法。

为了解决这个问题，不要使用 `erl -sname` 参数，而是改为 `erl -name` 参数。
`sname` 表示的是短名称，`name` 表示的是标准名称。

正确的用法如下。
```erlang
% 服务器
➜  socket_dist git:(main) ✗ erl -name point1
Erlang/OTP 24 [erts-12.2] [source] [64-bit] [smp:8:8] [ds:8:8:10] [async-threads:1] [dtrace]

Eshell V12.2  (abort with ^G)
(point1@192.168.0.108)1> kvs:start().
true

% 客户端
Erlang/OTP 24 [erts-12.2] [source] [64-bit] [smp:8:8] [ds:8:8:10] [async-threads:1] [dtrace]

Eshell V12.2  (abort with ^G)
% IP需要用单引号包起来
(point2@192.168.0.108)1> rpc:call('point1@192.168.0.108', kvs, store, [weather, fine]).
true
```


## code:which(module_name)

该函数可以用来查看模块的绝对路径。在 erlang 标准分发套装里，每个库都有两个子目录。
一个 src 目录包含源代码，一个 ebin 目录包含编译后的 erlang 代码。
