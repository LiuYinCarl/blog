# Effect Modern C++ 笔记

## 型别推导

### 条款 1 理解模板型别推导

型别推导例子：

```c++
template<typename T>
void f(ParamType param); 

```

当我们以如下形式调用的时候

``` c++
f(expr);
```

在编译器，编译器会通过 `expr` 推导两个型别: `T` 的型别和 `ParamType` 的型别。这两个型别往往不一样， `ParamType` 经常会包含一些如 `const` 之类的饰词。

``` c++
template<typename T>
void f(const T& param); 

// 调用
int x = 0; 
f(x); 

```

上面的例子中， `T` 会被推导为 `int`, `ParamType` 会被推导为 `const int&`。

`T` 的型别推导结果依赖于 `expr` 的型别和 `ParamType` 的型别。有 3 类情况。

* `ParamType` 具有指针或引用型别，但不是个万能引用
* `ParamType` 是一个万能引用
* `ParamType` 既非指针也非引用

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
void f(const T& param); // param 是个 const 引用

int x = 27; 
const int cx = x; 
const int& rx = x; 

f(x); // T 的型别是 int, param 的型别是 const int&
f(cx); // T 的型别是 int, param 的型别是 const int&
f(rx); // T 的型别是 int, param 的型别是 const int&

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

既非指针也非引用，就是按值传递。无论传入的是什么， `param` 都会是它的一个副本。

``` c++
template <typename T>
void f(T param); 
```

型别推导的步骤：

1. 如果 `expr` 具有引用型别，则忽略其引用部分。
2. 如果 `expr` 是个 `const` 对象，忽略 `const` 属性。如果 `expr` 是个 `volatile`  对象，忽略 `volatile` 属性。

``` c++
template <typename T>
void f(T param);

int x = 27;
const int cx = x;
const int& rx = x;

f(x);  // T 和 param 的型别都是 int
f(cx);  // T 和 param 的型别都是 int
f(rx);  // T 和 param 的型别都是 int
```

一个有价值的例子：

``` c++
template<typename T>
void f(T param); 

const char* const ptr = "hello"; 

f(ptr); 

```

位于 `*` 右侧的 `const` 将 `ptr` 声明为 `const`, `ptr` 指向不可以修改。位于 `*` 左侧的 `const` 将 `ptr` 指到的对象设为不可修改。当 `ptr` 被传递给 `f` 时，这个指针按值传递，`ptr` 的常量性会被忽视，`param` 的型别推导为 `const char *`, 即一个可修改的，指向一个 `const` 字符串的指针。`ptr` 指向的对象的常量性得到保留， `ptr` 自身的常量性被忽略。

#### 数组实参

将数组传递给持有按值形参的模板

``` c++
template<typename T>
void f(T param);

const char name[] = "Bob";

f(name);  // T 的型别为 const char*
```

由于数组和指针形参的等价性，函数无法声明真正的数组型别的形参。**但是却可以将形参声明成数组的引用**。

``` c++
template<typename T>
void f(T& param); // 按引用方式传递形参的模板

const char name[] = "Bob"; 
// T 的型别被推导为实际的数组型别，这个型别中包含数组尺寸
f(name); // T 被推导为 const char [13], param 被推导为 const char (&)[13]

```

可以利用数组声明引用的特点来写一个模板，在编译期推导数组含有的元素个数。

``` c++
// 以编译器常量的形式返回数组尺寸
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
    return N;
}

int a[] = {1, 2, 3, 4};
int b[arraySize(a)];
```

#### 函数实参

数组并非 C++ 中唯一可以退化为指针之物。函数型别也同样会退化为函数指针，并且上面针对数组型别推导的一切讨论都适用于函数及其向其函数指针的退化。

``` c++
void func(int, double); // 函数型别为 void (int, double)

template<typename T>
void f1(T param); // param 按值传递

template<typename T>
void f2(T& param); // param 按引用传递

f1(func); // param 被推导为函数指针，具体型别为 void (*)(int, double)

f2(func); // param 被推导为函数引用，具体型别为 void (&)(int, double)

```

要点速记：

