STL的相关模板
===

- [set](#set)
- [multiset](#multiset)
- [map](#map)
- [queue](#queue)
- [stack](#stack)
- [sort](#sort)
- [unique](#unique)
- [二分查找](#二分查找)
- next_permutition()
- [串处理函数](#串处理函数)
- [cctype](#cctype)

queue
---

```c

queue <vector> q;

q.push();
q.pop();

```


set
---

```c

set <vector> s;

// 清空
s.clear();

// 寻找v
s.count(v);

// 添加
s.insert(v);

```


Sort
---

Sort中cmp的写法

```c

int cmp_char(const void * _a, const void * _b)
{
    char * a = (char*) _a;
    char * b = (char*) _b;
    return *a - *b;
}

int cmp_string(const void *_a, const void *_b)
{
    char * a = (char*) _a;
    char * b = (char*) _b;
    return strcmp(a, b);
}

//也可以直接放一个数据类型。。。
```

unique
---

去重函数。返回last元素。事实上并没有删除，仅仅是将重复元素移到了数组的末端

```c
unique(a, a+n);
```
二分查找
---

```c
// STL 二分查找数组中>=value的第一个元素的位置，如果没有，返回n
// 前闭后开[a, n)
lower_bound(a, a+n, value)

// 反之，upper_bound
upper_bound(a, a+n, value)
```

串处理函数
---

寻找

```c
char *strstr(char *str1, char *str2); 
```


cctype
---


|函数名称	|返回值|
|:----------|:------|
|isalnum()	|如果参数是字母数字，即字母或数字，该函数返回true|
|isalpha()	|如果参数是字母，该函数返回真|
|isblank()	|如果参数是空格或水平制表符，该函数返回true|
|iscntrl()	|如果参数是控制字符，该函数返回true|
|isdigit()	|如果参数是数字（0～9），该函数返回true|
|isgraph()	|如果参数是除空格之外的打印字符，该函数返回true|
|islower()	|如果参数是小写字母，该函数返回true|
|isprint()	|如果参数是打印字符（包括空格），该函数返回true|
|ispunct()	|如果参数是标点符号，该函数返回true|
|isspace()	|如果参数是标准空白字符，如空格、进纸、换行符、回车 、水平制表符或者垂直制表符，该函数返回true|
|isupper()	|如果参数是大写字母，该函数返回true|
|isxdigit()	|如果参数是十六进制的数字，即0～9、a~f、A~F，该函数返回true|
|tolower()	|如果参数是大写字符，则返回其小写，否则返回该参数|
|toupper()	|如果参数是小写字母，则返回其大写，否则返回该参数|
