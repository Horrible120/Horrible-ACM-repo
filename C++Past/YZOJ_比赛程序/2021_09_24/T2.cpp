#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[3000010];
int color[3000010];

int main()
{
	freopen("perfect.in","r",stdin);
	freopen("perfect.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		
	color[1]=1;
	for(int i=2;i<=n;i++)
		if(abs(a[i]-a[i-1])<=1)
			color[i]=color[i-1];
		else
			color[i]=color[i-1]+1;
		
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		if(color[l]==color[r])
			printf("YES\n");
		else
			printf("NO\n");
	}
	
	return 0;
 } 
