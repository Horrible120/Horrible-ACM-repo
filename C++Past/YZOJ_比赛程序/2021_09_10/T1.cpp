#include<cmath>
#include<cstdio>
#include<iostream>
using namespace std;

int n,m;
long long ans;
int main()
{
	
	scanf("%d%d",&n,&m);
	
	float p=sqrt(n);
	float q=sqrt(m);
	
	int a=p;
	int b=q;
	
	ans=a*b+min(n,m)-min(a,b);
	
	printf("%lld",ans);
	
	
	return 0;
}
