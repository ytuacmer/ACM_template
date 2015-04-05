哈希
===


- [使用set](使用set)
- [哈希数组表示法](哈希数组表示法)
- [哈希指针表示法](哈希指针表示法)

set
---

```c
set <int> a;
// n 为检查的数字
a.cout(n);
// 加入n到n
a.add(n);
```

哈希数组表示法
---
- [代码](哈希数组表示法.cpp)

```cpp
#define MAXN 1010   
#define MOD 1009  
typedef ElemType int;

ElemType point[MAXN];  
int hash[MAXN+1], next[MAXN];  
int n;  

//get hashcode
int hashcode(ElemType &a)  
{  
    //cal hashcode	
    return abs(a.x+ a.y) % MOD;  
}  
  
void insertHash(int i)  
{  
    //头插入，拉链法  
    int key = hashcode(point[i]);  
    next[i] = hash[key];  
    hash[key] = i;  
}  
  
bool search(ElemType &t)  
{  
    int key = hashcode(t);  
    int i = hash[key];  
    while(i != -1)  
    {  
        if(point[i] == t)  
            return true;  
        i = next[i];  
    }  
    return false;  
} 
```


哈希指针表示法
---

- [代码](哈希表指针表示法.cpp)

```cpp

#define ElemType int
const int M = 1007;  

struct Node
{
    ElemType d;
    Node *next;
};
  
Node *pnd[M+1];  
Node nd[M+1]; 
int n_cnt;  //count
int a_cnt;  //count
int a[M+10];  

int hashcode(int i)
{
    return i % M;
}

bool search(int i)
{
    bool found = false;
    int p = hashcode(i);
    Node *pt = pnd[p];
    while(pt)
    {
        if(pt->d == i)
            return true;
        pt = pt->next;
    }
}

void Insert_hash(int i)
{
    int p = hashcode(i);
    nd[n_cnt].d = i;
    nd[n_cnt].next = pnd[p];
    pnd[p] = &nd[n_cnt];
    n_cnt++;
    a[a_cnt++] = i;
}
```
