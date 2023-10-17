# Python 创建常量

Python 自身没有内建类似其他语言中的常量关键字，导致需要使用常量的地方一般只能使用变量来替代。
下面介绍一种通过 `__setattr__` 魔术方法来实现 Python 中类似常量的特性。

```python
# constdef.py

class _constdef(object):
    def __setattr__(self, name, value):
        if name in self.__dict__:
            err_msg = "const attribute({}) duplicate set value({})".format(name, value)
            raise RuntimeError(err_msg)
        self.__dict__[name] = value

# 注册到 sys.modules 全局字典中
import sys
sys.modules["constdef"] = _constdef()
# 或者
# sys.modules[__name__] = _constdef()
```

测试代码:

```python
import constdef

constdef.VAL = 100
print(constdef.VAL)
constdef.VAL = 200
```

运行结果

```bash
100
Traceback (most recent call last):
  File "test.py", line 1, in <module>
    import constdef
  File "/Users/zhl/test/constdef.py", line 19, in <module>
    constdef.VAL = 200
  File "/Users/zhl/test/constdef.py", line 5, in __setattr__
    raise RuntimeError(err_msg)
RuntimeError: const attribute(VAL) duplicate set value(200)
```

对于比较大的项目来说，将项目中的所有常量都注册到一个模块中显然是不合适的，
所以我们需要对上面的代码进行改造来适应大项目。

```python
# cosntdef.py

class _constdef(object):
    def __setattr__(self, name, value):
        if name in self.__dict__:
            err_msg = "const attribute({}) duplicate set value({})".format(name, value)
            raise RuntimeError(err_msg)
        self.__dict__[name] = value
# 不再需要注册到全局模块中
```

假设项目中有两个模块都想定义一个 VAL 常量，可以像下面这样子来写。

```python
import constdef

module1_const = constdef._constdef()
module1_const.VAL = 100
print(module1_const.VAL)

module2_const = constdef._constdef()
module2_const.VAL = 200
print(module2_const.VAL)
```

在使用的时候，就可以通过 module1_const.VAL 来访问模块 1 的 VAL 常量，
通过 module2_const.VAL 来访问模块 2 的 VAL 常量。不同的模块分别创建一个 _constdef
对象，来隔离不同模块各自的常量。

运行结果如下：

```bash
100
200
```
