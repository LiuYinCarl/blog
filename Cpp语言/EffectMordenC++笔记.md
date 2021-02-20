# Effect Modern C++ 笔记



## 型别推导

### 条款1 理解模板型别推导

型别推导例子：

```c++
template<typename T>
void f(ParamType param);
```

当我们以如下形式调用的时候

``` c++
f(expr);
```

在编译器，编译器会通过 `expr` 推导两个型别:  `T` 的型别和 `ParamType` 的型别。这两个型别往往不一样， `ParamType` 经常会包含一些如 `const` 之类的饰词。

``` c++
template<typename T>
void f(const T& param);

// 调用
int x = 0;
f(x);
```

上面的例子中， `T` 会被推导为 `int`, `ParamType` 会被推导为 `const int&`。

`T` 的型别推导结果依赖于 `expr` 的型别和 `ParamType` 的型别。有 3 类情况。

- `ParamType` 具有指针或引用型别，但不是个万能引用
- `ParamType` 是一个万能引用
- `ParamType` 既非指针也非引用



#### `ParamType` 具有指针或引用型别，但不是个万能引用

型别推导的步骤：

1. 若 `expr` 具有引用型别，先将引用部分忽略
2. 对 `expr` 的型别和 `ParamType` 的型别执行模式匹配，来决定 `T` 的型别

``` c++
template <typename T>
void f(T& param);

int x = 27;
const int cx = x;
const int& rx = x;

// 调用 型别推导
f(x);  // T 的型别为 int, param 的型别为 int&
f(cx);  // T 的型别为 const int, param 的型别为 const int&
f(rx);  // T 的型别为 const int, param 的型别为 const int&
```

当向引用型别的形参传入 `const` 对象时，对象会保持其不可修改的属性，所以向持有 `T&` 型别的模板传入 `const` 对象是安全的。

``` c++
template <typename T>
void f(const T& param);  // param 是个 const 引用

int x = 27;
const int cx = x;
const int& rx = x;

f(x);  // T 的型别是 int, param 的型别是 const int&
f(cx);  // T 的型别是 int, param 的型别是 const int&
f(rx);  // T 的型别是 int, param 的型别是 const int&
```



``` c++
template<typename T>
void f(T* param);  // param 是个指针

int x = 27;
const int* px = &x;

f(&x);  // T 的型别是 int, param 的型别是 int*
f(px);  // T 的型别是 const int, param 的型别是 const int*
```

*注解：T 的类型就是 param 类型减去 param 类型中已写出类型*



#### `ParamType` 是一个万能引用

型别推导的步骤：

1. 如果 `expr` 是个左值， `T` 和 `ParamType` 都会被推导为左值引用。**这是在模板型别推导中， `T` 被推导为引用型别的唯一情形，尽管在声明时使用的时右值引用语法，它的型别推导结果却是左值引用。**
2. 如果 `expr` 是个右值，则应用上面情况 1 的规则。

**万能引用形参的型别推导规则不同于左值引用和右值引用形参。当遇到万能引用时，型别推导规则会区分实参是左值还是右值，而万能引用从来不会作这样的区分。**



#### `ParamType` 既非指针也非引用

既非指针也非引用，就是按值传递。

``` c++
template <typename T>
void f(T param);
```





