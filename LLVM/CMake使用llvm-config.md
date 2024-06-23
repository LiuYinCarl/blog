# CMake 使用 llvm-config

使用 LLVM 是，`llvm-config` 是一个很方便的工具，可以自动设置头文件目录，链接参数和链接库等。
但是如果需要将 `llvm-config` 这个工具接入 CMakeLists.txt 则没有找到资料进行说明，这里分享一下简单的模板。

首先是一个测试代码，主要是测试 LLVM 提供的 `scope_exit` 工具类，代码如下。

```c++
#include "llvm/ADT/ScopeExit.h"
#include <iostream>


int main() {
    auto foo = []() { std::cout << "test scope_exit" << std::endl; };
    auto scope_exit = llvm::make_scope_exit(foo);
}
```

下面是对应的 CMakeLists.txt 脚本。逻辑很简单，分别将 `llvm-config` 提供的三类
参数分别放入三个变量 `llvm_cxxflags`，`llvm_ldflags`，`llvm_libs`，然后将这三个
使用对应的 CMake 函数进行设置。

```cmake
cmake_minimum_required(VERSION 3.10)
project(llvm_learn)

set(CMAKE_CXX_COMPILER clang++)
set(llvm_config /home/kenshin/github/llvm-project/build/bin/llvm-config)

execute_process(
  COMMAND ${llvm_config} --cxxflags
  OUTPUT_VARIABLE llvm_cxxflags
)
execute_process(
  COMMAND ${llvm_config} --ldflags
  OUTPUT_VARIABLE llvm_ldflags
)
execute_process(
  COMMAND ${llvm_config} --libs
  OUTPUT_VARIABLE llvm_libs
)

# strip the string variable
string(STRIP ${llvm_cxxflags} llvm_cxxflags)
string(STRIP ${llvm_ldflags}  llvm_ldflags)
string(STRIP ${llvm_libs}     llvm_libs)

# message("llvm_cxxflags: ${llvm_cxxflags}")
# message("llvm_ldflags : ${llvm_ldflags}")
# message("llvm_libs    : ${llvm_libs}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${llvm_cxxflags}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${llvm_ldflags}")

add_executable(scope_exit scope_exit.cpp)
target_link_libraries(scope_exit ${llvm_libs})
```

最后测试一下这个功能。

```bash
kenshin:~/llvm/learn$ cmake -B build
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/kenshin/llvm/learn/build
kenshin:~/llvm/learn$ cmake --build ./build
[ 50%] Building CXX object CMakeFiles/scope_exit.dir/scope_exit.cpp.o
[100%] Linking CXX executable scope_exit
[100%] Built target scope_exit
kenshin:~/llvm/learn$ ./build/scope_exit
test scope_exit
```