字符串处理
===

- [比较字典序](#比较字典序)
- [字符串反转](#字符串反转)
- [获取整行](#获取整行)


比较字典序
---

```c
    template <class T>
bool lexicographicallySamller(vector <T> a, vector <T> b)
{
    int n = a.size();
    int m = b.size();
    int i;
    for(i = 0; i < n && i < m; i++)
    {
        if(a[i] < b[i]) return true;
        else if(a[i] > b[i]) return false;
    }
    return (i == n && i < m);
}
```




字符串反转
---

主要涉及了对一个数字的反转

```c

    int b;
    sscanf(num, "%d", &b);
    for(int i = 0; i < len/2 ;i ++)
    {
        char t = num[i];
        num[i] = num[len-1-i];
        num[len-1-i] = t;
    }
    sscanf(num, "%d", &x);

```

获取整行
---

- 使用`cin.getline(str, num, endchar)`函数
- 另外，如果不加上endchar则默认为'\n'

如果使用`fgets(str, num, stdin)`的话：
1. 没有读到\n是不会换行的
2. 没有读完当前行是不会换行的，即$当前行的字符数 > num$
3. 此外，这个函数会将\n读入到str中

