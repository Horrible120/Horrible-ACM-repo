#include<cstdio>
#include<iostream>
using namespace std;

int n,W,cur;
long long f[40086];

struct Goods
{
	int weight,value;
	Goods(int s=0,int e=0)
	{
		weight=s;
		value=e;
	}
}goods[10086];

int main()
{
	scanf("%d%d",&n,&W);
	
	int v,w,m,c;
	for(int i=1;i<=n;i++)
	{
		c=1;
		scanf("%d%d%d",&v,&w,&m);
		while(m>c)
		{
			m-=c;
			goods[++cur]=Goods(c*w,c*v);
			c=c<<1;
		}
		goods[++cur]=Goods(m*w,m*v);
	}
	
	for(int i=1;i<=cur;i++)
		for(int j=W;j>=goods[i].weight;j--)
			f[j]=max(f[j],f[j-goods[i].weight]+goods[i].value);
			
	printf("%lld",f[W]); 
	
	return 0;
 } 
