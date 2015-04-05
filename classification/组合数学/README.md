组合数学
===

- [公式](#公式)


公式
---

1. C(n, 0) = C(n, n) = 1
2. C(n, k) = C(n, n-k)
3. C(n, k) + C(n, k+1) = C(n+1, k+1)
组合数递推公式
4. C(n, k+1）= C(n, k)*(n-k)/(k+1)


全排列
---

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
