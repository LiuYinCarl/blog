# Python 多继承中 __init__ 方法未调用到的检测方法

本文提出一种通用的检测 python 多继承中部分父类自定义 `__init__` 方法未被调用的方法。

## 问题

在复杂的多继承场景下，可能由于某个父类未考虑到会被继承的情况，没有在 `__init__` 中调用 `super().__init__()` 导致在它之后的父类未被调用 `__init__` 方法。

```python
class A(object):
    def __init__(self) -> None:
        print("init A")

class B(object):
    def __init__(self) -> None:
        print("init B")

class C(A, B):
    def __init__(self) -> None:
        print("init C")
        super().__init__()

c = C()
```

这段代码执行后输出如下

```shell
init C
init A
```

## 原因

可以发现， `class B` 的 `__init__` 函数没有被调用。这是因为 `class A` 没有调用 `super().__init__` 方法。 `super()` 的原型为：

```python
class super(type, object_or_type=None):
    pass
```

`super()` 返回一个代理对象，它会将方法调用委托给 `type` 的父类或兄弟类。如果在类内调用了 `super()` ，那么含义就是返回所在类的父类的一个代理类。然后所有正对 `super()` 返回值的方法调用，例如 `super().__init__()` , 这个 `__init__()` 方法的调用会被转发给当前类的 `__mro__` 列表中拥有 `__init__` 方法的第一个类，在上面的例子中，也就是 `class A` 。如果对上面的代码做一下修改，删除 `class A` 的 `__init__` 方法。

```python
class A(object):
    pass

class B(object):
    def __init__(self) -> None:
        print("init B")

class C(A, B):
    def __init__(self) -> None:
        print("init C")
        super().__init__()

c = C()
```

输出则变为

```shell
init C
init B
```

`cpython` 中的这个 `MRO` 查找过程的实现如下：

```c
// typeobject.c
static PyObject *
super_getattro(PyObject *self, PyObject *name)
{
    superobject *su = (superobject *)self;
    PyTypeObject *starttype;
    PyObject *mro;
    Py_ssize_t i, n;

    starttype = su->obj_type;
    if (starttype == NULL)
        goto skip;

    // 这里对 __class__ 做了拦截，所以打印 super().__class__ 的结果才是 <class 'super'>
    if (PyUnicode_Check(name) &&
        PyUnicode_GET_LENGTH(name) == 9 &&
        _PyUnicode_EqualToASCIIId(name, &PyId___class__))
        goto skip;

    mro = starttype->tp_mro;
    if (mro == NULL)
        goto skip;

    assert(PyTuple_Check(mro));
    n = PyTuple_GET_SIZE(mro);

    /* No need to check the last one: it's gonna be skipped anyway.  */
    for (i = 0; i+1 < n; i++) {
        if ((PyObject *)(su->type) == PyTuple_GET_ITEM(mro, i))
            break;
    }
    i++;  /* skip su->type (if any)  */
    if (i >= n)
        goto skip;

    /* keep a strong reference to mro because starttype->tp_mro can be
       replaced during PyDict_GetItemWithError(dict, name)  */
    Py_INCREF(mro);
    do {
        // 这个循环内遍历被 super 代理的类型的 __mro__ 元组
        // 直到找到一个 mro 链中的类型含有 `name` 属性
        PyObject *res, *tmp, *dict;
        descrgetfunc f;

        tmp = PyTuple_GET_ITEM(mro, i);
        assert(PyType_Check(tmp));

        dict = ((PyTypeObject *)tmp)->tp_dict;
        assert(dict != NULL && PyDict_Check(dict));

        res = PyDict_GetItemWithError(dict, name);
        if (res != NULL) {
            Py_INCREF(res);

            f = Py_TYPE(res)->tp_descr_get;
            if (f != NULL) {
                tmp = f(res,
                    /* Only pass 'obj' param if this is instance-mode super
                       (See SF ID #743627)  */
                    (su->obj == (PyObject *)starttype) ? NULL : su->obj,
                    (PyObject *)starttype);
                Py_DECREF(res);
                res = tmp;
            }

            Py_DECREF(mro);
            return res;
        }
        else if (PyErr_Occurred()) {
            Py_DECREF(mro);
            return NULL;
        }

        i++;
    } while (i < n);
    Py_DECREF(mro);

  skip:
    // 返回 class super 的属性
    return PyObject_GenericGetAttr(self, name);
}
```

