# 获取 UTF8 字符串的第一个可读字符

近期有个从 UTF8 字符串中获取第一个可读的字符的需求，所以实现了下面这个函数，包含测试代码。

## UTF8 编码规则

互联网的普及，强烈要求出现一种统一的编码方式。UTF-8 就是在互联网上使用最广的一种 Unicode 的实现方式。其他实现方式还包括 UTF-16（字符用两个字节或四个字节表示）和 UTF-32（字符用四个字节表示），不过在互联网上基本不用。重复一遍，这里的关系是，UTF-8 是 Unicode 的实现方式之一。

UTF-8 最大的一个特点，就是它是一种变长的编码方式。它可以使用1~4个字节表示一个符号，根据不同的符号而变化字节长度。

UTF-8 的编码规则很简单，只有二条：

1）对于单字节的符号，字节的第一位设为0，后面7位为这个符号的 Unicode 码。因此对于英语字母，UTF-8 编码和 ASCII 码是相同的。

2）对于n字节的符号（n > 1），第一个字节的前n位都设为1，第n + 1位设为0，后面字节的前两位一律设为10。剩下的没有提及的二进制位，全部为这个符号的 Unicode 码。

下表总结了编码规则，字母x表示可用编码的位。

```
Unicode符号范围     |        UTF-8编码方式
(十六进制)          |              （二进制）
--------------------+---------------------------------------------
0000 0000-0000 007F | 0xxxxxxx
0000 0080-0000 07FF | 110xxxxx 10xxxxxx
0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
```

本节内容引用自 [字符编码笔记：ASCII，Unicode 和 UTF-8](https://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html)

## 实现及测试代码

```c++
#include <iostream>
#include <string>
#include <vector>

// 从 UTF8 字符串中取出第一个可读的字符
std::string get_frist_word_from_utf8(std::string utf8_str) {
    size_t len = utf8_str.size();
    if (len == 0) return "";
    // first char
    unsigned char c = utf8_str[0];
    
    if ((c >> 7) == 0x00 &amp;&amp; len >= 1) return utf8_str.substr(0, 1);
    if ((c >> 5) == 0x06 &amp;&amp; len >= 2) return utf8_str.substr(0, 2);
    if ((c >> 4) == 0x0E &amp;&amp; len >= 3) return utf8_str.substr(0, 3);
    if ((c >> 3) == 0x1E &amp;&amp; len >= 4) return utf8_str.substr(0, 4);
    return "";
}

// build command: g++ get_first_readable_word.cpp -std=c++11 &amp; &amp; ./a.out
int main() {
    std::vector<std::string> test_case;
    test_case.push_back(std::string("a你好"));
    test_case.push_back(std::string("我是谁"));
    test_case.push_back(std::string("龙争虎斗"));
    test_case.push_back(std::string("------"));
    test_case.push_back(std::string("*****"));
    test_case.push_back(std::string("&amp;&amp;设施"));
    test_case.push_back(std::string("。哈哈"));
    test_case.push_back(std::string("觀看立即"));
    test_case.push_back(std::string(""));

    for (auto&amp; single_case : test_case) {
        std::cout << single_case.size() << "\t| " << get_frist_word_from_utf8(single_case) << "\t| " << single_case << std::endl;
    }
}

```

```bash
# 测试结果
$ g++ get_first_readable_word.cpp -std=c++11 && ./a.out 
7       | a     | a你好
9       | 我    | 我是谁
12      | 龙    | 龙争虎斗
6       | -     | ------
5       | *     | *****
8       | &     | &&设施
9       | 。    | 。哈哈
12      | 觀    | 觀看立即
0       |       | 
```

## 参考资料

[字符编码笔记：ASCII，Unicode 和 UTF-8](https://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html)