* 在模板型别推导过程中，具有引用型别的实参的引用性会被忽略
* 对万能引用形参进行推导时，左值实参会进行特殊处理
* 对按值传递的形参进行推导时，若实参型别中带有 `const` 或 `volatile` 饰词，饰词会被忽略
* 在模板型别推导过程中，数组或函数型别的实参会退化成对应的指针，除非它们被用来初始化引用

### 条款 2 理解 auto 型别推导

``` c++
template <typename T>
void f(ParamType param);

f(expr);
```

在 `f ` 的调用语句中，编译器会利用 `expr` 来推导 `T` 和 `ParamType` 的型别。当某变量采用 `auto` 来声明时， `auto` 就扮演了模板中的 `T` 这个角色，而变量的型别饰词则扮演的是 `ParamType` 的角色。

`auto` 型别推导与模板型别推导只有一个地方不同。

``` c++
// C++98
int x1 = 27; 
int x2(27); 

// C++11 为了支持统一初始化添加的语法
int x3 = {27}; 
int x4{27}; 

```

如果将上边语句替换为采用 `auto` 声明变量

``` c++
auto x1 = 27;  // 型别是 int, 值是 27
auto x2(27);  // 同上

auto x3 = {27};  // 型别是 std::initializer_list<int>，值是 {27}
auto x4{27}; // 同上
```

其中 3，4 两条语句推导的型别和 1，2 两条语句不同是由于 `auto` 的一条特殊的型别推导规则。**当用 `auto` 声明变量的初始化表达式是用大括号括起来时，推导所得的型别就属于 `std::initializer_list` **。

``` c++
auto x5 = {1, 2, 3.5}; // 编译失败

```

上面这行代码随便会编译失败。但是可以分析一下它的推导过程。

1. 使用了 `auto`， 需要推导 `x5` 的型别。根据上面提到的 `auto` 的特殊推导规则可知， `x5` 被推导为一个 `std::initializer_list`。`std::initializer_list` 是个模板，需要根据某个型别 `T` 来实例化型别 `std::initializer_list<T>`，这意味着 `T` 需要被推导出来，这就是第二次推导。
2. 通过模板型别推导来推导出 `T` 的型别，但是由于初始化表达式中的值型别不一致，所以推导会失败，导致编译失败。

**所以， `auto` 和模板型别推导真正的唯一区别在于， `auto` 会假定用大括号括起来的初始化表达式代表一个 `std::initializer_list`，但模板型别推导不会**。

在 C++14 中，允许使用 `auto` 来表明函数返回值需要推导，`lambda` 表达式也会在形参声明中用到 `auto`。**但是，这些 `auto` 用法是在使用模板型别推导而不是 `auto` 型别推导。所以，带有 `auto` 返回值的函数若要返回一个大括号括起来的初始化表达式是无法通过编译的**。

``` c++
auto func() {
    return {1,2,3};  // 无法为 {1，2，3} 完成型别推导
}
```

用 `auto` 来指定 C++14 中 `lambda` 式的形参型别时，也不能使用大括号括起来的初始化表达式。

``` c++
std::vector<int> v; 

auto resetV = [&v](const auto& newV) {

    v = newV;

}

resetV({1, 2, 3}); 

```

要点速记：

* 在一般情况下， `auto` 型别推导和模板型别推导时一模一样的，但是 `auto` 型别推导会假定用大括号括起来的初始化表达式代表一个 `std::initializer_list`, 但模板型别推导不会。
* 在函数返回值或 `lambda` 式的形参中使用 `auto`，意思是使用模板型别推导而不是 `auto` 型别推导。

### 条款 3 理解 decltype

`decltype` 用来获取给定变量或表达式的型别。

C++11 中，`decltype` 的主要用途在于声明那些返回值型别依赖于形参型别的函数模板。假设要实现一个函数：形参包括一个容器(支持中括号下标)和一个下标，函数的返回值型别需要和下标操作结果的返回值型别相同。

``` c++
template<typename Container, typename Index>
auto func(Container& c, Index i) -> decltype(c[i]) {
    return c[i];
}
```

函数名前面的那个 `auto` 和型别推导没有关系，只是为了说明使用了 C++11 的返回值型别尾序语法。**尾序语法的好处时，在指定返回值型别时可以使用函数形参。比如 `c` 和 `i` **。采用这种方式之后， `operator[]` 返回值是什么型别， `func` 的返回值就是什么型别。

