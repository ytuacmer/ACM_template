图论
===

- 使用vector来实现，或者使用new开辟新的数组
- [code](邻接表.cpp)
- [无根树有根树转换](#无根树有根树转换)
- [邻接表存节点](#邻接表存节点)
- [欧拉回路](#欧拉回路)
- [连通分量](#连通分量)
- [二分图判定](#二分图判定)
- [无向图的割顶和桥](#无向图的割顶和桥)
- [无向图的双连通分量](#无向图的双连通分量)

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

连通分量
---

还可以使用并查集搞定，不会爆栈

```c
int current_c;

void dfs(int u)
{
	vis[u] = 1;
	// PREvisit
	cc[u] = current_cc;
	int d = G[u].size();
	for(int i = 0; i< d; i++)
	{
		int v = G[u][v];
		if(!vis[v]) dfs(v);
	}
}


// 判断连通分量的个数
void find_cc()
{
	current_cc = 0;
	memset(vis, 0, sizeof(vis));
	for(int i = 0; i < n; i++)
	{
		current_cc++;
		dfs(u);
	}
}
```

二分图判定
---

二分图判定并且着色。把图分成不相关的两个部分

常与最大[独立集](#独立集)共同

```c
// 二分图的判定
// 初始化0, 黑色1, 白色2
const int maxn = 1000;
int color[maxn];
bool biparitite(int u) {
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(color[v] == color[u]) return false; // 着色冲突
		if(!color[v]) {
			color[v] = 3 - color[u]; 			// 给结点v着相反颜色
			if(!bipartite(v)) return false;
		}
	}
}
```

独立集
---

最大独立集定义：从V个点中选出k个点，使得这k个点互不相邻。 那么最大的k就是这个图的最大独立数。
1. 二分匹配得到最大匹配数（即最小覆盖数）
2. 最大独立集 = 顶点数 - 最小覆盖数


无向图的割顶和桥
---

无向图G，删除点u，连通分量数目增加，则u为图的关节点（割顶）。
**对于连通图，割顶删除后图就不连通**

iscut 为判定是否割点

```c
// 无向图的割顶和桥

int dfs_clock;

void init()
{
	dfs_clock = 0;
	memset(pre, 0, sizeof(pre));
}

int dfs(int u, int fa) {
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(!pre[v]) {
			child++;
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if(lowv >= pre[u]) {
				iscut[u] = true;
			}
		}
		else if(pre[v] < pre[u] && v != fa) {
			lowu = min(lowu, pre[v]);
		}
	}
	if(fa < 0 && child == 1) iscut[u] = 0;
	low[u] = lowu;
	return lowu;
}
```

无向图的双连通分量
---

```c
int pre[maxn], iscut[maxn], bccno[maxn], dfs_clock, bcc_cnt;
vector <int> G[maxn], bcc[maxn];

stack <Edge> s;

int dfs(int u, int fa)
{
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;
	for(int i = 0; i< n ;i++)
	{
		int v = G[u][i];
		Edge e = (Edge){u, v};
		if(!pre[u]) { // 未访问
			S.push(e);
			child++;
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if(lowv >= pre[u]) {
				iscut[u] = true;
				bcc_cnt++; bcc[bcc_cnt].clear();
				for(;;) {
					Edge x = S.top(); S.pop();
					if(bccno[x.u] != bcc_cnt) {
						bcc[bcc_cnt].push_back(x.u);
						bccno[x.u] = bcc_cnt;
					}
					if(bccno[x.v] != bcc_cnt) {
						bcc[bcc_cnt].push_back(x,v);
						bccno[x.v] = bcc_cnt;
					}
					if(x.u == u && x.v == v) break;
				}
			}
		}
		else if(pre[v] < pre[u] && v != fa)
		{
			S.push(e);
			lowu = min(lowu, pre[v]);
		}

		if(fa < 0 && child == 1) iscut[u] = 0;
		return lowu;
	}
}

// Init
void find_cc(int n)
{
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	dfs_clock = bcc_cnt = 0;
	for(int i = 0; i < n; i++)
		if(!pre[i]) dfs(i, -1);
}
```
