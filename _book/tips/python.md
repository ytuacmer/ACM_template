python科学计算不是没有依据的= =特别大型的数据需要好好计算一下, 但是一般的验证,生成测试数据神马的用python真是再方便不过了.

进制转换
---

使用Python内置函数：`bin()`、`oct()`、`int()`、`hex()`可实现进制转换。

其中`int([number | string[, base]])`可以转换其他进制.比如8进制转换到二进制,我们这样`bin(int(x,8))`.

着实有用.


Math库的使用
---

我们依据素数定理求素数个数 -- 一般要使用这个定理的时候int值会比较大.

```python
import math

# 求lnx的值
print math.log(x, math.e)
```

日后使用到的现在没有想到的,会陆续添加.
