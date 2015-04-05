#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;

const int SIZE = 1001;
int phi[SIZE];

void init()
{
    int i, j;
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for(int i = 2; i < SIZE; i++) if(!phi[i])
    {
        for(j = i; j < SIZE; j+=i)
        {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i-1);
        }
    }
    return ;
}

int main()
{
    init();
    int n;
    while(~scanf("%d", &n))
    {
        for(int i = 1; i <= n; i++)
        {
            printf(i != n?"%d ":"%d\n", phi[i]);
        }
    }
    return 0;
}
