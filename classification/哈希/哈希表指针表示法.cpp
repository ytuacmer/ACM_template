
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

