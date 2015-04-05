总纲
===

- [特殊的数列](#特殊的数列)
- [公约数](#公约数)
- [线性筛素数](#线性筛素数)
- [快速幂模](#快速幂模)
- [计算一个数的位数](#计算一个数的位数)
- [大数](#大数)
- [进制转换](#进制转换)
- 欧拉函数筛法


特殊的数列
---

- 卡特兰数: 1 2 5 14 42 132 429 1430 4862 16796 ($4n-6/n*f(n)$)
- 欧拉函数: 1 2 2 4 4 
- 莱布尼兹数列： 1 1 2 3 5 8 13 21 34 55 (递推公式)



公约数
---

```cpp
int gcd(int a, int b)
{
    if(a % b == 0) return b;
    else return gcd(b, a % b);
}
```

线性筛素数
---

```cpp
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
```

快速幂模
---

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

大数
---

```cpp

// 最大大小
const int MAXN = 100;

// 每个
const int DLEN = 100;

class BigNum  
{   
private:   
    int a[12];    //可以控制大数的位数   
    int len;       //大数长度  
public:   
    BigNum(){ len = 1; memset(a,0,sizeof(a)); }   //构造函数  
    BigNum(const int);       //将一个int类型的变量转化为大数  
    BigNum(const char*);     //将一个字符串类型的变量转化为大数  
    BigNum(const BigNum &);  //拷贝构造函数  
    BigNum &operator=(const BigNum &);   //重载赋值运算符，大数之间进行赋值运算  
  
    friend istream& operator>>(istream&,  BigNum&);   //重载输入运算符  
    friend ostream& operator<<(ostream&,  BigNum&);   //重载输出运算符  
  
    BigNum operator+(const BigNum &) const;   //重载加法运算符，两个大数之间的相加运算   
    BigNum operator-(const BigNum &) const;   //重载减法运算符，两个大数之间的相减运算   
    BigNum operator*(const BigNum &) const;   //重载乘法运算符，两个大数之间的相乘运算   
    BigNum operator/(const int   &) const;    //重载除法运算符，大数对一个整数进行相除运算  
  
    BigNum operator^(const int  &) const;    //大数的n次方运算  
    int    operator%(const int  &) const;    //大数对一个int类型的变量进行取模运算      
    bool   operator>(const BigNum & T)const;   //大数和另一个大数的大小比较  
    bool   operator>(const int & t)const;      //大数和一个int类型的变量的大小比较  
  
    void print();       //输出大数  
    int count(int n);
};   

BigNum::BigNum(const int b)     //将一个int类型的变量转化为大数  
{   
    int c, d = b;  
    len = 0;  
    memset(a,0,sizeof(a));  
    while(d > MAXN)  
    {  
        c = d - (d / (MAXN + 1)) * (MAXN + 1);   
        d = d / (MAXN + 1);  
        a[len++] = c;  
    }  
    a[len++] = d;  
}  

BigNum::BigNum(const char*s)     //将一个字符串类型的变量转化为大数  
{  
    int t,k,index,l,i;  
    memset(a,0,sizeof(a));  
    l=strlen(s);     
    len=l/DLEN;  
    if(l%DLEN)  
        len++;  
    index=0;  
    for(i=l-1;i>=0;i-=DLEN)  
    {  
        t=0;  
        k=i-DLEN+1;  
        if(k<0)  
            k=0;  
        for(int j=k;j<=i;j++)  
            t=t*10+s[j]-'0';  
        a[index++]=t;  
    }  
}  

BigNum::BigNum(const BigNum & T) : len(T.len)  //拷贝构造函数  
{   
    int i;   
    memset(a,0,sizeof(a));   
    for(i = 0 ; i < len ; i++)  
        a[i] = T.a[i];   
}   

BigNum & BigNum::operator=(const BigNum & n)   //重载赋值运算符，大数之间进行赋值运算  
{  
    int i;  
    len = n.len;  
    memset(a,0,sizeof(a));   
    for(i = 0 ; i < len ; i++)   
        a[i] = n.a[i];   
    return *this;   
}  

istream& operator>>(istream & in,  BigNum & b)   //重载输入运算符  
{  
    char ch[MAXSIZE*4];  
    int i = -1;  
    in>>ch;  
    int l=strlen(ch);  
    int count=0,sum=0;  
    for(i=l-1;i>=0;)  
    {  
        sum = 0;  
        int t=1;  
        for(int j=0;j<4&&i>=0;j++,i--,t*=10)  
        {  
            sum+=(ch[i]-'0')*t;  
        }  
        b.a[count]=sum;  
        count++;  
    }  
    b.len =count++;  
    return in;  
  
}  

ostream& operator<<(ostream& out,  BigNum& b)   //重载输出运算符  
{  
    int i;    
    cout << b.a[b.len - 1];   
    for(i = b.len - 2 ; i >= 0 ; i--)  
    {   
        cout.width(DLEN);   
        cout.fill('0');   
        cout << b.a[i];   
    }   
    return out;  
}  
  
BigNum BigNum::operator+(const BigNum & T) const   //两个大数之间的相加运算  
{  
    BigNum t(*this);  
    int i,big;      //位数     
    big = T.len > len ? T.len : len;   
    for(i = 0 ; i < big ; i++)   
    {   
        t.a[i] +=T.a[i];   
        if(t.a[i] > MAXN)   
        {   
            t.a[i + 1]++;   
            t.a[i] -=MAXN+1;   
        }   
    }   
    if(t.a[big] != 0)  
        t.len = big + 1;   
    else  
        t.len = big;     
    return t;  
}  

BigNum BigNum::operator-(const BigNum & T) const   //两个大数之间的相减运算   
{    
    int i,j,big;  
    bool flag;  
    BigNum t1,t2;  
    if(*this>T)  
    {  
        t1=*this;  
        t2=T;  
        flag=0;  
    }  
    else  
    {  
        t1=T;  
        t2=*this;  
        flag=1;  
    }  
    big=t1.len;  
    for(i = 0 ; i < big ; i++)  
    {  
        if(t1.a[i] < t2.a[i])  
        {   
            j = i + 1;   
            while(t1.a[j] == 0)  
                j++;   
            t1.a[j--]--;   
            while(j > i)  
                t1.a[j--] += MAXN;  
            t1.a[i] += MAXN + 1 - t2.a[i];   
        }   
        else  
            t1.a[i] -= t2.a[i];  
    }  
    t1.len = big;  
    while(t1.a[t1.len - 1] == 0 && t1.len > 1)  
    {  
        t1.len--;   
        big--;  
    }  
    if(flag)  
        t1.a[big-1]=0-t1.a[big-1];  
    return t1;   
}   
  
BigNum BigNum::operator*(const BigNum & T) const   //两个大数之间的相乘运算   
{   
    BigNum ret;   
    int i,j,up;   
    int temp,temp1;     
    for(i = 0 ; i < len ; i++)  
    {   
        up = 0;   
        for(j = 0 ; j < T.len ; j++)  
        {   
            temp = a[i] * T.a[j] + ret.a[i + j] + up;   
            if(temp > MAXN)  
            {   
                temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);   
                up = temp / (MAXN + 1);   
                ret.a[i + j] = temp1;   
            }   
            else  
            {   
                up = 0;   
                ret.a[i + j] = temp;   
            }   
        }   
        if(up != 0)   
            ret.a[i + j] = up;   
    }   
    ret.len = i + j;   
    while(ret.a[ret.len - 1] == 0 && ret.len > 1)  
        ret.len--;   
    return ret;   
}   

BigNum BigNum::operator/(const int & b) const   //大数对一个整数进行相除运算  
{   
    BigNum ret;   
    int i,down = 0;     
    for(i = len - 1 ; i >= 0 ; i--)  
    {   
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;   
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;   
    }   
    ret.len = len;   
    while(ret.a[ret.len - 1] == 0 && ret.len > 1)  
        ret.len--;   
    return ret;   
}  

int BigNum::operator %(const int & b) const    //大数对一个int类型的变量进行取模运算      
{  
    int i,d=0;  
    for (i = len-1; i>=0; i--)  
    {  
        d = ((d * (MAXN+1))% b + a[i])% b;    
    }  
    return d;  
}  

BigNum BigNum::operator^(const int & n) const    //大数的n次方运算  
{  
    BigNum t,ret(1);  
    int i;  
    if(n<0)  
        exit(-1);  
    if(n==0)  
        return 1;  
    if(n==1)  
        return *this;  
    int m=n;  
    while(m>1)  
    {  
        t=*this;  
        for( i=1;i<<1<=m;i<<=1)  
        {  
            t=t*t;  
        }  
        m-=i;  
        ret=ret*t;  
        if(m==1)  
            ret=ret*(*this);  
    }  
    return ret;  
}  

bool BigNum::operator>(const BigNum & T) const   //大数和另一个大数的大小比较  
{   
    int ln;   
    if(len > T.len)  
        return true;   
    else if(len == T.len)  
    {   
        ln = len - 1;   
        while(a[ln] == T.a[ln] && ln >= 0)  
            ln--;   
        if(ln >= 0 && a[ln] > T.a[ln])  
            return true;   
        else  
            return false;   
    }   
    else  
        return false;   
}  

bool BigNum::operator >(const int & t) const    //大数和一个int类型的变量的大小比较  
{  
    BigNum b(t);  
    return *this>b;  
}  
  
void BigNum::print()    //输出大数  
{   
    int i;     
    cout << a[len - 1];   
    for(i = len - 2 ; i >= 0 ; i--)  
    {   
        cout.width(DLEN);   
        cout.fill('0');   
        cout << a[i];   
    }   
    cout << endl;  
}  

int cc(int n)
{
    int a = 0;
    if(n / 1000 == 5)
        a++;
    n -= n/1000 * 1000;
    if(n / 100 == 5)
        a++;
    n -= n/100 * 100;
    if(n / 10 == 5)
        a++;
    n -= n/10 * 10;
    if(n == 5)
        a++;
    return a;
}

// 计算大数某个数字的个数
int BigNum::count(int n)
{
    int i;
    int sum;
    sum = cc(a[len-1]);
    for(i = len-2; i >= 0; i--)
    {
        sum += cc(a[i]);
    }
    cout << sum;
    return sum;
}
```

欧拉函数
---

```c
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
```
