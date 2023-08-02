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

要输出一个符号的类型，有可以使用标准库自带的 `typeid` 或者 `Boost` 的 `type_id_with_cvr` ，但是 `typeid` 是不可靠的，因为标准只要求 `std::type_info::name` 中处理型别的方式类似像函数模板按值传递参数就可以。这样子会导致型别的 `cosnt`, `volatile`, 引用这三个属性消失。但是 `Boost` 的不会，从名字就可以看出来。

``` c++
File Edit Options Buffers Tools C++ Hide/Show Help
#include <iostream>
#include <boost/type_index.hpp>

template<typename T>
void f(const T& param) {
  using std::cout;
  using boost::typeindex::type_id_with_cvr;

  cout << "T = " << type_id_with_cvr<T>().pretty_name() << '\n';
  cout << "param = " << type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}

template<typename T>
void f2(const T& param) {
  using std::cout;

  cout << "T = " << typeid(T).name() << '\n';
  cout << "param = " << typeid(param).name() << '\n';
}


int main() {
  int n = 10;
  f(n);
  f2(n);

  return 0;
}
```

运行结果

``` bash
T = int
param = int const&
T = i
param = i
```



**要点速记**

- 有些工具产生的推导型别可能无用，或者不准确，所以理解 C++ 型别推到规则是必要的

## auto

### 条款 5 优先选用 auto，而非显式型别声明

使用 `auto` 而不使用 `std::function` 的原因

- `std::function` 语法复杂，需要重复定义形参
- `std::function`声明的是一个存储着一个闭包的 `std::function` 对象实例，可能需要从堆上分配内存来储存这个闭包， 但是使用 `auto` 声明的是一个就是一个指向闭包的对象，不需要多余的内存

显式型别声明在代码迁移的时候没有 `auto` 灵活，比如

``` c++
std::vector<int> v;
unsigned sz = v.size();
```

在 32 位的 Windows 上，`unsigned` 是 32 位的，`std::vector<int>::size_type` 也是 32 位的。在 64 位的 Windows 上，`unsigned` 还是 32 位的，但是 `std::vector<int>::size_type` 是 64 位的。所以，上面的代码从 32 位 Windows 移植到 64 位 Windows 可能会出问题，如果使用 `auto` 代替 `unsigned` 的话，就不会有这个问题。

另一个 `auto` 优于显式型别声明的例子：

``` c++
std::unordered_map<std::string, int> m;

for (const std::pair<std::string, int>& p : m) {
	// ... ...   
}
```

这个例子的错误在于 `std::unordered_map` 的键值部分是 `const` 的，所以 `std::unordered_map` 中的 `std::pair` 的型别是 `std::pair<const std::string, int>` 而不是 `std::pair<std::string, int>`。所以上面 `p` 的类型写错了，编译器就得想办法将 `std::pair<const std::string, int>` 转化为 `std::pair<std::string, int>`, 方法就是对 `m` 中的每个对象都做一次复制操作，形成一个 `p` 可以绑定的型别的临时对象，然后将 `p` 绑定到临时对象。这会造成如下后果：

- 循环的每次迭代都需要创建和析构临时对象，开销巨大
- 如果对 `p` 取地址，那么地址是临时对象的地址，而且这个临时对象在迭代结束的时候会被析构



**要点速记**

- `auto` 变量必须被初始化，这个特点可以防止忘记初始化对象



### 条例 6 当 auto 推导的型别不符合要求时，使用带显式型别的初始化物习惯用法

`auto`  出现与预期型别不同的例子

``` c++
std::vector<bool> features(const Widget& w);

auto b = features(w)[5];
```

上面 `b` 的类型并不是 `bool&`, 而是 `std::vector<bool>::reference`。 `std::vector<bool>`  的 `operator[]` 的这一点和一般的 `std::vector<T>` 容器返回 `t&` 不同。但是为了保证返回的 `std::vector<bool>::reference` 和常规的 `bool&` 表现保持一致，`std::vecot<bool>::reference` 做了一个向 `bool` 的隐式型别转换（**是 `bool` 不是 `bool&`**）。

`feature(w)` 会返回一个 `std::vector<bool>` 临时对象，然后针对这个对象执行 `operator[]` 返回一个 `std::vector<bool>::reference` 型别的对象。如果 `std::vector<bool>::reference` 的实现是一个对象含有一个指针。那么 `features(w)` 调用返回的临时对象会在表达式结束的地方被析构，那么 `b` 最后就会持有一个野指针，如果后面使用到了 `b`，就会发生未定义的行为。（我觉得这个锅其实不该怪 `auto`，得怪设计出了 `std::vector<bool>::reference` 的人）。

`std::vector<bool>::reference` 是一个代理类的实例。所谓代理类就是指为了模拟或者扩展其他型别的类。智能指针也是代理类。

**这种隐形代理类往往无法和 `auto` 和平相处，隐形代理类往往设计成生存期在一个语句内的形式。所以，如果要创建这种类的变量，往往违反了隐形代理类的假定前提，很容易造成未定义行为。** 所以要比避免写出下面这种代码：

``` c++
auto var = 隐形代理型别表达式;
```



需要做类型转转的时候，尽量使用显式的转型操作。



**要点速记**

- ”隐形“的代理型别可以导致 `auto` 根据 初始化表达式推导出 "错误的"（不符合预期的）型别
- 带显式型别的初始化物习惯用法可以强制 `auto` 推导出想要的类型



## 转向现代 C++

### 条款 7 在创建对象时注意区分 () 和 {}

大括号初始化语法也叫做统一初始化语法，适用于所有的初始化场合。

