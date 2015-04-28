一些奇技淫巧
===

- [位操作](tips/C++按位操作符.md)
- [利用python](tips/python.md)

利用def来控制编译是否使用freopen
---

编译的时候加上`-DDEBUG`选项就可以控制`freopen()`

```c
#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
#ifdef DEBUG
    freopen("input", "r", stdin);
#endif
    return 0;
}
```

使用const定义常量，而非def
---

使用const好处在于，可以确定变量的类型，而不是单纯的一段代码。


段错误和栈溢出
---

使用`size`命令来查看执行文件中段大小
```
   text	   data	    bss	    dec	    hex	filename
   1320	    280	      4	   1604	    644	3-8
```
分别是正文段，数据段和bss段。

此外，**局部变量**也是存放在堆栈段的，所以栈溢出不见得是递归调用过多，也可能是局部变量太大（Stack Overflow)。

ulimit 查看栈大小
---

Linux的栈大小通过ulimit命令修改，不过在比赛中似乎是不允许的。
使用`ulimit -s`命令查看栈大小，单位是KB

INF的取值
---

一般是0x3f3f3f3f, 可以用memset来赋值

assert.h
---

利用assert.h调试，通过检测变量值来确定程序运行过程中的问题

```c
#include <stdio.h>
#include <assert.h>

int main()
{
    int x = -1;
    assert(x > 0);
    return 0;
}
```

printf的进制利用
---

x, o, d

```c
// 大写小写16进制
printf("%X", d);
printf("%x", d);

// 效果不同
printf("%02X", d);
printf("%.2X", d);
```
