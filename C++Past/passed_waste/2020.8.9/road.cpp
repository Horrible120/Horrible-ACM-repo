#include<cstdio>
using namespace std;
int n,d[1000000],ans;
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		scanf("%d",&d[i]);
	ans=d[1]; 
	for(int i=2;i<=n;i++)
		if(d[i]>d[i-1]) 
			ans+=d[i]-d[i-1];
	printf("%d",ans);
} 
