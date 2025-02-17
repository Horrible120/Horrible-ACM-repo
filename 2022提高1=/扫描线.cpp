#include<set> 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std; 

struct Node
{
	int h,x;
	int op;
}node[400010];

multiset <int> m;

int n,tot;

bool cmp(Node a,Node b)
{
	if(a.x!=b.x)
		return a.x<b.x;
	else if(a.op!=b.op)
		return a.op<b.op;
	return a.h>=b.h;
}

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
	{
		int k,l,r;
		scanf("%d%d%d",&k,&l,&r);
		node[++tot]={k,l,1};
		node[++tot]={k,r,-1};
	}
		
		
	sort(node+1,node+tot+1,cmp);
	
//	m.
	
	
	return 0;
}