大括号初始化有一个特性，就是禁止内建型别之间进行隐式窄化型别转换。如果大括号内的表达式无法保证能够采用初始化的对象来表达，则代码不能通过与编译。

``` c++
double x, y, z;
int sum{ x + y + z}; // 编译错误，不能将 double 转化成 int
```

大括号初始化语法的另一个好处是可以避免语法解析错误，C++ 规定，任何能够解析为声明的都要解析为声明，但是这个规则有一个副作用：如果本来想要以默认方式构造一个对象，可能变成了声明一个函数。

``` c++
Widget w(); // 本来可能是想调用默认构造函数，却变成了声明
```

**大括号初始化的缺点**

大括号初始化语法有时会出现我们预料之外的情况。这些情况往往源于大括号初始化物、`std::initializer_list` 以及构造函数重载决议之间的纠结关系。比如前面的条款 2 提到的，如果使用大括号初始化物来初始化一个使用 `auto` 声明的变量，那么推导出来的型别就会成为 `std::initializer_list`。

在构造函数被调用的时候，如果形参中没有任何一个具备 `std::initializer_list` 型别，那么大括号和小括号初始化的意义就没有区别。

``` c++
class Widget {
public:
    Widget(int i, bool b);
    Widget(int i, double b);
};

Widget w1(10, true); // 调用第一个构造函数
Widget w2(10, 5.0); // 调用第二个构造函数
Widget w1{10, true}; // 调用第一个构造函数
Widget w2{10, 5.0}; // 调用第二个构造函数
```

但是如果有构造函数声明了任何一个具备 `std::initializer_list` 型别的形参，那么采用了大括号初始化语法的调用语句会 **强烈的优先选用带有 `std::initializer_list` 型别形参的重载版本。**

``` c++
class Widget {
public:
    Widget(int i, bool b);
    Widget(int i, double b);
    Widget(std::initializer_list<long double> il);
};

Widget w1(10, true); // 调用第一个构造函数
Widget w2(10, 5.0); // 调用第二个构造函数
Widget w1{10, true}; // 调用第三个构造函数，10 和 true 被强制转换成 long double
Widget w2{10, 5.0}; // 调用第三个构造函数，10 和 5.0 被强制转换成 long double
```



有一个边界用例需要了解。假如使用了一对空大括号来构造一个函数，而该对象既支持默认构造函数，又支持带有 `std::initializer_list` 型别参数的构造函数。那么，这对空大括号的意义是什么呢，如果意义是”没有实参“，那就应该执行默认构造，如果意义是 ”空的 `std::initializer_list`“，那就应该以一个不含任何元素的 `std::initializer_list` 为基础执行构造。**语言规定，在这种情况下应该执行默认构造，空大括号表示的是 ”没有实参“而不是”空的 `std::initializer_list`“**。



**要点速记**

- 大括号初始化可以应用的语境最为宽泛，可以阻止隐式窄化型别转换，还可以防止初始化的时候的解析语法歧义。
- 在构造函数重载决议期间，只要有任何可能，大括号初始化物就会与带有 `std::initializer_list` 型别的形参相匹配，即使其他重载版本有着貌似更加匹配的形参表。
- 使用小括号还是大括号，会造成结果大相径庭的一个例子是，使用两个实参创建一个 `std::vector<T>`对象。

### 条款 8 优先选用 nullptr，而非 0 或 NULL

0 或者 `NULL` 并不是指针

``` c++
#include <iostream>

void f(void* p) {
  std::cout << "void*" << std::endl;
}

void f(long x) {
  std::cout << "long" << std::endl;
}

void f(int n) {
  std::cout << "int" << std::endl;
}

int main() {
  f(NULL);

  return 0;
}
```

在 g++9.3 clang++10 上测试，输出都是 "long"。



**要点速记**

- 相对于 0 或 `NULL`，优先选用 `nullptr`。
- 避免在整型和指针型别之间重载。



### 条款 9 优先选用别名声明，而非 typedef

**使用别名声明而不是 `typedef` 的理由**

别名声明可以模板化（这种情况下它们被称为别名模板，alias template），`typedef` 就不行。它给了 C++11 程序员一种直截了当的表达机制，用以表达 C++98 程序员不得不用嵌套在模板化的 `struct` 里的 `typedef` 才能硬搞出来的东西。比如，想要定义一个同义词，表达一个链表，它使用了一个自定义分配器 `MyAlloc`。

``` c++
// 使用别名声明
template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

MyAllocList<Widget> lw;
```

``` c++
// 使用 typedef
template<typename T>
struct MyAllocList {
    typedef std::list<T, MyAlloc<T>> type;
};
```

如果想在模板内使用 `typedef` 来创建一个链表，它容纳的对象型别由模板形参指定的话，那你就要给 `typedef` 的名字加一个 `typename` 前缀。

``` c++
template<typename T>
class Widget {
private:
    typename MyAllocList<T>::type list;
};
```

这里，`MyAllocList<T>::type` 代表一个依赖于模板型别参数形参（T) 的型别，所以 `MyAllocList<T>::type` 称为带依赖型别，带依赖型别必须前面加一个 `typename`。

但是如果 `MyAllocList` 是使用别名模板来定义的，那么要写 `typename` 的要求就消失了。

``` c++
template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

template<typename T>
class Widget {
private:
    MyAllocList<T> list;
};
```



**要点速记**

- `typedef` 不支持模板化，但别名声明支持
- 别名模板可以免写 "::type" 后缀，并且在模板内，对于内嵌 `typedef` 的引用经常要求加上 `typename` 前缀

### 条款 10 优先选用限定作用域的枚举型别，而非不限作用域的枚举型别

