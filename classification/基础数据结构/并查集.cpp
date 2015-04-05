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