C++11 允许对单表达式的 `lambda` 函数的返回值实施推导，在 C++14 中则将这个允许范围扩张到了一切 `lambda` 函数和一些函数。对于上面的 `func` 函数，可以去掉返回值型别尾序语法，只保留函数名前面的 `auto` ，编译器会根据函数实现自动推导返回值的型别。

``` c++
template<typename Container, typename Index>
auto func(Container& c, Index i) {

    return c[i];

}

```

这种写法也不是很合适。大多数含有型别 `T` 的对象的容器的 `operator[]` 会返回 `T&`，但是由条款 1 可知，在模板型别推导过程中，初始化表达式的引用性会被忽略，所以下面代码会编译失败。

``` c++
#include <iostream>
#include <vector>
using namespace std;

template<typename Container, typename Index>
auto func(Container& c, Index i) {
  return c[i];
}

int main() {
  vector<int> vec{1,2,3};
  func(vec, 1) = 10;  // func(vcc, 1) 返回值的型别是 int, 是一个左值

  cout << vec[0] << "," << vec[1] << "," << vec[2] << endl;

  return 0;
}
```

为了防止上面这种问题，就要对 `func` 函数的返回值实行 `decltype` ，即指定 `func` 的返回值型别与表达式 `c[i]` 返回的型别完全一致，在 C++14 中通过 `decltype(auto)` 饰词解决这个问题。这个饰词中， `auto` 指定欲实施推导的型别，但是推导过程采用 `decltype` 的规则。

``` c++
template<typename Container, typename Index>
decltype(auto) func(Container& c, Index i) {
  return c[i]; 
}

```

**`decltype(auto)` 不限于在函数返回值型别处使用，在声明变量的场合，如果也想在初始化表达式处应用 `decltype` 型别推导规则，也可以使用**。

``` c++
Widget w;
const Widget& cw = w;

auto w1 = cw;  // auto 型别推导， w1 的型别是 Widget
decltype(auto) w2 = cw; // decltype 型别推导，w2 的型别是 const Widget&
```

前面的 `func` 函数还有一个缺陷就是不能接受传入的容器为右值，为了避免这个问题，需要将 `func` 的形参改成既能接受左值也能接受右值的万能引用。

``` c++
#include <iostream>
#include <vector>
using namespace std; 

vector<int> makeVector() {
  return vector<int>{1, 2, 3, 4}; 
}

template<typename Container, typename Index>
decltype(auto) func(Container&& c, Index i) {
  return forward<Container>(c)[i]; 
}

int main() {
  auto n = func(makeVector(), 1); 
  cout << n << endl; 

  return 0; 
}

```

#### decltype 的特性

将 `decltype` 应用到一个名字上，就会得出该名字的声明型别，名字是左值表达式。但是如果是比仅有名字更复杂的左值表达式的话， `decltype` 就保证得出的型别总是左值引用。**换言之，只要一个左值表达式不仅是一个型别为 `T` 的名字，它就得出一个 `T&` 型别。这种行为一般没有什么影响，因为绝大多数左值表达式都自带一个左值引用饰词。** 

但是凡事总有特例，

``` c++
int x = 0; // decltype(x) 的型别是 int

// 但是如果把 x 放到小括号里面，就得到一个比仅有名字更复杂的表达式 "(x)"，decltype((x)) 的型别是 int&
```

这个特性可能会导致如下这种误用：

``` c++
decltype(auto) f() {

    int x = 0;
    return (x);  // decltype((x)) 是 int&, 所以 f 返回的是 int&

}
```

上面这种写法就会导致返回一个局部变量的引用。所以，使用 `decltype(auto)` 的时候必须要小心。

要点速记：

* 绝大多数情况下， `decltype` 会得出变量或表达式的型别而不做任何修改
* 对于型别为 `T` 的左值表达式，除非该表达式仅有一个名字，`decltype` 总是得出型别 `T&`
* C++14 支持 `decltype(auto)`, 和 `auto` 一样，他会从其初始化表达式出发来推导型别，但是它的型别推导规则使用的是 `decltype` 的规则

### 条款 4 掌握查看型别推导结果的方法

