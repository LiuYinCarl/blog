# OCaml 的一些特殊函数

这篇文章记录一下 OCaml 中一些特殊函数的使用，因为这些函数在其他命令式语言中不太常见，所以容易不理解。

## @@

这个函数被定义在标准库中，是 `Stdlib.(@@)`。叫做 Application operator，是右结合运算符。`g @@ f @@ x` 等价于 `g (f (x))`。

```ocaml
let func1 x =
  x * 2

let func2 x =
  x + 5

let () =
  let res = func2 @@ func1 @@ 3 in
  print_int res;
  print_endline ""

(* 打印 11 *)
```

> https://ocaml.org/manual/5.1/api/Stdlib.html#VAL(@@)

## |>

这个函数也被定义在标准库中，是 `Stdlib.(|>)`。叫做 `Reverse-application operator`，是左结合运算符。 `x |> f |> g` 等价于 `g (f (x))`。

```ocaml
let func1 x =
  x * 2

let func2 x =
  x + 5

let () =
  let res = 3 |> func1 |> func2 in
  print_int res;
  print_endline ""
  
(* 打印 11 *)
```

> https://ocaml.org/manual/5.1/api/Stdlib.html#VAL(|%3E)