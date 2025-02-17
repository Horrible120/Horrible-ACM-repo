#include<queue>
#include<cstdio>
#include<iostream>
using namespace std;

long long a[100010];
long long sum[100010],summn[100010];
int n,q,ans;
long long x,cur;

std::priority_queue <int> qu; 

int main()
{
	scanf("%d%d",&n,&q);
	
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	
	sum[1]=a[1];
	summn[1]=a[1];
	
	for(int i=2;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
		summn[i]=min(summn[i-1],sum[i]);
	}
	
	for(int i=1;i<=q;i++)
	{
		scanf("%lld",&x);
		if(x+summn[n]>=0)
			printf("0\n");
		else
		{
			while(!qu.empty())
				qu.pop();
			for(int j=1;j<=n;j++)
				if(a[i]<0)
				{
					qu.push(-a[i]);
					while(x+sum[i]<0)
					{
						ans++;
						x+=qu.top();
						qu.pop();
					}
				}
		printf("%d\n",ans);
		}
	}
	
	return 0;
}
