#include<cstdio>
using namespace std;

int n,q;
long long tree[4000086];
long long lazy[4000086];
int a[1000086];

void build_tree(int o,int l,int r)
{
	if(l==r) 
		tree[o]=a[l];
	else
	{
		int mid=(l+r)/2;
		build_tree(2*o,l,mid);
		build_tree(2*o+1,mid+1,r);
		tree[o]=tree[2*o]+tree[2*o+1];
	}		
}

void change(int o,int l,int r,int s,int t,int k)
{
	int m=(s+t)/2;
	
	if(s>=l&&t<=r)
	{
		lazy[o]+=k;
		tree[o]+=(t-s+1)*k;
	}
		
	else
	{
		if(lazy[o]&&s!=t)
		{
			tree[2*o]+=(m-s+1)*lazy[o];
			tree[2*o+1]+=(t-m)*lazy[o];
			lazy[2*o]+=lazy[o];
			lazy[2*o+1]+=lazy[o];
			lazy[o]=0;
		}
		if(l<=m)
			change(2*o,l,r,s,m,k);
		if(r>m) 
			change(2*o+1,l,r,m+1,t,k);
		tree[o]=tree[2*o]+tree[2*o+1];
	}
}

long long getsum(int o,int l,int r,int s,int t)
{
	if(s>=l&&t<=r)
		return tree[o];
	else
	{
		int m=(s+t)/2;
		long long k=0;
		
		if(lazy[o]&&s!=t)
		{
			tree[2*o]+=(m-s+1)*lazy[o];
			tree[2*o+1]+=(t-m)*lazy[o];
			lazy[2*o]+=lazy[o];
			lazy[2*o+1]+=lazy[o];
			lazy[o]=0;
		}
		
		if(l<=m) k+=getsum(2*o,l,r,s,m);
		if(r>m) k+=getsum(2*o+1,l,r,m+1,t);
		return k;
	}
}

int main()
{
	scanf("%d%d",&n,&q);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		
	build_tree(1,1,n);
	
	for(int i=1;i<=q;i++)
	{
		int op;
		int x,y,z;
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			change(1,x,y,1,n,z);
		}
		else if(op==2)
		{
			scanf("%d%d",&x,&y);
			printf("%lld\n",getsum(1,x,y,1,n));
		}
	}
	
	return 0;
}
