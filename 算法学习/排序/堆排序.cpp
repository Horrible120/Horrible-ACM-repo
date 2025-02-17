#include<cstdio>
#include<iostream>
using namespace std;

int num[100086],n,m;

void down(int x)
{
	int t;
	while((x<<1)<=n)
	{
		t=x<<1;
		if(t+1<=n&&num[t+1]>num[t]) t++;
		if(num[x]>=num[t]) return;
		swap(num[x],num[t]);
		x=t;
	}
}

void build_heap()
{
	for(int i=n>>1;i>=1;i--)
		down(i);
	return;
}

int main()
{
	scanf("%d",&n);
	
	m=n;
	
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
		
	build_heap();
	
	for(int i=1;i<m;i++)
	{
		swap(num[1],num[n]);
		n--;
		down(1);
	}
	
	for(int i=1;i<=m;i++)
		printf("%d ",num[i]); 
	
	return 0;
 } 
