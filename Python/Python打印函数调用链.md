# Python 打印函数调用链

最近在看 cython 项目，发现一个比较有意思的调试函数。这个函数的位置在 [Cython/Debugging.py](https://github.com/cython/cython/blob/master/Cython/Debugging.py)。函数内容如下：

```python
def print_call_chain(*args):
    import sys
    print(" ".join(map(str, args)))
    # 获取调用栈的上一帧
    f = sys._getframe(1)
    while f:
        # 获取 caller 的函数名字
        name = f.f_code.co_name
        # 检查 caller 是否有 self 参数
        s = f.f_locals.get('self', None)
        if s:
            # 如果 caller 有 self 参数，那么 caller 就是一个类方法
            # 获取它的类名
            c = getattr(s, "__class__", None)
            if c:
                name = "%s.%s" % (c.__name__, name)
        # 打印 caller 的 [类名.]函数名
        print("Called from: %s %s" % (name, f.f_lineno))
        # 继续获取调用链的上一层
        f = f.f_back
    print("-" * 70)
```

实现的逻辑很简单，注释中进行了说明，这个相比于标准库的 `traceback.print_stack()` 函数，增加了类名的展示，去掉了文件名信息，对于整理调用链，更加清爽一些。看一下实际的使用效果。以 ipython 为例，看一下它的调用栈。

```ipython
In [2]: print_call_chain()

Called from: <module> 1
Called from: TerminalInteractiveShell.run_code 3577
Called from: TerminalInteractiveShell.run_ast_nodes 3517
Called from: TerminalInteractiveShell.run_cell_async 3334
Called from: _pseudo_sync_runner 129
Called from: TerminalInteractiveShell._run_cell 3130
Called from: TerminalInteractiveShell.run_cell 3075
Called from: TerminalInteractiveShell.interact 904
Called from: TerminalInteractiveShell.mainloop 911
Called from: TerminalIPythonApp.start 317
Called from: launch_instance 1075
Called from: start_ipython 130
Called from: <module> 8
----------------------------------------------------------------------
```

这个结果和堆栈的展示顺序一样，被调用者在最上面的，也可以简单修改一下，改为正向的调用链展示，使得展示效果更好。

```python
def print_call_chain(*args):
    import sys
    print(" ".join(map(str, args)))
    frames = []
    f = sys._getframe(1)
    while f:
        name = f.f_code.co_name
        s = f.f_locals.get('self', None)
        if s:
            c = getattr(s, "__class__", None)
            if c:
                name = "%s.%s %s" % (c.__name__, name, f.f_lineno)
        frames.append(name)
        f = f.f_back
    frames.reverse()
    for idx, frame in enumerate(frames):
        print(f"{idx:2d} |", "--" * idx, frame)
    print("-" * 70)
```

效果如下：

```ipython
In [7]: print_call_chain()

 0 |  <module>
 1 | -- start_ipython
 2 | ---- launch_instance
 3 | ------ TerminalIPythonApp.start 317
 4 | -------- TerminalInteractiveShell.mainloop 911
 5 | ---------- TerminalInteractiveShell.interact 904
 6 | ------------ TerminalInteractiveShell.run_cell 3075
 7 | -------------- TerminalInteractiveShell._run_cell 3130
 8 | ---------------- _pseudo_sync_runner
 9 | ------------------ TerminalInteractiveShell.run_cell_async 3334
10 | -------------------- TerminalInteractiveShell.run_ast_nodes 3517
11 | ---------------------- TerminalInteractiveShell.run_code 3577
12 | ------------------------ <module>
----------------------------------------------------------------------
```