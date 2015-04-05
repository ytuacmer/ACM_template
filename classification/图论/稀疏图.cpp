#include <stdio.h>

using namespace std;


const int MAXN = 1000;
const int MAXM = 1000;
int n, m;
int first[MAXN];
int u[MAXM], v[MAXM], w[MAXM], next[MAXM];
void read_graph()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) first[i] = -1;
    for(int e = 0; e < m; e++)
    {
        scanf("%d%d%d", &u[e], &v[e], &w[e]);
        next[e] = first[u[e]];
        first[u[e]] = e;
    }
}



int main()
{

    return 0;
}

