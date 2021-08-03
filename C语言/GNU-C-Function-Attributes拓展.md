# GNU-C-Function-Attributes 拓展

在看代码的过程中遇到了一些 GNU C 函数属性拓展，找到了相关文档，暂且记录下来。

这里简短的翻译一下对 Function-Attributes 的介绍。

在 ＧNU C 和 GNU C++ 中，你可以使用函数属性来帮助编译器做优化或者检查代码正确性。举个例子，可以使用 `noreturn` 属性来指定函数永远无返回值，可以使用 `const` 属性来指定函数的返回值取决于函数的参数，可以使用 `format` 属性来说明函数具有 `printf` 风格的参数。

你还可以使用函数属性来控制函数的内存结构，代码生成选项或调用/返回约定。其中许多的属性是属于特定平台的(target-specific)。比如，许多平台支持定义中断处理程序函数的属性，这些函数通常必须遵循特定的寄存器使用和返回约定。这些属性在文档中描述不同平台的小节中进行说明。但是，大多数平台都支持相当多的属性，这些在通用函数属性(Common Function Attributes)一节进行了描述。

函数属性使用函数声明中的 `__attribute__` 关键字来定义。你可以在函数声明中指定多个函数属性，只要在双括号内用用逗号分隔这些属性即可（具体可以看一下这个文档[6.39 Attribute Syntax](https://gcc.gnu.org/onlinedocs/gcc/Attribute-Syntax.html#Attribute-Syntax)）。

有些函数属性具有一个或多个参数，这些参数通过他们在函数参数列表中的位置来引用函数属性的参数，这种函数属性参数被称为位置参数。除非另有说明，否则指定具有指针类型的参数的属性的位置参数也可以指定非静态成员函数中隐式 C++ `this` 参数的相同属性，以及指向指针类型的参数的相同属性。对于普通函数，第一个函数参数指的是参数列表中的第一个参数。在 C++ 非静态成员函数中， 第一个函数参数指的是隐式的 `this` 指针（这一段好绕 ^o^~~）。

函数属性和编译器指令之间存在一些重复，如果使用 GCC，那么尽量使用 `__attribute__`，如果使用其他编译器，可以考虑使用 `#pragma` 编译指令。

[6.33 Declaring Attributes of Functions](https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html)

[6.33.1 Common Function Attributes](https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes)