其中 `do` 循环做的事情也解释了如下代码运行的结果。

```python
class A(object):
    pass

class B(object):
    def __init__(self) -> None:
        print("init B")

class C(A, B):
    def __init__(self) -> None:
        print("init C")
        super().__init__()

print(C.__mro__)
c = C()
print("*" * 30)
super(C, c).__init__()
```

输出如下

```shell
(<class '__main__.C'>, <class '__main__.A'>, <class '__main__.B'>, <class 'object'>)
init C
init B
******************************
init B
```

调用 `super(C, c).__init__()` 之所以只输出了一行 `init B` 就是因为 `super(C, c)` 在 `MRO` 查找过程中找到的 `class C` 的第一个含有 `__init__` 方法的类为 `class B` 。

通过查看 `cpython` 的源代码，现在完全理解 `super().__init__()` 这句代码的含义了。

## 自动查找多继承中未调用 `__init__`

了解了多继承中如何调用各个父类的 `__init__` 方法之后，那么能否找到一个方案自动检测到遗漏了调用 `__init__` 的多继承代码呢。在 Python 大型项目中，人工查看所有多继承的实现是否规范不太现实，如果能够找到一个方案快速检测，可以针对这个问题节约部分排查时间。

下面提出一个运行时检查的方案来实现这个功能。实现这个方案可以分为几个步骤：

1. 实现一个装饰器，对存在继承的类进行注册，在类型初始化的时候触发装饰器。自动输出不符合规范的类定义信息。
2. 扫描项目代码，修改源文件，对存在继承关系的类定义处添加装饰器代码。
3. 运行项目，启动检测。

### 通用方案实现