C++98 风格的枚举型别中定义的枚举量属于包含着这个枚举型别的作用域，这就意味着在此作用域内不能有其他实体取相同的名字。

``` c++
enum Color { black, white, red }; // black, white, red 的作用域和 Color 相同

auto white = false; // 错误， white 重定义
```

C++11 添加的限定作用域的枚举类型

``` c++
enum class Color { black, white, red }; // black, white, red 所在作用域被限定在 Color 内

auto white = false; // 正确
```

`enum class` 是强类型的，不会隐式转换到整数类型。



**要点速记**

- 限定作用域的枚举型别仅在枚举型别内可见，只能通过强制类型转换以转换到其他型别
- 限定作用域的枚举类型和不限定作用域的枚举型别都支持底层型别指定。限定作用域的枚举型别的默认底层型别是 `int`，不限定作用域的枚举型别没有默认底层型别
- 限定作用域的枚举型别总是可以进行前置声明，而不限定作用域的枚举型别只有在指定了默认底层型别的前提下才可以进行前置声明



### 条款 11 优先选用删除函数，而非 private 未定义函数

删除函数申明为 `public` 的优点：

-  在编译链接时，C++ 会先校验函数的可访问性，再校验删除状态，这样子的话，当试图调用某个 `private` 删除函数时，有些编译器可能只会报该函数为 `private`  的错误，所以，将删除函数声明为 `public` 可以得到更好的错误信息

删除函数的另外一个优点是任何函数都可以成为删除函数，但只有成员函数可以声明成 `private`。

举个例子，为了避免不想要的隐式转换，可以将含有某些类型的参数声明成删除函数。

``` c++
void foo(int n) {
    // ... ...
}

void foo(char) = delete;
void foo(bool) = delete;
```

尽管删除函数不可被使用，但是它们还是程序的一部分，所以在重载决议的时候他们还是会被考虑。看下面一个例子。

``` c++
bool func(int n) {
    // ... ...
}

bool func(char) = delete; // 拒绝 char 型别
bool func(double) = delete; // 拒绝 double 和 float 型别
```

为什么 `bool func(double) = delete;` 会拒绝 `float` 型别呢？这是因为当 `float` 型别面临转型到 `int` 还是 `double` 型别的时候， C++ 会优先转型到 `double` 型别。这样一来，对于 `func` 的调用如果传入一个 `float`, 则会尝试调用 `double` 型别形参的重载版本，但是由于这个重载版本已经是个删除版本，所以编译就被阻止了。

还有一个删除函数能做到而 `private` 成员函数不能做到的事情就是阻止不应该进行的模板具现。

``` c++
template<typename T>
void processPointer(T* p) {
	// ... ...
}

template<typename T>
void processPointer<void>(void*) = delete;

template<typename T>
void processPointer<char>(char*) = delete;
```

如果是类内部的函数模板，并且你想通过 `private` 声明来禁用某些具现，这是做不到的，因为你不可能给予成员函数模板的某个特化以不同于主模板的访问层级。如果 `processPointer` 是在 `Widget` 内部的一个成员函数模板，而你想禁止使用 `void*` 指针来调用它，下面是 C++98 的用法，但是通不过编译。

``` c++
class Widget {
public:
    template<typename T>
    void processPointer(T* ptr) {
        // ... ...
    }
   
private:
    template<>  // 错误
    void processPointer<void>(void*);
};
```

编译不过的原因是 **模板特化必须在名字空间作用域而不是类作用域内编写**。但是删除函数可以避免这个缺点，因为他们不需要不同的访问层级，也因为成员函数模板可以在类外（名字空间作用域）被删除。

``` c++
class Widget {
public:
    template<typename T>
    void processPointer(T* ptr) {
        // ... ...
    }
};

// 仍然具有 public 访问层级但是被删除了
template<>
void Widget::processPointer<void>(void*) = delete;
```



**要点速记**

- 优先选用删除函数，而非 `private` 未定义函数
- 任何函数都可以删除，包括非成员函数和模板函数



### 条款 12 为意在改写的函数添加 override 声明

C++98 对虚函数重写的要求：

- 基类中的函数必须是虚函数
- 基类和派生类中的函数名字必须完全相同（析构函数除外）
- 基类和派生类中的函数形参型别必须完全相同
- 基类和派生类中的函数常量性必须完全相同
- 基类和派生类中的函数返回值和异常规格必须兼容

C++ 11 中新加的限制：

基类和派生类中的函数引用饰词必须完全相同。成员函数引用饰词是 C++11 的一个新特性，是为了限制成员函数仅用于左值或右值。带有引用饰词的成员函数，不必是虚函数。

``` c++
class Widget {
public:
    void doWork() &; // 仅在 *this 是左值时调用
    void doWork() &&; // 仅在 *this 时右值时调用
};

Widget makeWidget(); // 工厂函数，返回右值
Widget w;  // 普通对象，左值

w.doWork(); // 以左值调用 Widget::doWork(即 Widget::doWork &)
makeWidget().doWork(); // 以右值调用 Widget::doWork(即 Widget::doWork &&)
```



所以在重写(override)函数的时候，最好加上 `override` 声明。

C++11 添加了两个语境关键字 `override` 和 `final`。它们的特色是，语言保留这两个关键字，但仅在特定语境下保留。对于 `override` 的情况而言，它仅于出现在成员函数声明的末尾时才有保留意义。

引用饰词的一个使用场景：防止多余的复制

``` c++
class Widget {
public:
    using DataType = std::vector<double>;
    
    DataType& data() & { return values; }
    
    DataType data() && { return std::move(values); }
    
private:
    DataType values;
};
```

