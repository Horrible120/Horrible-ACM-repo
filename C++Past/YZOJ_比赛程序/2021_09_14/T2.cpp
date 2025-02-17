#include<cstdio>
#include<algorithm>
using namespace std;

struct Obj
{
	int v,w;
}obj[100010];

int n,m,k,ans;
long long sumq[100010];
long long sumh[100010];

int heap[200010];
/*************************************************************************/
bool cmp(Obj a,Obj b)
{
	return a.w>b.w;
}

void heapify(int o)
{
	int Max=o;
	if(heap[Max]<heap[o*2])
		Max=o*2;
	if(heap[Max]<heap[o*2+1])
		Max=o*2+1;
	if(Max!=o)
	{
		int xp=heap[o];
		heap[o]=heap[Max];
		heap[Max]=xp;
		heapify(Max);
	}
	return;
}
/***********************************************************************/
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	
	for(int i=1;i<=n;i++)
		scanf("%d%d",&obj[i].v,&obj[i].w);
		
	sort(obj+1,obj+n+1,cmp);
	/*****************************************************************/
	int l=k/2;
	for(int i=1;i<=l;i++)
	{
		heap[i]=obj[i].v;
		sumq[l]+=obj[i].v;
	}
	
	for(int i=l;i>=1;i--)
		heapify(i);
		
	for(int i=l+1;i<=n-l-1;i++)
		if(obj[i].v<heap[1])
		{
			sumq[i]=sumq[i-1]+obj[i].v-heap[1];
			heap[i]=obj[i].v;
		}
		else
			sumq[i]=sumq[i-1];
	/*****************************************************************/
	
	for(int i=n;i>=n-l+1;i--)
	{
		heap[i]=obj[i].v;
		sumh[l]+=obj[i].v;
	}	
	
	for(int i=l;i>=1;i--)
		heapify(i);
	
	for(int i=n-l;i>=l+2;i--)
		if(obj[i].v<heap[1])
		{
			sumh[i]=sumh[i+1]+obj[i].v-heap[1];
			heap[i]=obj[i].v;
		}
		else
			sumh[i]=sumh[i+1];
	/*****************************************************************/
	for(int i=l+1;i<=n-l;i++)
		if(sumq[i-1]+sumh[i+1]<=m)
		{
			ans=obj[i].w;
			break;
		}
	
	if(ans)
		printf("%d",ans);
	else
		printf("-1");
	
	return 0;
}
