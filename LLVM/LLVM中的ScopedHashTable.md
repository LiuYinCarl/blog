# LLVM 中的 ScopedHashTable

LLVM 在 `llvm/include/llvm/ADT/ScopedHashTable.h` 中实现了一种和作用域关联的 HashTable。
用法如下：

```c++
#include "llvm/ADT/ScopedHashTable.h"
#include <iostream>
#include <string>

int main() {
    llvm::ScopedHashTable<int, std::string> ht;

    {
        llvm::ScopedHashTableScope<int, std::string> scope1(ht);
        ht.insert(42, "in scope1");
        ht.insert(34, "scope1 34");
        std::cout << ht.lookup(42) << std::endl;
        {
            llvm::ScopedHashTableScope<int, std::string> scope2(ht);
            ht.insert(42, "in scope2");
            std::cout << ht.lookup(42) << std::endl;
        }
        std::cout << ht.lookup(42) << std::endl;
    }
}
```

执行结果如下：

```bash
kenshin:~/llvm/learn$ ./build/scoped_hash_table
in scope1
in scope2
in scope1
```

这个机制的实现原理也很简单，主要用到三个类。

- `ScopedHashTableVal` 用来保存实际的 key 和 value。
- `ScopedHashTableScope` 和作用域进行关联，在嵌套作用域中每一个作用域对应一个该对象。
- `ScopedHashTable` 存储数据以及和实际的 HashTable。

以上面的代码作为例子，简单说明一下流程。`llvm::ScopedHashTable<int, std::string> ht` 构造了
一个 `ScopedHashTable` 对象。`llvm::ScopedHashTableScope<int, std::string> scope1(ht);`
构造了一个 `ScopedHashTableScope`，并且 `scope1` 表示当前生效的 scope。往 `ht` 内插入元素其实
会在 `scope1` 对象中记录一个插入链表，并且将对应的数据存储到 `ht` 内的实际哈希表中，依靠这个链表，
可以知道在当前作用域内实际新增了哪些 key 和 value 组（也就是 ScopedHashTableVal 对象）。
这一个可以看源码 `insert` 函数增强理解。

`ht.lookup(42)` 表示在 `ht` 内查询 key 对应的 value。那么是如何实现在不同作用域中查找同一个 key
返回不同 value 的呢。这个其实是在插入这一步就进行了实现。

```txt



```