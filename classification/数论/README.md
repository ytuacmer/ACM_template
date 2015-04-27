总纲
===

- [素数定理](#素数定理)
- [欧几里得公约数](#公约数)
- [线性筛素数](#线性筛素数)
- [模算术](#模算术)
- [欧拉函数筛法](#欧拉函数筛法)
- [进制转换](#进制转换)
- [线性筛求莫比乌斯反演](#线性筛求莫比乌斯反演)
- [勾股数](#勾股数)


素数定理
---

$ x/lnx $ 含义为不超过x的素数的个数，是一个近似值，比实际值要小

公约数
---

直接采用白书的算法了..

```cpp
lln gcd(lln a, lln b)
{
    return b == 0? a : gcd(b, a%b);
}

// ax + by = d
void gcd(lln a, lln b, lln &d, lln &x, lln &y)
{
    if(!b) { d = a; x = 1; y = 0; }
    else { gcd(b, a%b, d, y, x);  y-= x*(a/b);  }
}
```

线性筛素数
---

推荐使用2，代码相对清晰。

```cpp
// 1.
#define N 10000
int prime[N];
bool isprime[N];  

void makeprime()
{ 
    // 线性筛素数  
    memset(isprime, 1, sizeof(isprime));  
    int i, j;  
    int num = 0;  
    for(i = 2 ; i <= N; i++)  
    {  
        if(isprime[i])  
            prime[num++] = i;  
        for(j = 0; j < num && i * prime[j] <= N; j++)  
        {  
            isprime[i * prime[j]] = 0;  
            if(i % prime[j] == 0) break;  
        }  
    }  
}  

// 2.
const int maxn = 10000000 + 10;
const int maxp = 700000;

int vis[maxn];
int prime[maxp];

// 筛素数
void sieve(int n) 
{
    int m = (int) sqrt(n+0.5);
    memset(vis, 0, sizeof(vis));
    for(int i = 2; i <= m;i ++) if(!vis[i])
        for(int j = i*i; j <= n; j+=i) vis[j] = 1;
}

// 生成素数表
int gen_primes(int n)
{
    sieve(n);
    int c = 0;
    for(int i = 2; i <= n; i++) if(!vis[i])
        prime[c++] = i;
    return c;
}


// 3. bitset速度打
const int N = 10000010;  
  
bitset<N> prime;  
LL phi[N];  
LL f[N];  
int p[N];  
int k;  
  
void isprime()  
{  
    k = 0;  
    prime.set();  
    for(int i=2; i<N; i++)  
    {  
        if(prime[i])  
        {  
            p[k++] = i;  
            for(int j=i+i; j<N; j+=i)  
                prime[j] = false;  
        }  
    }  
}  
```

模算术
---

1. 快速幂模

```c
ll pow_mod(ll x, ll k) {
    ll ans = 1;
    x %= p;
    while (k) {
        if (k&1) ans = ans * x % p;
        x = x * x % p;
        k >>= 1;
    }
    return ans;
}
```

2. 另一种快速，含义相同

```c
typedef long long ll;

ll mul_mod(ll a, ll b, int n)
{
    return a*b%n;
}

ll pow_mod(ll a, ll p, ll n)
{
    if(p == 0) return 1;
    ll ans = pow_mod(a, p/2, n);
    ans = ans * ans % n;
    if(p %2 == 1) ans = ans * a % n;
    return ans;
}
```


整数位数
---

    // 整数位数
    int cal(int a)
    {
        if(a == 0) return 0;
        return (int) log10( (double) a)+1;
    }

进制转换
===

除了以下方法以外，还有

```c
printf("%x"); // 16
printf("%o"); // 8
printf("%d"); // 10
```
这些方法。更改X即可输出大写字母，增加ll或者I64就可以使用大范围。

b进制转换为10进制
---

```c
/**
 * c为数字，b为进制
 */
void trans(char *c, int b)
{
    // 输入数字不正确的可能处理没有添加
    int len = strlen(c);
    int j, temp, tt;
    int res = 0;
    temp = pow(b, len-1);
    for(j = 0; j < len; j++)
    {
        tt = c[j] - '0';
        res += tt * temp;
        temp /= b;
    }

    printf("%d\n", res);
}
```

十进制转换为b进制
---

```c
/**
 * 模拟手算
 * @param b, c
 * b为int型进制，c为大数，返回的数值为余数
 * @return rest
 */
int divide(int b , char *c)
{
    int len = strlen(c);
    int i;
    int temp, rest;
    rest = 0;
    for(i = 0; i < len; i++)
    {
        temp = c[i] - '0';
        rest = rest * 10 + temp;
        temp = rest / b;
        c[i] = temp + '0';
        rest = rest % b;
    }
    return rest;
}

// 判断是否为0
int eval(char *c, char b)
{
    int i = 0;
    int len = strlen(c);
    for(i = 0; i < len; i++)
    {
        if(c[i] != b)
            return 0;
    }
    return 1;
}

void transCHAR(int b, char *c)
{
    int a[100];
    int i = 0;
    /* test(); */
    /* output(c); */

    while(!eval(c, '0'))
    {
        a[i] = divide(b, c);
        i++;
    }

    /* printf("i: %d\n", i); */
    /* printf("b: %d\n", b); */
    /* printf("s: %s\n", c); */

    int j;
    for(j = i-1; j >= 0; j--)
        printf("%d", a[j]);
    printf("\n");
}

```

欧拉函数筛法
---


```c
// 计算单个phi
int euler_phi(int n)
{
    int m = (int) sqrt(n+0.5);
    int ans = n;
    for(int i = 2; i <= m; i++) if(n % i == 0) {
        ans = ans / i *(i-1);
        while(n % i == 0) n /= i;
    }
    if(n > 1) ans = ans / n * (n-1);
    return ans;
}

// 筛欧拉函数
const int maxn = 100000;
int phi[maxn];
void phi_table(int n)
{
    for(int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1;
    for(int i = 2; i <= n; i++) if(!phi[i])
        for(int j = i; j <= n; j += i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i-1);
        }
}

```

线性筛求莫比乌斯反演
---

莫比乌斯反演:

1. $F(n) = ∑_{d|n} f(d)$
2. $f(n) = ∑_{d|n} u(d)F(n/d)$

$u(d)$ 就是莫比乌斯反演函数

u(d)的特性:
1. d = 1, u(d) = 1
2. d = p1p2p3p4..pr, pi均为素数，那么u(d) = (-1)^k
3. 其他情况u(d) = 0
4. $∑_{d|n}u(d) = {1, n=1; 0, n>1}$
5. $∑_{d|n}u(d)/d = euler(n)/n$

```c
void Init()
{
    memset(vis,0,sizeof(vis));
    mu[1] = 1;
    cnt = 0;
    for(int i=2; i<N; i++)
    {
        if(!vis[i])
        {
            prime[cnt++] = i;
            mu[i] = -1;
        }
        for(int j=0; j<cnt&&i*prime[j]<N; j++)
        {
            vis[i*prime[j]] = 1;
            if(i%prime[j]) mu[i*prime[j]] = -mu[i];
            else
            {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
}
```

勾股数
---

給一個任意數對(X,Y)，用以下公式代替
> 
$A = X^2 - Y^2$
$B = 2XY$
$C = X^2 + Y^2$
得出的A,B,C就是一組勾股數。

若 (X,Y) 恰好互質而且一奇一偶，那麼會得到一組(A,B,C)互質的勾股數。
