图论
===


- 使用vector来实现，或者使用new开辟新的数组
- [code](邻接表.cpp)
- [无根树有根树转换](#无根树有根树转换)
- [邻接表存节点](#邻接表存节点)
- [欧拉回路](#欧拉回路)



无根树有根树转换
---

```c
// u为起点，f为父节点，d为深度
void dfs(int u, int f, int d)
{
    fa[u] = f;
    int nc = g[u].size();
    // 叶子节点插入
    if(nc == 1 && d > k) nodes[d].push_back(u);
    for(int i = 0; i < nc; i++) {
        int v = g[u][i];
        if(v != f) dfs(v, u, d+1);
    }
}
```


邻接表存节点
---

```cpp
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
//If G is a tree
//half of n is enough;

#define MAXN 1000
// N 为节点个数
typedef vector <int> vint;
vector <vint> G(MAXN);
//遍历使用clear()函数, 清空使用的空间

void Insert(int a, int i)
{
    G[a].push_back(i);
}

void DFS(int v)
{
    for(int i = 0; i < G[v].size(); i++)
        DFS(G[v][i]);
}

int main()
{
    G.clear();
    return 0;
}

```

存边的写法，类似于哈希表中的拉链法
---

```cpp
struct Arc
{
    int next_arc;
    int point;
};

#define MAXN 1000
#define MAXE 1000

int node[MAXN];
Arc arc[E];

//  以u开始，以v结束
int EdgeCount = 0;;
void AddEdge(int u, int v)
{
    arc[EdgeCount].next_arc = node[u];
    arc[EdgeCount].point = v;
    node[u] = EdgeCount;
    EdgeCount++;
}
```

欧拉回路
---

判断这个图是否是一个能够遍历完所有的边而没有重复。

```c
void euler(int u)
{
    for(int v = 0; v < n; v++) if(G[u][v] && !vis[u][v])
    {
        vis[u][v] = vis[v][u] = 1;
        euler(v);
        printf("%d %d\n", v, u);
    }
}
```

白书给的是printf u v，需要逆序压栈。当然，我们只需要输出就可以了。