上面这种情况下如果是一个左值 `Wdiget` 对象调用 `data()`，就会返回 `values` 的左值引用，如果一个右值 `Widget` 对象调用 `data()`，则返回一个右值。



**要点速记**

- 为意在改写的函数添加 `override` 声明
- 成员函数引用饰词使得对于左值和右值对象的处理可以区分开来



### 条款 13 优先选用 const_iterator, 而非 iterator

`const_iterator` 是 STL 中相当于指涉到 `const` 的指针的等价物，它们指涉到不可被修改的值。



**要点速记**

- 优先选用 `const_iterator` 而非 `iterator`
- 在最通用的代码中，优先选用非成员函数版本的 `begin`，`end` 和 `rbegin` 等，而非其成员函数版本



### 条款 14 只要函数不会抛出异常，就为其加上 noexcept 声明

对不会抛出异常的函数加上 `noexcept` 声明。意思就是如果确保本函数内部调用的所有函数都不会抛出异常，且本函数自己不会抛出异常，那么就可以给本函数添加 `noexcept` 声明。

在带有 `noexcept` 声明的函数中，优化器不需要在异常传出函数的前提下，将执行期栈保持在可展开状态，也不需要在异常溢出的前提下，保证所有其中的对象以其被构造顺序的逆序完成析构。而 C++98 风格的以 `throw()` 异常规则声明的函数就没有这种灵活性，和没有加异常规格声明的函数一样。

``` c++
T function(params) noexcept; // C++11 风格 最优化
T function(params) throw; // C++98 风格 优化不够
T function(params); // 优化不够
```



**要点速记**

- `noexcept` 声明是函数接口的组成部分，这意味着调用方可能会对它有依赖
- 相对于不带 `noexcept` 声明的函数，带有 `noexcept` 声明的函数有更多机会得到优化
- `noexcept` 性质对于移动操作，`swap`，资源释放函数和析构函数最有价值
- 大多数函数都是异常中立的，不具备 `noexcept` 性质



### 条款 15 只要有可能使用 constexpr, 就使用它

当 `constexpr` 应用于对象时，就是一个加强版的 `const`, 但应用于函数时，却有不同的含义。

所有 `constexpr` 对象都是 `const` 对象，而并非所有 `const` 对象都是 `constexpr` 对象。如果想要让编译器提供保证，让变量拥有一个值，用于要求编译期常量的语境，那么使用 `constexpr` 更加合适。

如果将 `constexpr` 应用于函数的话：

- `constexpr` 函数可以用在要求编译期常量的语境中。在这种语境下，如果传给一个 `constexpr` 函数的实参值是在编译期已知的，则结果也会在编译期间计算出来。如果任何一个实参在编译期未知，则代码无法通过编译。
- 在调用 `constexpr` 函数时，若传入的值有一个或多个在编译期未知，则函数的运行方式和普通函数一样，也是在运行期执行计算的结果。

由于 `constexpr` 函数必须在传入编译期常量时能够返回编译期结果，它们的实现必须加以限制。在 C++11 和 C++14 中，这样的限制还有所不同。

在 C++11 中， `constexpr` 函数不得包含多于一个可执行语句，即一条 `return` 语句。但是我们可以用技巧来拓展 `constexpr` 函数的表达能力：

1. 使用三目运算符来替代 if-else 语句
2. 使用递归替代循环

``` c++
// 使用 conseexpr 实现整数的 pow 函数
constexpr int pow(int base, int exp) noexcept {
    return (exp == 0 ? 1 : base * pow(base, exp-1));
}
```

`constexpr` 函数仅限于传入和返回字面型别 （literal type），意思就是这样的型别能够持有编译期可以决议的值。在 C++11 中，除了 `void`，其他所有的内建型别都符合这个条件。但是用户自定义型别也可能是字面型别，因为它的构造函数和其他成员函数可能也是 `constexpr` 函数。

``` c++
class Point {
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept : x(xVal), y(yVal) {}
    constexpr double getX() const noexcept { return x; }
    void double setX(double xVal) noexcept { x = xVal; }
    // ... ...
};

// 使用
constexpr Point p1(1.0, 2.0); // 在编译期运行构造函数
```

有两个限制使得无法将 `setX` 函数声明为 `constexpr`。

1. 该函数修改了操作对象，可是在 C++ 11 中， `constexpr` 函数都隐式地被声明为 `const` 的了。
2. 该函数的返回值型别是 `void`，在 C++11 中，`void` 并不是字面型别。

不过在 C++14 中，这两个限制都被解除了。

需要注意的是， `constsexpr` 是对象和函数接口的组成部分，所以将函数声明为 `constexpr` 的时候需要慎重，防止之后如果去掉函数的 `constexpr` 属性后造成代码不能向后兼容。

**要点速记**

- `constexpr` 对象都具备 `const` 属性，并由编译期已知的值完成初始化。
- `constexpr` 函数在调用时若传入的值是编译期已知的，则会产出编译期结果。
- 比起非 `constexpr` 对象或 `constexpr` 函数，`constexpr` 对象和函数可以用在一个作用域更广的语境中。

### 条款 16 保证 const 成员函数的线程安全性

**要点速记**

- 保证 `const` 成员函数的线程安全性，除非可以确保它们不会用在并发语境中
- 运用 `std::atomic` 型别的变量会被运用互斥量提供更好的性能，但前者仅适用于对单个变量或内存区域的操作

### 条款 17 理解特种成员函数的生成机制

特种成员函数指 C++ 会自行生成的成员函数。

