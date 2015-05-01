组合数学
===

- [公式](#公式)
- [特殊的数列](#特殊的数列)
- [全排列](#全排列)
- [排列组合数字](#排列组合数字)
- [斯特林数stirling](#斯特林数stirling)


公式
---

1. C(n, 0) = C(n, n) = 1
2. C(n, k) = C(n, n-k)
3. C(n, k) + C(n, k+1) = C(n+1, k+1)
4. C(n, k+1）= C(n, k)*(n-k)/(k+1)

特殊的数列
---

|名称           |数列                                                   |
|:--------------|:------------------------------------------------------|
|斐波那契数列   |1 1 2 3 5 8                                            |
|卡特兰数       |1 2 5 14 42 132 429 1430 4862 16796 ($4n-6/n*f(n)$)    |

全排列
---

可以使用next_permutation生成

```cpp

template <class Type>
void Perm(Type list[], int k, int m)
{
    if(k > m)//list[m] > list[0];
    {
        for(int i = 0; i <= m ; i++)
            cout << list[i];
        cout << endl;
    }
    else
    {
        for(int i = k; i <= m; i++)
        {
            swap(list[k], list[i]);
            Perm(list, k+1, m);
            swap(list[k], list[i]);
        }
    }
}
```

排列组合数计算
---

```c
#define ll long long 

/**
 * 排列数
 * P(n, k)
 * 特别的，k = n 的时候，返回n!
 */
ll getP(int n, int k)
{
    ll res = 1;
    int b = n-k;
    for(int i = n; i > b; i--)
        res *= i;
    return res;
}

/**
 * 组合数
 * C(n, k)
 * 直接递推，返回需要的那一个
 * 注意溢出问题
 */
const int maxn = 1000;
ll C[maxn][maxn];
ll getC(int n, int k)
{
    if(C[n][0] == 1)
        return C[n][k];

    // 组合数性质
    C[n][0] = C[n][n] = 1;
    for(int i = 0; i < n; i++)
        C[n][i+1] = C[n][i] * (n-i)/(i+1);
    return C[n][k];
}

```

斯特林数stirling
---

- 第一类 stirling数 s(n, k)

n个人分成k组，组内再按特定顺序围圈

也就是分成了k组，组内就像是项链颜色一样，

1. ( {A, B}, {C, D} )
2. ( {B, A}, {C, D} ) 

属于一组

1. ({A}, {B, C, D})
2. ({A}, {B, D, C})

不属于一组

给定 $s(n,0)=0,s(1,1)=1$，有递归关系$s(n,k)=s(n-1,k-1) + (n-1) s(n-1,k)$



- 第二类 stirling数 

S(n, k) 是把p元素集合划分到k个不可区分的盒子里且没有空盒的划分个数。

公式:

$$ S(n, n) = 1 (n >= 0) $$
$$ S(n, 0) = 0 (n >= 1) $$
$$ S(n,k)=k*S(n-1,k)+S(n-1,k-1),\text (1<=k<=n-1) $$
