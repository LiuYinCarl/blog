# gcc 标准库的虚假唤醒问题

**用到的工具**

- gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
- clang version 10.0.0-4ubuntu1 



## 代码

``` c++
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unistd.h>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

int main() {
    std::unique_lock<std::mutex> lck(mtx);

    while(!ready) {
        printf("before\n");
        cv.wait(lck);
        // cv.wait(lck, []{ return ready; });
        printf("after\n");
    }

    lck.unlock();
    return 0;
}
```



上面这段代码在实际执行中效果如下：

``` bash
before
after
before
after
before
after
before
after
before
after
... ...
```

十分快速不断的输出 `before` 和 `after`。

代码里面并没有调用 `notify_*` 函数,   `cv.wait` 却频繁的返回，这就是虚假唤醒的一种，另一种是调用了一次 `notify` 函数想要唤醒一个线程，却唤醒了多个线程。

定义如下：

[wikipedia Spurious wakeup](https://en.wikipedia.org/wiki/Spurious_wakeup)

摘录一段如下：

> A **spurious wakeup** happens when a thread wakes up from waiting on a [condition variable](https://en.wikipedia.org/wiki/Condition_variable) that's been signaled, only to discover that the condition it was waiting for isn't satisfied. It's called spurious because the thread has seemingly been awakened for no reason. But spurious wakeups don't happen for no reason: they usually happen because, in between the time when the condition variable was signaled and when the waiting thread finally ran, another thread ran and changed the condition. There was a [race condition](https://en.wikipedia.org/wiki/Race_condition) between the threads, with the typical result that sometimes, the thread waking up on the condition variable runs first, winning the race, and sometimes it runs second, losing the race.
>
> On many systems, especially multiprocessor systems, the problem of spurious wakeups is exacerbated because if there are several threads waiting on the condition variable when it's signaled, the system may decide to wake them all up, treating every `signal( )` to wake one thread as a `broadcast( )` to wake all of them, thus breaking any possibly expected 1:1 relationship between signals and wakeups.[[1\]](https://en.wikipedia.org/wiki/Spurious_wakeup#cite_note-1) If there are ten threads waiting, only one will win and the other nine will experience spurious wakeups.
>
> To allow for implementation flexibility in dealing with error conditions and races inside the operating system, condition variables may also be allowed to return from a wait even if not signaled, though it is not clear how many implementations actually do that. In the Solaris implementation of condition variables, a spurious wakeup may occur without the condition being signaled if the process is signaled; the wait system call aborts and returns `EINTR`.[[2\]](https://en.wikipedia.org/wiki/Spurious_wakeup#cite_note-2) The Linux pthread implementation of condition variables guarantees it will not do that.[[3\]](https://en.wikipedia.org/wiki/Spurious_wakeup#cite_note-3)[[4\]](https://en.wikipedia.org/wiki/Spurious_wakeup#cite_note-4)
>
> Because spurious wakeups can happen whenever there's a race and possibly even in the absence of a race or a signal, when a thread wakes on a condition variable, it should always check that the condition it sought is satisfied. If it's not, it should go back to sleeping on the condition variable, waiting for another opportunity.

后两段里面提到了wait 没有被 `notify` 但是线程仍然被唤醒的情况，提示我们在被唤醒后再此检查下条件。所以一般的写法就是就是在循环里面调用`wait` 或者直接使用我上面代码里面注释掉的写法（给 wait 传一个 lambda 函数）。

`pthread_cond_wait` 的 [man page](https://linux.die.net/man/3/pthread_cond_wait) 也提到了这种情况

> When using condition variables there is always a Boolean predicate involving shared variables associated with each condition wait that is true if the thread should proceed. Spurious wakeups from the *pthread_cond_timedwait*() or *pthread_cond_wait*() functions may occur. Since the return from *pthread_cond_timedwait*() or *pthread_cond_wait*() does not imply anything about the value of this predicate, the predicate should be re-evaluated upon such return.



wiki 里面提到了 pthread 不会有这种虚假唤醒，尝试一下

``` c++
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
pthread_cond_t cv;
bool ready = false;

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cv, NULL);

    pthread_mutex_lock(&mutex);
    while (!ready) {
        printf("before\n");
        pthread_cond_wait(&cv, &mutex);
        printf("after\n");
    }

    pthread_mutex_unlock(&mutex);
    return 0;
}
```

输出结果：

``` bash
before
```

确实没有问题。

用 clang 测试下第一段代码，也不存在这个问题，所以可能和 gcc 的实现有关。

为了避免这个问题，一定要记得在 `wait` 返回之后再检查一遍条件。