C++98 有四种特种成员函数：默认构造函数，析构函数，复制构造函数和复制赋值运算符。这些函数仅在某些代码使用了它们，但在类中未显式声明它们的时候才会生成。

 生成的特种成员函数都具有 `public` 访问层级且是 `inline` 的，并且它们都是非虚的，除非是个虚构函数，且位于一个派生类中，且基类的析构函数是个虚函数。在这种情况下，编译期给派生类自动生成的析构函数也是个虚函数。

C++11 中，新添加了两类特种成员函数：移动构造函数和移动赋值运算符。

``` c++
class Widget {
public:
    Widget(Widget&& rhs);  // 移动构造函数
    Widget& operator=(Widget&& rhs); // 移动赋值运算符
};
```

**移动构造函数和移动赋值运算符只能作用于非静态成员**。移动构造函数将依据其形参 `rhs` 的各个非静态成员对于本类的对应成员执行移动构造，而移动赋值运算符则将依据其形参 `rhs` 的各个非静态成员对于本类的对应成员执行移动赋值。如果有基类的话，移动构造函数同事还会移动构造它的基类部分，而移动赋值运算符则会移动赋值它的基类部分。

对于不可移动型别的成员（即并未为移动操作提供特殊支持的型别）将进行复制操作。每个按成员进行移动的操作，其核心在于把 `std::move` 应用到每一个移动源对象，其返回值被用于函数重载决议，最终决定是执行一个移动还是复制操作。

**复制构造函数和复制赋值函数是彼此独立的。声明了其中一个，并不会阻止编译器生成另一个。**

**移动构造函数和移动赋值运算符不是彼此独立的，声明了其中一个，就会阻止编译器生成另一个。这种机制的理由在于，假设你声明了一个移动构造函数，你实际上表明移动操作的实现方式将会于编译器生成的默认按成员移动的移动构造函数有所不同。如果按成员进行的移动操作有不合适的地方，那么按成员进行的移动赋值运算符也极有可能不合预期。**



**Rule of Three**

如果你声明了复制构造函数，复制赋值运算符或析构函数中的任何一个，你就得同时声明所有这三个。

**C++11 规定：只要用户声明了析构函数，就不会生成移动操作。**

所以，移动操作的生成条件仅当以下三者同时成立：

- 该类未声明任何复制操作
- 该类未声明任何移动操作
- 该类未声明任何析构函数

C++11 中特种函数的规则：

- 默认构造函数：与 C++98 的机制相同，仅当类中不包含用户声明的构造函数时才生成。
- 析构函数：与 C++98 的机制基本相同，唯一的区别在于析构函数默认未 `noexcept`, 与 C++98 的机制相同，仅当基类的析构函数为虚的，派生类的构造函数才是虚的。
- 复制构造函数：运行期行为与 C++98 相同：按成员进行非静态数据成员的复制构造。仅当类中不包含用户声明的复制构造函数时才生成。如果该类声明了移动操作，则复制构造函数将被删除。在已经存在复制赋值运算符或析构函数的条件下，仍然生成复制构造函数已经成为了被废弃的行为。
- 复制赋值运算符：运行期行为与 C++98 相同：按成员进行非静态数据成员的复制赋值。仅当类中不包含用户声明的赋值赋值运算符时才生成，如果该类声明了移动操作，则复制构造函数将被删除。在已经存在复制构造函数或析构函数的条件下，仍然生成复制赋值运算符已经成为了被废弃的行为。
- 移动构造函数和移动赋值运算符：都按成员进行非静态数据成员的移动操作。仅当类中不包含用户声明的复制操作、移动操作和析构函数时才生成。

**要点速记**

成员函数模板在任何情况下都不会抑制特种成员函数的生成。



## 智能指针

### 条款 18 使用 std::unique_ptr 管理具备专属所有权的资源

在默认情况下，`std::unique_ptr` 和裸指针有着相同的大小。

`std::unique_ptr` 实现的是专属所有权语义。一个非空的 `std::unique_ptr` 总是拥有其所指涉到的资源。移动一个 `std::unique_ptr` 会将所有权从源指针移动到目标指针，源指针置空。`std::unique_ptr` 不允许复制，是个只移型别。在执行析构操作时，由非空的 `std::unique_ptr` 析构其资源。默认地，资源的析构时通过对 `std::unique_ptr` 内部的裸指针进行 `delete` 实现的。

`std::unique_ptr` 的一个常见用法是在对象的继承图谱中作为工厂函数的返回型别。这种继承谱系的工厂函数通常会在堆上分配一个对象并返回一个指涉到它的指针，并当不再需要该对象时，由调用者负责删除。当调用者释放 `stdLLunique_ptr` 的时候，`std::unique_ptr` 被析构，自动对其指涉的对象实行 `delete`。

`std::unique` 以两种形式提供，一种时单个对象（`std::unique_ptr<T>`），另一种是数组（`std::unique_ptr<T[]>`）。这样区分的结果是，对于 `std::unique_ptr` 指涉到的对象种类不会产生二义性。`std::unique_ptr` 的 API 也被设计成与使用形式相匹配。比如单个对象形式不提供索引运算符(`operator[]`)，而数组形式则不提供提领运算符（`operator*` 和 `operator->`）。

**要点速记**

- `std::unique_ptr` 是小巧，高速，具备只移型别的智能指针，对托管资源实施专属所有权语义。
- 默认地，资源析构采用 `delete` 运算符实现，但可以指定自定义删除器。有状态的删除器（匿名函数）和采用函数指针实现的删除器会增加 `std::unique_ptr` 型别的对象尺寸。
- 将 `std::unique_ptr` 转换成 `std::shared_ptr` 是容易实现的。

### 条款 19 使用 `std::shared_ptr` 管理具备共享所有权的资源

