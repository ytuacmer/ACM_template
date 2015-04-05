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

