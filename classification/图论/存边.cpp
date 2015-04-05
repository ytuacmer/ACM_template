#include <iostream>
#include <cstdio>

using namespace std;

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

int main()
{
    return 0;
}