`std::shared_ptr` 使用引用计数来管理资源。当最后一个指向资源的 `std::shared_ptr` 被析构时，资源会被释放。

引用计数会带来一些性能问题：

- `std::shared_ptr` 的尺寸是裸指针的两倍。因为它们内部既包含一个指涉到该资源的指针，也包含一个指涉到该资源的引用计数的裸指针。
- 引用计数的内存必须动态分配。
- 引用计数的递增和递减必须是原子操作。原子操作一般比非原子操作要慢。

由于移动 `std::sharder_ptr` 不需要修改资源的引用计数，所以移动 `std::shared_ptr` 比复制它们要快。

`std::shared_ptr` 也使用 `delete` 运算符作为其默认资源析构机制，但也同样支持自定义析构器。但是这种支持的设计却与 `std::unique_ptr` 有所不同。对于 `std::unique_ptr` 来说，析构器的型别是智能指针的一部分。对于 `std::shared_ptr` 来说却不是。

与 `std::unique_ptr` 不同的另一点是：自定义析构器不会改变 `std::shared_ptr` 的尺寸。无论析构器是怎么样的型别，`std::shared_ptr` 对象的尺寸都是裸指针的两倍。

`std::shared_ptr` 的模型

![image-20210309224538880](E:\blog\Cpp语言\images\EffectMordenC++笔记\image-20210309224538880.png)

一个对象的控制块由创建首个指涉到该对象的 `std::shared_ptr` 的函数来确定。因为，正在创建指涉到某对象的 `std::shared_ptr` 的函数是无从得知是否有其他的 `std::shared_ptr` 已经指涉到该对象。因此，控制块的创建遵循如下规则：

- `std::make_shared` 总是创建一个控制块。
- 从具备装束所有权的指针 (`std::unique_ptr` 和 `std::auto_ptr`指针) 出发构建一个 `std::shared_ptr` 时，会创建一个控制块。
- 当 `std::shared_ptr` 构造函数使用裸指针作为实参来调用时，会创建一个控制块。

由以上规则可以知道，千万不要对一个对象创建多个控制块，不然会引发多次析构。

`std::shared_ptr` 没有提供对数组的操作。

**要点速记**

- 避免使用裸指针型别的变量来创建 `std::shared_ptr`，而应该直接使用 `new` 的返回值。



### 条款 20 对于类似 std::shared_ptr 但有可能空悬的指针使用 std::weak_ptr

`std::weak_ptr` 是作为 `std::shared_ptr` 的一种扩充，不会影响所指涉到的对象的引用计数。

从效率的角度来看，`std::weak_ptr` 和 `std::shared_ptr` 从本质上来说是一致的。`std::erak_ptr` 的对象和 `std::shared_ptr` 的对象尺寸相同，它们和 `std::shared_ptr` 使用同样的控制块，其构造，析构，赋值操作都包含了对引用计数的原子操作。实际上 `std::shared_ptr` 的控制块里面还有第二个引用计数，`std::weak_ptr` 操作的就是这第二个引用计数。

**要点速记**

- 使用 `std::weak_ptr` 来替代可能空悬的 `std::shared_ptr`。
- `std::weak_ptr` 的使用场景包括缓存，观察者列表，以及避免 `std::shared_ptr` 指针循环引用等。



### 条款 21 优先使用 std::make_unique 和 std::make_shared，而非直接使用 new

 `std::make_shared` 是 C++11 的时候加入标准库的， `std::make_unique` 是 C++14 的时候加入标准库的。

``` c++
// 在 C++11 中实现简单的 make_unique
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
```

`std::make_shared` 和 `std::make_unique` 会把一个任意实参集合完美转发给动态分配内存的对象的构造函数，并返回一个指涉到该对象的智能指针。make 系列的另一个函数是 `std::allocate_shared`，它的行为和 `std::make_shared` 一样，只不过它的第一个实参是个用以动态分配内存的分配器对象。

**要点速记**

- 相对于直接使用 `new` 表达式，`make` 系列函数消除了重复代码，改进了异常安全性，并且对于 `std::make_shared` 和 `std::allocated_shared` 而言，生成的目标代码尺寸更小，速度更快。
- 不适于使用 make 系列函数的场景包括需要定制删除器，以及期望直接传递大括号初始化物。
- 对于 `std::shared_ptr` ，不建议使用 make 系列函数的额外场景包括：自定义内存管理的类。内存紧张的系统，非常大的对象，以及存在比指涉到相同对象的 `std::shared_ptr` 生存期更久的 `std::weak_ptr`，因为 `std::make_shared` 函数创建对象的时候，会将控制块和对象的内存一起申请，所以，在控制块还存在引用的时候，对象使用的内存也无法释放。



### 条款 22 使用 Pimpl 习惯用法时，将特殊成员函数的定义放到实现文件中

Pimpl 习惯用法就是 “pointer to implementation”, 即指涉到实现的指针。这种技巧就是把某类的数据成员用一个指涉到某实现类的指针替代，然后把原来在主类中的数据成员放置到实现类中，并通过指针间接访问这些数据成员。Pimpl 是一种可以在类实现和类使用者之间减少编译依赖的方法。

``` c++
// widget.h
class Widget {
public:
    Widget();
private:
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;  // Gadget 是某种用户自定义型别
};
```

上面这种写法，widget.h 必须包含 string, vector, Gadget 等的头文件，这些头文件会增加使用了 widget.h 的程序的编译时间，而且假如某个头文件发生了变化，使用了 widget.h 的程序都必须重新编译。

使用 Pimpl 进行修改

(C++98 过时写法)

