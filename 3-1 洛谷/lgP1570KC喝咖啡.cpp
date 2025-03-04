#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int n,m;
double ans;

struct Gd//调味料结构体 
{
	int c,v;
	Gd(){};		
}gd[2100];

bool cmp(Gd a,Gd b)
{
	return (a.v-a.c*ans>b.v-b.c*ans);
}

double check(double x)
{
	double sumi=0;
	sort(gd+1,gd+n+1,cmp);
	for(int i=1;i<=m;i++)
		sumi+=gd[i].v-gd[i].c*ans;
	//printf("%lf %lf\n",ans,sumi);
	return sumi;
}

int main()
{
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&gd[i].v);
		
	for(int i=1;i<=n;i++)
		scanf("%d",&gd[i].c);
	
	double left=0,right=1000;
	double mid;
	double flag;
	
	while(left<right-0.0001)
	{
		ans=(left+right)/2;
		flag=check(ans);
		if(flag>0)
			left=ans+0.0001;
		else if(flag<0)
			right=ans-0.0001;
		else if(flag==0)
			break;
	}
	
	printf("%.3lf",(left+right)/2);
		
	return 0;
 } 
