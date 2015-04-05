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