``` c++
// widget.h
class Widget {
public:
    Widget();
    ~Widget();  // 析构函数变得必要,因为需要管理实现类
private:
    struct Impl;  // 声明实现结构体(非完整型别)
    Impl* pImpl;  // 以及指涉到它的指针
};
```

``` c++
// widget.cpp
#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>

struct Widget::Impl {
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

Widget::Widget() : pImpl(new Impl) {}

Widget::~Widget() { delete pImpl; }
```

（C++14 潮流写法）

``` c++
// widget.h
class Widget {
public:
    Widget();
	// 使用智能指针，可以不用写析构函数了
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};
```



``` c++
// widget.cpp
#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>

struct Widget::Impl {
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) {}
```

``` c++
// 客户代码
#include "widget.h"
Widget w;  // 编译错误
```

但是这种写法很可能无法通过编译。原因是为 w 生成析构代码错误。在使用 `std::unique_ptr` 的类定义中，我们未声明析构函数。编译器会为我们生成一个析构函数，在该析构函数内，编译器会插入代码来调用 `Widget` 的数据成员 `pImpl`。`pImpl` 是一个 `std::unique_ptr<Widget::Impl>` 型别的对象，即一个使用了默认析构器的 `std::unique_ptr`。默认析构器是在 `std::unique_ptr` 内部使用 `delete` 运算符来针对裸指针实施析构的函数。然而，在实施 `delete` 运算符之前，典型的实现会使用 C++11 中的 `static_assert` 确保裸指针未指涉到非完整型别，但是 widget.h 中的 `Impl` 就是个非完整型别。

为了解决这个问题，只需要在生成析构 `std::unique_ptr<Widget::Impl>` 代码处，`Widget::Impl` 是个完整型别就好了。只要型别的定义可以被看到，它就是完整的。而 `Widget::Impl` 的定义位于 widget.cpp 中。因此，只要在 widget.cpp 内部的 `Widget::Impl` 定义之后定义 `Widget` 的析构函数就好了。

``` c++
// widget.h
class Widget {
public:
    Widget();
	~Widget(); // 仅声明
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};
```

``` c++
// widget.cpp
#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>

struct Widget::Impl {
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) {}
Widget::~Widget() {}  // ~Widget 的定义要位于 Impl 的定义之后
```

**要点速记**

- Pimpl 惯用法通过降低类的客户和类实现者之间的依赖性，减少了构建遍数。
- 对于采用 `std::unique_ptr` 来实现的 pImpl 指针，需要在类的头文件中声明特种成员函数，并且在实现文件中实现它们，以防止非完整对象造成的编译错误。

## 右值引用、移动语义和完美转发

形参总是左值，即使其型别是右值引用。

``` c++
void f(Widget&& w);
```

形参 `w` 是个左值，即使它的型别是个指涉到 `Widget` 型别对象的右值引用。

### 条款 23 理解 std::move 和 std::forward

 `std::move` 并不进行任何移动，`std::forward` 也不进行任何转发，这两者在运行期都无所作为，他们不会生成任何可执行代码。`std::move` 和 `std::forward` 都是仅仅执行强制类型转换的函数模板。`std::move` 无条件将实参转换成右值，而 `std::forward` 则仅在某个特定条件满足时才执行同一个强制转换。

如果想取得对某个对象执行移动操作的能力，则不要将它声明为常量，因为针对常量对象执行的移动操作将变换成复制操作。`std::move` 不实际移动任何东西，甚至不保证经过其强制型别转换后的对象具备可移动能力。关于针对任意对象实施过 `std::move` 的结果，唯一可以确定的是，该结果是个右值。

`std::forward` 是由条件强制类型转换，仅当其实参是使用右值完成初始化时，它才会执行向右值型别的强制型别转换。`std::forward` 如何分辨实参是通过左值还是右值完成了初始化呢？原因见条款 28。

**要点速记**

- `std::move` 实施的是无条件的向右值型别的强制型别转换。就其本身而言，它不会执行移动操作。
- 仅当传入的实参被绑定到右值时，`std::forward` 才针对该实参实施向右值型别的强制类型转换。
- 在运行期，`std::move` 和 `std::forward` 都不会做任何操作。

### 条款 24 区分万能引用和右值引用

`T&&` 有两种不同的含义。一种含义是右值引用，它们仅仅会绑定到右值，其主要的存在理由是识别出可移动对象。另一种含义则表示其既可以是右值引用，也可以是左值引用，二者居一。带有这种含义的引用在代码中形如右值引用，但它们可以像左值引用一样运作，这种双重特性使之既可以绑定到右值，也可以绑定到左值，这种引用叫做万能引用。

万能引用有两种常见使用场景：

一是函数模板的形参

``` c++
template<typename T>
void f(T&& param); // param 是个万能引用
```

二是 `auto` 声明

``` c++
auto && var2 = var1;  // var2 是个万能引用
```

相同之处在于它们都涉及型别推导。`param` 和 `var2` 的型别都是经过推导得到的。

如果你看到了 `T&&` 但是却没有涉及型别推导，那么你看到的就是个右值引用。

```c++
void f(Widget&& param); // 右值引用

Widget&& var1 = Widget(); // 右值引用
```

因为万能引用是个引用，所以初始化是必须的。万能引用的初始化物会决定它代表的是个左值还是右值引用。如果初始化物是右值，万能引用就会对应到一个右值引用，如果初始化物是个最值，万能引用就对应到一个左值引用。对于作为函数形参的万能引用而言，初始化物在调用处提供。

``` c++
template<typename T>
void f(T&& param);  // param 是个万能引用

Widget w;
f(w);  // 左值被传递给 f，param 的型别是 Widget&, 即一个左值引用

f(std::move(w));  // 右值被传给 f，param 的型别是 Widget&&, 即一个右值引用
```

