# getattr 的参数

在 Python 中，不支持对函数进行重载，解释器如果发现了同名的函数定义，后者会将前者进行覆盖，如下代码中， `func(a, b)` 的定义就覆盖了 `func(a)` 的定义。

```python
def func(a):
    print(a)

def func(a, b):
    print(a, b)

func(10) # TypeError: func() missing 1 required positional argument: 'b'
func(10, 20) # 10 20
```

但是经常使用到的用来获取一个对象属性的 `getattr` 函数却有两种调用方式，分别是 `getattr(obj, name)` 和 `getattr(obj, name, default)`。

```python
class Foo(object):
    val = 42

print(getattr(Foo, "val"))
# 42
print(getattr(Foo, "val", "Not Exist"))
# 42

print(getattr(Foo, "val2"))
# AttributeError: type object 'Foo' has no attribute 'val2'.
print(getattr(Foo, "val2", "Not Exist"))
# Not Exisst
```

那么这个函数是使用了了默认参数吗？比如可能有如下定义：

```python
def getattr(obj, name, default=None):
    pass
```

虽然这个猜测有一定道理，不过答案却是否定的。`getattr` 是一个 `builtins` 模块的函数，这个模块内的函数都是 C 语言编写的函数，
注入到了 Python 的默认命名空间 `builtins`，也就是说，这个函数并没有 Python 形式，自然也不可能是使用了默认参数。想要进一步理解
这个问题，需要深入 Python 虚拟机，查看 `getattr` 函数的实现。

```c
// Python/bltinmodule.c
static PyMethodDef builtin_methods[] = {
    // ...
    {"getattr",         (PyCFunction)(void(*)(void))builtin_getattr, METH_FASTCALL, getattr_doc},
    // ...
    {NULL,              NULL},
};

static PyObject *
builtin_getattr(PyObject *self, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *v, *name, *result;
    // 检查 getattr 的参数数量是否为 2 或 3 个
    if (!_PyArg_CheckPositional("getattr", nargs, 2, 3))
        return NULL;

    v = args[0]; // 获取 getattr 第一个参数
    name = args[1]; // 获取 getattr 第二个参数
    // 检查 name 是否是一个字符串
    if (!PyUnicode_Check(name)) {
        PyErr_SetString(PyExc_TypeError,
                        "getattr(): attribute name must be string");
        return NULL;
    }
    if (nargs > 2) {
        // 如果 getattr 参数为 3 个，并且 obj 中没有找到对应的属性，则返回默认值(getattr 的第三个参数)
        if (_PyObject_LookupAttr(v, name, &result) == 0) {
            PyObject *dflt = args[2];
            Py_INCREF(dflt);
            return dflt;
        }
    }
    else {
        result = PyObject_GetAttr(v, name);
    }
    return result;
}
```

从源码中，可以发现，限制 `getattr` 参数只能为 2 或者 3 个的原因在于这段代码，其他任何地方都没有对参数数量进行检查。
```c
    if (!_PyArg_CheckPositional("getattr", nargs, 2, 3))
        return NULL;
```

那么可以设想，如果跳过这个检查，则 `getattr` 的数量可以为任意个(如果要保证功能正常的话，至少需要 2 个)。修改源码如下：
```c
static PyObject *
builtin_getattr(PyObject *self, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *v, *name, *result;
    // 注释掉原来的参数数量检查
    // if (!_PyArg_CheckPositional("getattr", nargs, 2, 3))
    //     return NULL;
    // 添加我们自己的参数检查，只检查参数下限，不检查上限
    if (nargs < 2) {
      PyErr_SetString(PyExc_TypeError, // 错误类型只是为了演示方便，不一定合适
                      "getattr(): Hi, you should use at least 2 args for it!!!");
      return NULL;
    }

    v = args[0];
    name = args[1];
    if (!PyUnicode_Check(name)) {
        PyErr_SetString(PyExc_TypeError,
                        "getattr(): attribute name must be string");
        return NULL;
    }
    if (nargs > 2) {
        if (_PyObject_LookupAttr(v, name, &result) == 0) {
            PyObject *dflt = args[2];
            Py_INCREF(dflt);
            return dflt;
        }
    }
    else {
        result = PyObject_GetAttr(v, name);
    }
    return result;
}
```

重新编译源码，进行测试。
```python
Python 3.10.4 (heads/learn_3.10.4-dirty:7472151d17, Sep 10 2023, 01:50:49) [GCC 11.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> class Foo(object):
...     val = 10
...
>>> getattr(Foo)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: getattr(): Hi, you should use at least 2 args for it!!!
>>> getattr(Foo, "val")
10
>>> getattr(Foo, "val2", "Not Exist")
'Not Exist'
>>> getattr(Foo, "val", "Not Exist", None, None, None, None)
10
>>> getattr(Foo, "val2", "Not Exist", None, None, None, None)
'Not Exist'
>>>
```

从测试中可以发现，我们添加的 `getattr` 参数下限检查在执行 `getattr(Foo)` 的时候被触发。因为删除了参数上限检查，所以在执行
`getattr(Foo, "val", "Not Exist", None, None, None, None)` 是也没有报错。

到这里，就很清楚地知道了 `getattr` 可以有 2 或者 3 个参数的原因，并不是因为第三个参数使用了默认参数，而只是因为在 C 代码中强制限制
了它的参数数量只能为 2 或者 3。如果去掉上限检查， `getattr` 可以允许使用任意个参数。
