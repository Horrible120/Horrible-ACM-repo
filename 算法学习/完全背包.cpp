#include<cstdio>
#include<iostream>
using namespace std;

int t,m;
long long f[10000086];

struct Goods
{
	int w,d;
}goods[10086];

int main()
{
	scanf("%d%d",&t,&m);
	
	for(int i=1;i<=m;i++)
		scanf("%d%d",&goods[i].w,&goods[i].d);
	
	for(int i=1;i<=m;i++)
		for(int j=goods[i].w;j<=t;j++)
			f[j]=max(f[j],f[j-goods[i].w]+goods[i].d);
			
	printf("%lld",f[t]);
	
	
	return 0;
 } 
