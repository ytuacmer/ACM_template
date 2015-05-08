基础数据结构
===

- [大数](#大数) 
- [并查集](#并查集)
- [树状数组](#树状数组)

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

并查集
---

判断是否同一集合的数据结构，不过可以使用set来替代 -- 不过似乎就违背了初衷了
 
- [代码](并查集.cpp)

```cpp
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
```

树状数组
---

```cpp
/* from freecode */
#define MAXN 100010

int N;	
int c[MAXN];

int lowbit(int x)
{
    return x & (-x);
}

void add(int d,int x)	//将编号为d的数加x
{
    while(d<=N){
        c[d] += x;
        d += lowbit(d);
    }
}

int sum(int d)		//求出区间[1,d]元素的和
{
    int ans =0;
    while(d>=1){
        ans += c[d];
        d -= lowbit(d);
    }
    return ans;
}
```

Karatsuba快速相乘算法
---

- 用于计算两个超大数字的快速相乘法则
- 来自 http://blog.csdn.net/sunnyyoona/article/details/43234889

```c
/*********************************
*   日期：2015-01-29
*   作者：SJF0115
*   题目: Karatsuba快速相乘算法
*   博客：
**********************************/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// given two unequal sized bit strings, converts them to
// same length by adding leading 0s in the smaller string. Returns the
// the new length
int MakeSameLen(string& num1,string& num2){
    int len1 = num1.length();
    int len2 = num2.length();
    if(len1 < len2){
        for(int i = 0;i < len2 - len1;++i){
            num1 = "0" + num1;
        }//for
        return len2;
    }//if
    else{
        for(int i = 0;i < len1 - len2;++i){
            num2 = "0" + num2;
        }//for
        return len1;
    }//else
}
// big number minus function
string MinusString(string num1, string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    // 相等
    if(num1 == num2){
        return "0";
    }//if
    // 正负
    bool positive = true;
    if(len1 < len2 || (len1 == len2 && num1 < num2)){
        positive = false;
        // 交换使之num1 > num2
        string tmp = num1;
        num1 = num2;
        num2 = tmp;
        int temp = len1;
        len1 = len2;
        len2 = temp;
    }//if
    string result;
    int i = len1 - 1,j = len2 - 1;
    int a,b,sum,carray = 0;
    // 从低位到高位对位做减法
    while(i >= 0 || j >= 0){
        a = i >= 0 ? num1[i] - '0' : 0;
        b = j >= 0 ? num2[j] - '0' : 0;
        sum = a - b + carray;
        carray = 0;
        // 不够减
        if(sum < 0){
            sum += 10;
            carray = -1;
        }//if
        result.insert(result.begin(),sum + '0');
        --i;
        --j;
    }//while
    // 删除前导0
    string::iterator it = result.begin();
    while(it != result.end() && *it == '0'){
        ++it;
    }//while
    result.erase(result.begin(),it);
    return positive ? result : "-"+result;
}
// big number add function
string AddString(string num1,string num2){
    int len1 = num1.length();
    int len2 = num2.length();
    // 容错处理
    if(len1 <= 0){
        return num2;
    }//if
    if(len2 <= 0){
        return num1;
    }
    string result;
    int i = len1-1,j = len2-1;
    int a,b,sum,carry = 0;
    // 倒序相加
    while(i >= 0 || j >= 0 || carry > 0){
        a = i >= 0 ? num1[i] - '0' : 0;
        b = j >= 0 ? num2[j] - '0' : 0;
        // 按位相加并加上进位
        sum = a + b + carry;
        // 进位
        carry = sum / 10;
        result.insert(result.begin(),sum % 10 + '0');
        --i;
        --j;
    }//while
    return result;
}
// 移位
string ShiftString(string num,int len){
    if(num == "0"){
        return num;
    }//if
    for(int i = 0;i < len;++i){
        num += "0";
    }//for
    return num;
}
// Karatsuba快速相乘算法
string KaratsubaMultiply(string num1, string num2) {
    int len = MakeSameLen(num1,num2);
    if(len == 0){
        return 0;
    }//if
    // all digit are one
    if(len == 1){
        return to_string((num1[0] - '0')*(num2[0] - '0'));
    }//if
    int mid = len / 2;
    // Find the first half and second half of first string.
    string x1 = num1.substr(0,mid);
    string x0 = num1.substr(mid,len - mid);
    // Find the first half and second half of second string
    string y1 = num2.substr(0,mid);
    string y0 = num2.substr(mid,len - mid);
    // Recursively computer
    string z0 = KaratsubaMultiply(x0,y0);
    string z1 = KaratsubaMultiply(AddString(x1,x0),AddString(y1,y0));
    string z2 = KaratsubaMultiply(x1,y1);
    // (z2*10^(2*m))+((z1-z2-z0)*10^(m))+(z0)
    // z2*10^(2*m)
    string r1 = ShiftString(z2,2*(len - mid));
    // (z1-z2-z0)*10^(m)
    string r2 = ShiftString(MinusString(MinusString(z1,z2),z0),len - mid);
    return  AddString(AddString(r1,r2),z0);
}


int main(){
    string num1("12345001");
    string num2("1006789");
    string result = KaratsubaMultiply(num1,num2);
    // 输出
    cout<<result<<endl;
    return 0;
}
```
