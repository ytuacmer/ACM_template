字符串处理
===

- [比较字典序](#比较字典序)
- [字符串反转](#字符串反转)
- [获取整行](#获取整行)
- [KMP](#KMP)


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

KMP
---

用的是白书kmp，此外P为短串，T为长串，f为next数组

KMP 本质也是自动机，此处为MP算法，处理失效函数才是KMP

```c
// 生成next数组，即为f数组
void getFail(char *P, int *f)
{
    int m = strlen(P);
    f[0] = 0; f[1] = 0;
    for(int i = 1; i < m; i++)
    {
        int j = f[i];
        while(j && P[i] != P[j]) j = f[j];
        f[i+1] =  P[i] == P[j] ? j+1 : 0;
    }
}

int find(char *T, char *P, int *f)
{
    int n = strlen(T), m = strlen(P);
    getFail(P, f);
    int j = 0;
    for(int i = 0; i < n; i++) {
        while(j && P[j] != T[i]) j = f[j];
        if(P[i] == T[i]) j++;
        if(j == m) return i-m+1; // 找到了
    }
    return -1; // 没找到
}
```
