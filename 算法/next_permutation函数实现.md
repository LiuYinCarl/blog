# next_permutation 函数实现

`next_permutation` 函数的功能是用来获取一个可排序的序列中的更大的下一个序列。例如，我们有一个数组 [1,2,3]，它的 `next_permutation` 就是 [1,2,3]。

下面介绍一个实现 `next_permutation` 函数的算法，以数字序列 `nums =  [4,10,9,8,1]` 为例。

1. 从数组末尾向前找，找到满足条件的值 `i` 满足 `nums[i] < nums[i+1]`，在这个例子中，`i = 0, nums[i] = 4`
2. 从数组末尾向前找，找到满足条件的值 j 满足 `nums[i] < nums[j]`，在这个例子中，`j = 3, nums[j] = 8`
3. 交换 `nums[i]` 和 `nums[j]` 的位置，在这里交换后的序列 `nums = [8,10,9,4,1]`
4. 将从位置 `i + 1` 到末尾的数组翻转，在这里翻转后的序列 `nums = [8,1,4,9,10]`

如果第一步就失败怎么办？如果是这样子的话就说明我们的序列是一个单调递减的序列，已经是这个序列可以组成的最大值了，例如 `nums = [10,9,8,4,1]`。



## next_permutation 的一个实现

> https://en.cppreference.com/w/cpp/algorithm/next_permutation

```c++
template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;
 
    while (true) {
        BidirIt i1, i2;
 
        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2))
                ;
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}
```

