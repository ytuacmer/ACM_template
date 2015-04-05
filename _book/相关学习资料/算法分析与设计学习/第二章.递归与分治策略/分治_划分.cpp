#include <iostream>
#include <cstdio>
using namespace std;

/*
 * 求整数n的划分
 * n, m
 * 在整数n的所有划分中， 最大加数 n1<=m 的划分记做p(n, m);
 * 1. p(n, 1) = 1;                    (m == 1)
 * 2. p(n, n) = 1 + p(n, n-1);        (n == m)
 * 3. p(1, m) = 1;                    (n == 1)
 * 4. p(n, m) = p(n, m-1) + p(n-m, m) (n > m > 1)
 * 4的解释
 * n 关于m的划分
 *
 * m + div(n4), m + div(n3)..
 * m-1 + div(n1), m-1 + div(n2) ...
 * m-2 ...
 * 1 + 1 + 1....(m个1)
 */


int p(int n, int m)
{
    if(m == 1 || n == 1)  return 1;
    else if(n == m) return 1+p(n, n-1);
    else if(m >= n) return p(n,n);
    else return p(n , m-1) + p(n-m, m);
}

int main()
{
    //计算n的划分，即为p(n, n);
    cout << p(6,6) << endl;;
    return 0;
}
