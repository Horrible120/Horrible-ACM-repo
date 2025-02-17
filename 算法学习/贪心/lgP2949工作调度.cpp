#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std; 

int n;
int cur;
long long ans;

struct Task
{
	int time;
	int w;
}task[100086];

Task heap[100086];

bool cmp(Task a,Task b)
{
	return a.time<b.time;
}

void up(int x)
{
	while(x>0&&heap[x].w<heap[x>>1].w)
	{
		swap(heap[x],heap[x>>1]);
		x>>=1;
	}
}

void down(int x)
{
	int t;
	while(x<<1<=cur)
	{
		t=x<<1;
		
		if(heap[t+1].w<heap[t].w&&t+1<=cur) t++;
		if(heap[t].w>=heap[x].w) break;
		
		swap(heap[x],heap[t]);
		x=t;
	}
}

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d%d",&task[i].time,&task[i].w);
		
	stable_sort(task+1,task+n+1,cmp);
		
	/*for(int i=1;i<=n;i++)
		printf("%d ",task[i].time);*/
	
		
	for(int i=1;i<=n;i++)
	{
		if(task[i].time>cur)
		{
			heap[++cur]=task[i];
			up(cur);
		}
		else if(task[i].w>heap[1].w)
		{
			heap[1]=task[i];
			down(1);
		}
	}
	
	for(int i=1;i<=cur;i++)
		ans+=heap[i].w;
		
	printf("%lld",ans);	
	
	return 0;
}
