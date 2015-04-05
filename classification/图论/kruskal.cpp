// 最小生成树kruskal算法

const int maxn = 1000;

int p[maxn]; // 初始化并查集
int w[maxn]; // 边的权重
int r[maxn]; // 边的序号

int u[maxn]; // 边序号对应那个点
int v[maxn];

int cmp(const int i, const int j){ return w[i] < w[j]; }
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

int kruskal()
{
    int n, m;
    int ans = 0;
    for(int i = 0; i < n; i++) p[i] = i; // 初始化并查集
    for(int i = 0; i < m; i++) r[i] = i; // 初始化边序号

    sort(r, r+m, cmp); // 给边排序
    for(int i = 0; i < m; i++)
    {
        // 找出当前边两个端点所在的集合编号
        int e = r[i]; int x = find(u[e]); int y = find(v[e]); 

        // 在不同的集合，合并
        if(x != y) { ans += w[e]; p[x] = y;}
    }
    return ans;
}
