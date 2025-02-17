#include<cstdio>
#include<iostream>
using namespace std;
int n,k,ans;
int l,h;
int d[30010];
int main()
{
	freopen("river.in","r",stdin);
	freopen("river.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	
	for(int i=1;i<=n;i++)
	{
		h=d[i];
		l=d[i];
		for(int j=i+1;j<=n;j++)
		{
			h=max(h,d[j]);
			l=min(l,d[j]);
			if(h-l>k)
			{
				ans=max(ans,j-i);
				break;
			}
		}	
	}
	printf("%d",ans);
	return 0;
}