```python
# analysis_init.py
import os
import re
import inspect

# 白名单类
class_white_list = ["object", "dict"]
no_init_class = []
not_call_super_init_class = []

def log_analysis(log:str) -> None:
    if not log.endswith("\n"):
        log += "\n"
    # 可将结果输出到文件
    # with open("~/code_analysis.log", "a") as f:
    #     f.write(str+"\n")
    print(log.rstrip("\n"))

def cls_init_called_super_init(cls):
        if cls.__init__ == object.__init__:
            return False
        regex = r"super\((.*?)\)\.__init__\((.*?)\)"
        init_src = inspect.getsource(cls.__init__)
        lines = init_src.split('\n')
        lines = [l.strip() for l in lines]
        lines = [l for l in lines if not l.startswith('#')]
        found = False
        for line in lines:
            match = re.search(regex, line)
            if match:
                found = True
                break
        return found

def analysis_init(cls):
    try:
        # 忽略白名单类
        if cls.__name__ in class_white_list:
            return cls
        # 忽略只有一个父类并且父类在白名单中的类
        if len(cls.__bases__) == 1 and cls.__bases__[0].__name__ in class_white_list:
            return cls

        defs = [cls]
        defs.extend(cls.__bases__) # defs = [base_class, super_classes]
        # 排除掉 [子类，父类列表] 继承顺序中前者 __init__ 继承了后者的相同的类
        # 例1: class B(C1, C2): C1, C2 只继承 object 类, 类 B 没有自定义 __init__ 函数
        # 则 B.__init__ == C1.__init__, base_cls = [C1, C2]
        # 例2: class B(C1, C2, C3): C1, C2, C3 只继承 object 类, 类 B, C1 没有自定义 __init__ 函数
        # 则B.__init__ == C2.__init__, C1.__init__ == object.__init__, base_cls 为 [B, C1, C2, C3]
        defs = [defs[i] for i in range(len(defs)) if i == len(defs)-1 or defs[i].__init__ != defs[i+1].__init__]
        # defs_name = [klass.__name__ for klass in defs]
        defs_has_user_def_init = [klass.__init__ != object.__init__ for klass in defs]
        defs_called_super_init = [cls_init_called_super_init(klass) for klass in defs]
        # log_analysis(f">>>> {defs_name} {defs_has_user_def_init} {defs_called_super_init}")

        # 从后往前找，如果某个父类自定义了 __init__，但是它之前的某个子类没有自定义 __init__ 或者没有调用 super().__init__ 则为错误
        for idx in range(len(defs)-1, -1, -1):
            if defs_has_user_def_init[idx]:
                cls_def = inspect.getsource(cls).split('\n')[0]
                if m := [defs[i].__name__ for i in range(idx) if defs_has_user_def_init[i] == False]:
                    s = f"[not define init]\t {cls_def}\t {m}"
                    no_init_class.append((cls.__name__, tuple(m)))
                    log_analysis(s)
                if m := [defs[i].__name__ for i in range(idx) if defs_called_super_init[i] == False]:
                    s = f"[not call super init]\t {cls_def}\t {m}"
                    not_call_super_init_class.append((cls.__name__, tuple(m)))
                    log_analysis(s)
    except Exception as e:
        log_analysis(f"[EXCEPTION] {cls.__name__}  {str(e)}")
    finally:
        return cls

# 匹配所有类定义的正则表达式
pattern = re.compile(r'class\s+\w+\s*\((?:\s*\w+\s*(?:\:\s*\w+(?:\.\w+)?\s*)?,\s*)*\s*\w*(?:\.\w+)?(?:\:\s*\w+(?:\.\w+)?\s*)?\s*\):')
# 匹配 `class A:`, `class A():`, `class A(object)` 三种格式类定义的正则表达式
simple_calss_def_pattern = re.compile(r'class\s+\w+(\(\s*object\s*\)|\(\s*\))?\s*:')

def analysis_file(path:str):
    lines = []
    with open(path, "r") as f:
        lines = f.readlines()
    found = False
    for i in range(len(lines)):
        line = lines[i]
        if not line.startswith('class'):
            continue
        simple = simple_calss_def_pattern.findall(line)
        if simple:
            continue
        matches = pattern.findall(line)
        if matches:
            found = True
            print(f"{line}".rstrip("\n"))
            lines[i] = f"@analysis_init\n{line}"

    if found:
        lines[0] = f"from analysis_init import analysis_init\n{lines[0]}"
    with open(path, "w", encoding="utf-8") as f:
        f.writelines(lines)

def analysys_dir(code_dir:str):
    for item in os.listdir(code_dir):
        item_path = os.path.join(code_dir, item)
        if os.path.isdir(item_path):
            analysys_dir(item_path)
        if not item_path.endswith(".py"):
            continue
        analysis_file(item_path)
```

用于测试的类代码定义文件。

