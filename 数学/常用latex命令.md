### 换行

```latex
% 使用 \ 符号
\begin{align}
a=1+2+3+4+5 \\
=6+9
\end{align}
```

$$
\begin{align}
a=1+2+3+4+5 \\
=6+9
\end{align}
$$



### 左对齐

```latex
% 使用 & 符号
\begin{align}
a&=1+2+3+4+5 \\
&=6+9
\end{align}
```

$$
\begin{align}
a&=1+2+3+4+5 \\
&=6+9
\end{align}
$$



### 右对齐

``` latex
% 使用 \ 符号
\begin{align}
a=1+2+3+4+5 \\
=6+9
\end{align}
```

$$
% 使用 \ 符号
\begin{align}
a=1+2+3+4+5 \\
=6+9
\end{align}
$$

## 矩阵

[如何用latex编写矩阵](https://zhuanlan.zhihu.com/p/266267223)

```latex
% 使用 matrix 符号
\begin{matrix}
a & b
c & d
\end{matrix}

% 使用 pmatrix 符号
\begin{pmatrix}
a & b
c & d
\end{pmatrix}

% 使用 bmatrix 符号
\begin{bmatrix}
a & b
c & d
\end{bmatrix}

% 使用 Bmatrix 符号
\begin{Bmatrix}
a & b
c & d
\end{Bmatrix}

% 行列式使用 vmatrix 符号
\begin{vmatrix}
a & b
c & d
\end{vmatrix}

% 范数使用 Vmatrix 符号
\begin{Vmatrix}
a & b
c & d
\end{Vmatrix}
```


$$
% 使用 matrix 符号
\begin{matrix}
a & b \\
c & d
\end{matrix}

 \\
% 使用 pmatrix 符号
\begin{pmatrix}
a & b \\
c & d
\end{pmatrix}

 \\
% 使用 bmatrix 符号
\begin{bmatrix}
a & b \\
c & d
\end{bmatrix}

 \\
% 使用 Bmatrix 符号
\begin{Bmatrix}
a & b \\
c & d
\end{Bmatrix}

 \\
% 行列式使用 vmatrix 符号
\begin{vmatrix}
a & b \\
c & d
\end{vmatrix}

 \\
% 范数使用 Vmatrix 符号
\begin{Vmatrix}
a & b \\
c & d
\end{Vmatrix}
$$

## 多行公式对齐

``` latex
% 使用 & 符号放在公式的最前面
\begin{align}
& A(A^{-1}) = (A^{-1})A = I
\\
& (ABC)^{-1} = C^{-1}B^{-1}A^{-1}

\end{align}
```

$$
% 使用 & 符号放在公式的最前面
\begin{align}
& A(A^{-1}) = (A^{-1})A = I
\\
& (ABC)^{-1} = C^{-1}B^{-1}A^{-1}

\end{align}
$$





## 矩阵上标的写法

``` latex
\begin{align}
\begin{bmatrix} 
a & b & c \\
d & e & f \\
g & h & i \\
\end{bmatrix} ^ \mathrm{T}
\end{align}
```

$$
\begin{align}
\begin{bmatrix} 
a & b & c \\
d & e & f \\
g & h & i \\
\end{bmatrix} ^ \mathrm{T}
\end{align}
$$



## 插入空行

```latex
% 写法1，手动控制行距
\\[10pt]

```



## 公式撇号角标

```latex
\begin{align}
r{'}
\end{align}
```


$$
\begin{align}
r{'}
\end{align}
$$
