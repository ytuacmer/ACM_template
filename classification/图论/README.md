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
- [最短路Dijkstra](#最短路Dijkstra)
- [负权最短路Bellman-Ford](#负权最短路Bellman-Ford)
- [所有点最短路Floyd](#所有点最短路Floyd)

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

//2. 

// untest
const int maxn = 1000;
const int maxm = 1000; // 最大边数
int n, m;
int first[maxn];
int u[maxm], v[maxm], w[maxm], next[maxm];
void read_graph()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n;i ++) first[i] = -1;
	for(int e = 0; e < m; e++)
	{
		scanf("%d%d%d", &u[e], v&[e], &w[e]);
		next[e] = first[u[e]];
		first[u[e]] = e;
	}
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

- untest

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

- untest

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

- untest

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

最短路Dijkstra
---

- 2.untest

```c

//1. 
const int MAXN = 100010*3;
const int INF  = 1 << 30;

struct HeapNode
{
    int d, u;
    HeapNode() { }
    HeapNode( int _d, int _u ): d(_d), u(_u) { }
    bool operator<( const HeapNode& rhs ) const
    {
        return d > rhs.d;
    }
};

struct Edge
{
    int from, to, dist;
    Edge() { }
    Edge( int f, int t, int d ) : from(f), to(t), dist(d) { }
};

struct Dijkstra
{
    int n, m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool done[MAXN];
    int d[MAXN], p[MAXN];

    void init( int n )
    {
        this->n = n;
        for ( int i = 0; i <= n; ++i ) G[i].clear();
        edges.clear();
        return;
    }

    void AddEdge( int from, int to, int dist )
    {
        edges.push_back( Edge( from, to, dist ) );
        m = edges.size();
        G[from].push_back(m - 1);
        return;
    }

    void dijkstra( int s )
    {
        priority_queue<HeapNode> Q;
        for ( int i = 0; i <= n; ++i ) d[i] = INF;
        d[s] = 0;
        memset( done, 0, sizeof(done) );
        Q.push( HeapNode( 0, s ) );
        while ( !Q.empty() )
        {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if ( done[u] ) continue;
            done[u] = true;
            for ( int i = 0; i < (int)G[u].size(); ++i )
            {
                Edge& e = edges[ G[u][i] ];
                if ( d[e.to] > d[u] + e.dist )
                {
                    d[e.to] = d[u] + e.dist;
                    p[e.to] = G[u][i];
                    Q.push( HeapNode( d[e.to], e.to ) );
                }
            }
        }
        return;
    }
};



//2.

const int maxn = 1000;

typedef pair<int, int> pii;

struct cmp
{
	bool operator() (const int a, const int b)
	{
		return a % 10 > b % 10;
	}
};

priority_queue <int, vector<int>, cmp> q;

void Dijkstra()
{
	bool done[maxn];
	for(int i = 0; i < n; i++) d[i] = (i == 0? 0:INF);
	memset(done, 0, sizeof(done));
	q.push(make_pair(d[0], 0));
	while(!q.empty())
	{
		pii u = q.top(); q.pop();
		int x = u.second;
		if(done[x]) continue;
		done[x] = true;
		for(int e = first[x]; e != -1; e = next[e]) if(d[v[e]] > d[x] + w[e])
		{
			d[v[e]] = d[x] + w[e];
			q.push(make_pair(d[v[e]], v[e]));
		}
	}
}

```

负权最短路Bellman-Ford
---

- untest

```c
// 未使用优先队列的bellman
void bellman()
{
	for(int i = 0; i < n ;i++) d[i] = INF;
	d[0] = 0;
	for(int k = 0; k < n-1; k++)
	{
		for(int i = 0; i< m; i++)
		{
			int x= u[i], y= v[i];
			if(d[x] < INF) d[y] = min(d[y], d[x] + w[i]);
		}
	}
}

//使用有限队列的bellman
void bellman()
{
	queue <int> q;
	bool inq[maxn];
	for(int i = 0; i < n;i ++) d[i] = (i == 0? 0: INF);
	memset(inq, 0, sizeof(inq));
	q.push(0);
	while(!q.empty())
	{
		int x= q.front(); q.pop();
		inq[x] = false;
		for(int e = first[x]; e != -1; e = next[e]) if(d[v[e]] > d[x] + w[e])
		{
			d[v[e]] = d[x] + w[e];d
				if(!inq[v[e]])
				{
					inq[v[e]] = true;
					q.push(v[e]);
				}
		}
	}
}
```

所有点最短路Floyd
---

```c


```
