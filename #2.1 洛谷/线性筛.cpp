#include<cstdio>
#include<iostream>
using namespace std;

const int maxn=10000010;
int n,tot;
int zhishu[1000000];
bool book[100000010];

void shai()
{
	for(int i=2;i<=maxn;i++)
		if(!book[i])
			for(int j=2;j*i<=maxn;j++)
				book[j*i]=true;	
	return;			
}

int  main()
{
	scanf("%d",&n);
	
	shai();
	
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		printf("%d\n",book[x]);
	}
	
	return 0;
 } 