```python
# template.py
class A1:
    pass

class A2():
    pass

class A3(object):
    pass

class A4(dict):
    pass

class B1(object):
    pass

class B2(B1):
    pass

class C1(object):
    def __init__(self):
        pass

class C2(C1):
    pass

class D1(object):
    def __init__(self):
        pass
# bad case
class D2(D1):
    def __init__(self):
        pass

class E1(object):
    pass

class E2(object):
    pass

class E3(E1, E2):
    pass

class F1(object):
    def __init__(self):
        pass

class F2(object):
    pass

class F3(F1, F2):
    pass

class G1(object):
    pass

class G2(object):
    def __init__(self):
        pass
# bad case
class G3(G1, G2):
    pass

class H1(object):
    def __init__(self):
        pass

class H2(object):
    pass
# bad case
class H3(H1, H2):
    def __init__(self):
        pass

class I1(object):
    pass

class I2(object):
    def __init__(self):
        pass
# bad case
class I3(I1, I2):
    def __init__(self):
        pass

class J1(object):
    pass

class J2(J1):
    def __init__(self):
        super().__init__()

class K1(object):
    def __init__(self):
        pass

class K2(K1):
    def __init__(self):
        super().__init__()

class L1(object):
    pass

class L2(object):
    pass

class L3(L1, L2):
    def __init__(self):
        super().__init__()

class M1(object):
    def __init__(self):
        pass

class M2(object):
    pass

class M3(M1, M2):
    def __init__(self):
        super().__init__()

class N1(object):
    pass

class N2(object):
    def __init__(self):
        pass
# bad case
class N3(N1, N2):
    def __init__(self):
        super().__init__()

class O1(object):
    def __init__(self):
        pass

class O2(object):
    def __init__(self):
        pass
# bad case
class O3(O1, O2):
    def __init__(self):
        super().__init__()

class P1(object):
    def __init__(self):
        super().__init__()

class P2(object):
    def __init__(self):
        pass

class P3(P1, P2):
    def __init__(self):
        super().__init__()

class Q1(object):
    def __init__(self):
        pass

class Q2(object):
    def __init__(self):
        super().__init__()
# bad case
class Q3(Q1, Q2):
    def __init__(self):
        super().__init__()

class R1(object):
    def __init__(self):
        super().__init__()

class R2(object):
    def __init__(self):
        super().__init__()

class R3(R1, R2):
    def __init__(self):
        super().__init__()
```

单元测试代码。

```python
# test_analysis_init.py
import unittest
import shutil
import analysis_init

class TestAnalysisInit(unittest.TestCase):
    def setUp(self) -> None:
        shutil.copy('template.py', 'classes.py')
        analysis_init.analysis_file('classes.py')

    def test_analysis_init(self):
        import classes
        no_init_class = analysis_init.no_init_class
        not_call_super_init_class = analysis_init.not_call_super_init_class
        self.assertEqual(no_init_class,[
            ('G3', ('G1',)),
            ('I3', ('I1',)),
            ('N3', ('N1',)),
        ])
        self.assertEqual(not_call_super_init_class,[
            ('D2', ('D2',)),
            ('G3', ('G3', 'G1')),
            ('H3', ('H3',)),
            ('I3', ('I3', 'I1')),
            ('N3', ('N1',)),
            ('O3', ('O1',)),
            ('Q3', ('Q1',)),
        ])
```

测试结果

```shell
$ python3 -m unittest test_analysis_init.py
class A4(dict):
class B2(B1):
class C2(C1):
class D2(D1):
class E3(E1, E2):
class F3(F1, F2):
class G3(G1, G2):
class H3(H1, H2):
class I3(I1, I2):
class J2(J1):
class K2(K1):
class L3(L1, L2):
class M3(M1, M2):
class N3(N1, N2):
class O3(O1, O2):
class P3(P1, P2):
class Q3(Q1, Q2):
class R3(R1, R2):
[not call super init]    class D2(D1):   ['D2']
[not define init]        class G3(G1, G2):       ['G1']
[not call super init]    class G3(G1, G2):       ['G3', 'G1']
[not call super init]    class H3(H1, H2):       ['H3']
[not define init]        class I3(I1, I2):       ['I1']
[not call super init]    class I3(I1, I2):       ['I3', 'I1']
[not define init]        class N3(N1, N2):       ['N1']
[not call super init]    class N3(N1, N2):       ['N1']
[not call super init]    class O3(O1, O2):       ['O1']
[not call super init]    class Q3(Q1, Q2):       ['Q1']
.
----------------------------------------------------------------------
Ran 1 test in 0.017s

OK
```

## 在项目中实际测试的效果

使用这个方案对一个 35 万行左右的纯 Python 项目进行了测试，发现了 9 处多继承异常。
