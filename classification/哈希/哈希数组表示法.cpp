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