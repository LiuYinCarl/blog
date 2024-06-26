## lua 字符串和时间戳相互转换

## luaforge

该网站收集了各种 Lua 库
[luaforge 程序库](http://luaforge.net/tags/)

## 时间戳转成格式化字符串

直接利用函数 os.date()将时间戳转化成格式化字符串.

```lua
local timestamp = 1561636137;
local strDate = os.date("%Y/%m/%d %H:%M:%S", timestamp)
print("strDate = ", strDate);
```

输出: strDate = 2019/06/27 19: 48: 57 注意'%Y', Y 是大写, 如果是小写的话则输出为: 输出: strDate = 19/06/27 19: 48: 57

## 字符串转化成时间戳

通过 string.find 的模式匹配, 解析子串.

```lua
local strDate = "2019/06/27 19:48:57"
local _, _, y, m, d, hour, min, sec = string.find(strDate, "(%d+)/(%d+)/(%d+)%s*(%d+):(%d+):(%d+)");
print(y, m, d, hour, min, sec);
```

输出: 2019 06 27 19 48 57 这里已经将'y, m, d, hour, min, sec'从 strDate 中分离出来了, 接下来转化为时间戳. 完整代码:

--分离字符串

```lua
local strDate = "2019/06/27 19:48:57"
local _, _, y, m, d, _hour, _min, _sec = string.find(strDate, "(%d+)/(%d+)/(%d+)%s*(%d+):(%d+):(%d+)");

print(y);
print(m);
print(d);
print(_hour);
print(_min);
print(_sec);

--转化为时间戳
local timestamp = os.time({year=y, month = m, day = d, hour = _hour, min = _min, sec = _sec});
print("timestamp = ", timestamp);
```

输出: 2019 06 27 19 48 57 timestamp = 1561636137