若要使一个引用成为万能引用，其涉及型别推导是必要条件，但不是充分条件。引用声明的形式必须形如 `T&&` 才行。

``` c++
template<typename T>
void f(std::vector<T>&& param); // param 是个右值引用
```

即使是一个 `const` 饰词的存在，也会导致一个引用无法成为一个万能引用。

``` c++
template<typename T>
void f(const T&& param);  // param 是个右值引用
```

有些模板里面的引用也未必是右值引用，因为它们没有涉及到型别推导。

``` c++
template<class T, class Allocator = allocator<T>>
class vector {
public:
    void push_back(T&& x);
};
```

`x` 是个右值引用而不是个万能引用。因为 `push_back` 是作为 `vector` 实例的一部分，这个已经被实例化了的模板里面的 `push_back` 并不需要型别推导。

``` c++
template<class T, class Allocator = allocator<T>>
class vector {
public:
    template<class... Args>
    void emplace_back(Args&&... args); // args 是个右值引用
};
```

`emplace_back` 的型别形参 `Args` 独立于 `vector` 的型别形参 T, 所以，`Args` 必须在每次调用 `emplace_back` 的时候进行推导。

**要点速记**

- 如果函数模板形参具备 `T&&` 型别，并且 `T` 的型别是推导而来的，或如果使用 `auto&&` 声明其型别，则该形参或对象就是个万能引用。
- 如果型别声明并不精确地具备 `type&&` 地形式，或者没有型别推导过程，则 `type&&` 就代表右值引用。
- 若采用右值来初始化万能引用，就会得到一个右值引用。若采用左值来初始化万能引用，就会得到一个左值引用。

### 条款 25 针对右值引用实施 std::move，针对万能引用实施 std::forward

当转发右值给其他函数时，应当通过 `std::move` 对其实施向右值地无条件型别转换，因为它们一定绑定到右值。当转发万能引用时，应当通过 `std::forward` 对其实施向右值地有条件地转换，因为它们不一定绑定到右值。

#### RVO

return value optimization. 返回值优化。

编译期如果要在一个按值返回的函数里省略局部对象的复制或者移动，则需要满足两个前提条件：

1. 局部对象型别和函数返回值型别相同
2. 返回的就是局部对象本身。

**编译期实现 RVO 优化的办法就是通过直接在为函数返回值分配的内存上创建函数内部需要返回的的局部对象来避免复制。**

``` c++
#include <iostream>
using namespace std;

struct S {
  S() { cout << "S" << endl; }
  S(const S& s) { cout << "copy ctor" << endl; }
  void operator=(const S& s) { cout << "operator =" << endl; }
  S(const S&& s) { cout << "move ctor" << endl; }
  ~S() {cout << "~S" << endl; }

  int n;
};

S make_s() {
  S s;
  return move(s);
}

int main() {
  S s1 = make_s();
  return 0;
}

// 输出结果
S
move ctor
~S
~S
```



``` c++
#include <iostream>
using namespace std;


struct S {
  S() { cout << "S" << endl; }
  S(const S& s) { cout << "copy ctor" << endl; }
  void operator=(const S& s) { cout << "operator =" << endl; }
  S(const S&& s) { cout << "move ctor" << endl; }
  ~S() {cout << "~S" << endl; }

  int n;
};


S make_s() {
  S s;
  return s;
}

int main() {
  S s1 = make_s();

  return 0;
}

// 输出结果
S
~S
```

从上面的例子中可以看到，如果对返回值使用了 `std::move`，反而画蛇添足，多用一次移动构造构造了一个临时对象。

但是 RVO 优化是否需要实施由编译器决定，如果不放心编译器，非要使用 `std::move` ，也不是个好主意。因为标准中关于 RVO 的说明后面又接着说明，即使实施 RVO 的前提条件满足，但表一起选择不执行复制省略操作的时候，返回值必须作为右值处理。这样子就等于标准要求，在 RVO 的条件满足下，要么发生复制省略，要么 `std::move` 被隐式地实施于返回地局部对象上。

**要点速记**

- 针对右值引用的最后一次使用实施 `std::move`，针对万能引用的最后一次使用实施 `std::forward`。
- 作为按值返回的函数的右值引用和万能引用，依上一条所述采取相同行为。
- 若局部对象可能适用于返回值优化，则请勿针对其实施 `std::move` 或 `std::forward`。



### 条款 26 避免依万能引用型别进行重载

形参为万能引用的函数，是 C++ 中最贪婪的。它们会在具现过程中，和几乎任何实参型别都产生精确匹配。这就是为何把重载和万能引用这两者结合起来几乎总是馊主意。



### 条款 27 熟悉依万能引用型别进行重载的替代方案

- 舍弃重载
- 传递 `const T&` 型别的形参
- 传值
- 标签分派，就是说除了万能引用形参，再加个其他非万能引用型别的形参
- 使用 `std::enable_if` 对接受万能引用的模板施加限制

**要点速记**

- 经由 `std::enable_if` 对模板施加限制，就可以将万能引用和重载一起使用，不过这种计数控制了编译器可以调用到接受万能引用的重载版本的条件。



### 条款 28 理解引用折叠

条款 23 提到，实参在传递给函数模板时，推导出来的模板形参会将实参是左值还是右值的信息编码到结果型别中，但是并未提及到，这个编码操作只有在实参被用以初始化的形参为万能引用时才会发生。

以下面为例：

``` c++
Widget widgetFactory();  // 返回右值的函数

Widget w;

```



引用折叠规则：

如果任一引用为左值引用，则结果为左值引用。否则（即两个皆为右值引用），结果为右值引用。









































