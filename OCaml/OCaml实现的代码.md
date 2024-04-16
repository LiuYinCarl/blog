# OCaml 实现的代码

### 堆排序算法

```ocaml
(* 辅助打印功能 *)
let cnt = ref 0
let msg = ref ""

let p arr =
  for _ = 0 to !cnt - 1 do
    print_string "    "
  done;
  for i = 0 to Array.length arr - 1 do
    print_int arr.(i);
    print_string " ";
  done;
  if !msg <> ""
  then (
    print_endline (" " ^ !msg);
    msg := ""
  )
  else print_endline ""


(* 交换 Array 的两个成员 *)
let swap arr i j =
  let tmp = arr.(i) in
  arr.(i) <- arr.(j);
  arr.(j) <- tmp

(* 整理堆 *)
let rec heapify arr root left right =
  p arr;
  cnt := !cnt + 1;
  let rela_root = root - left in
  let lc = (2 * rela_root) + left + 1 in
  let rc = (2 * rela_root) + left + 2 in
  let largest =
    if lc <= right && arr.(lc) > arr.(root)
    then lc
    else root
  in
  let largest =
    if rc <= right && arr.(rc) > arr.(largest)
    then rc
    else largest
  in
  if largest <> root
  then (
    msg := Printf.sprintf "swap %d(%d) %d(%d)"
             root arr.(root) largest arr.(largest) ;
    swap arr root largest;
    heapify arr largest left right;
  );
  cnt := !cnt - 1;
  p arr

let build_heap arr left right =
  print_endline "\n==== build heap start =====";

  for i = (left + right) / 2 downto left do
    heapify arr i left right
  done;

  print_endline "==== build heap finish ====="

(* 堆排序函数 *)
let sort arr left right =
  build_heap arr left right;
  for i = right downto left + 1 do
    msg := Printf.sprintf "sort swap %d(%d) %d(%d)"
             left arr.(left) i arr.(i);
    swap arr left i;
    heapify arr left left (i-1);
  done

let () =
  let arr = [|5;4;3;2;1;|] in
  sort arr 0 (Array.length arr - 1);

  let arr = [|1;2;3;4;5;|] in
  sort arr 0 (Array.length arr - 1);
```

输出结果如下:

```txt
==== build heap start =====
5 4 3 2 1
5 4 3 2 1
5 4 3 2 1
5 4 3 2 1
5 4 3 2 1
5 4 3 2 1
==== build heap finish =====
1 4 3 2 5  sort swap 0(5) 4(1)
    4 1 3 2 5  swap 0(1) 1(4)
        4 2 3 1 5  swap 1(1) 3(2)
        4 2 3 1 5
    4 2 3 1 5
4 2 3 1 5
1 2 3 4 5  sort swap 0(4) 3(1)
    3 2 1 4 5  swap 0(1) 2(3)
    3 2 1 4 5
3 2 1 4 5
1 2 3 4 5  sort swap 0(3) 2(1)
    2 1 3 4 5  swap 0(1) 1(2)
    2 1 3 4 5
2 1 3 4 5
1 2 3 4 5  sort swap 0(2) 1(1)
1 2 3 4 5

==== build heap start =====
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
    1 5 3 4 2  swap 1(2) 4(5)
    1 5 3 4 2
1 5 3 4 2
1 5 3 4 2
    5 1 3 4 2  swap 0(1) 1(5)
        5 4 3 1 2  swap 1(1) 3(4)
        5 4 3 1 2
    5 4 3 1 2
5 4 3 1 2
==== build heap finish =====
2 4 3 1 5  sort swap 0(5) 4(2)
    4 2 3 1 5  swap 0(2) 1(4)
    4 2 3 1 5
4 2 3 1 5
1 2 3 4 5  sort swap 0(4) 3(1)
    3 2 1 4 5  swap 0(1) 2(3)
    3 2 1 4 5
3 2 1 4 5
1 2 3 4 5  sort swap 0(3) 2(1)
    2 1 3 4 5  swap 0(1) 1(2)
    2 1 3 4 5
2 1 3 4 5
1 2 3 4 5  sort swap 0(2) 1(1)
1 2 3 4 5
```