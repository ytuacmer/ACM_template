本文出自[Svitter的blog](http://blog.csdn.net/svitter)

基础数据结构
===

并查集
---
 
- [代码](并查集.cpp)

```cpp
/* from freecode */

#define MAXN 1010	//并查集的大小

int par[MAXN];    //par[x]表示x的父节点
int n;

void Init()    //初始化
{
    int i;
    for(i=0;i<=n;i++)
        par[i] = i;
}

int Find(int x)    //查询x的根节点并路径压缩
{
    if(par[x]!=x)
        par[x] = Find(par[x]);
    return par[x];
}

void Union(int x,int y)    //合并x和y所在集合
{
    par[Find(x)] = Find(y);
}
```

树状数组
---

```cpp
/* from freecode */
#define MAXN 100010

int N;	
int c[MAXN];

int lowbit(int x)
{
    return x & (-x);
}

void add(int d,int x)	//将编号为d的数加x
{
    while(d<=N){
        c[d] += x;
        d += lowbit(d);
    }
}

int sum(int d)		//求出区间[1,d]元素的和
{
    int ans =0;
    while(d>=1){
        ans += c[d];
        d -= lowbit(d);
    }
    return ans;
}
```
