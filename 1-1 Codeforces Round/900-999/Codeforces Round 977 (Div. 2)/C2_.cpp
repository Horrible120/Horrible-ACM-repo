#include<iostream>
#include<map>
#include<set> 
using namespace std;

int t,n,m,q;

struct Node
{
	int mx,mn,flag;
};

Node node[800010];
int v[200010],b[200010],mp[200010];
set<int> st[200010];

void build_tree(int x,int l,int r)
{
	if(l==r)
	{
		if(st[l].empty())
			node[x].mn=l+m;
		else
			node[x].mn=*st[l].begin();
		node[x].mx=node[x].mn;
		
		node[x].flag=1;
		
		//cout<<x<<' '<<l<<' '<<r<<' '<<node[x].mn<<'|'<<node[x].mx<<' '<<node[x].flag<<endl;
		
		return;
	}
	
	int mid=l+((r-l)>>1);
	
	build_tree(x<<1,l,mid);
	build_tree((x<<1)+1,mid+1,r);
	
	node[x].mn=min(node[x<<1].mn,node[(x<<1)+1].mn);
	node[x].mx=max(node[x<<1].mx,node[(x<<1)+1].mx);
	
	if(node[x<<1].flag&&node[(x<<1)+1].flag&&node[x<<1].mx<node[(x<<1)+1].mn)
		node[x].flag=1;
	else
		node[x].flag=0;
	
	//cout<<x<<' '<<l<<' '<<r<<' '<<node[x].mn<<'|'<<node[x].mx<<' '<<node[x].flag<<endl;
	
	return;
}

void init()
{
	for(int i=1;i<=4*n;i++)
	{
		node[i].flag=0;
		node[i].mn=999999999;
		node[i].mx=0;
	}
	
	for(int i=1;i<=n;i++)
	{
		v[i]=0;
		mp[i]=0;
	}
		
	
	for(int i=1;i<=m;i++)
		b[i]=0;
	
	for(int i=1;i<=n;i++)
		st[i].clear();
	
	return;
}

void change(int x,int l,int r,int coo)
{
	if(l==r&&l==coo)
	{
		if(st[l].empty())
			node[x].mn=l+m;
		else
			node[x].mn=*st[l].begin();
		node[x].mx=node[x].mn;
		
		node[x].flag=1;
		
		return;
	}
	
	int mid=l+((r-l)>>1);
	
	if(coo<=mid) 
		change(x<<1,l,mid,coo);
	else
		change((x<<1)+1,mid+1,r,coo);
	
	node[x].mn=min(node[x<<1].mn,node[(x<<1)+1].mn);
	node[x].mx=max(node[x<<1].mx,node[(x<<1)+1].mx);
	
	if(node[x<<1].flag&&node[(x<<1)+1].flag&&node[x<<1].mx<node[(x<<1)+1].mn)
		node[x].flag=1;
	else
		node[x].flag=0;
	
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	while(t--)
	{
		cin>>n>>m>>q;
		
		init();
		 
		for(int i=1;i<=n;i++)
			cin>>v[i];	
		for(int i=1;i<=n;i++)
			mp[v[i]]=i;	
			
		for(int i=1;i<=m;i++)
		{
			cin>>b[i];	
			b[i]=mp[b[i]];
		}
		
		for(int i=1;i<=m;i++)
			st[b[i]].insert(i);
			
		build_tree(1,1,n);
		
		if(node[1].flag)
			cout<<"YA"<<endl;
		else
			cout<<"TIDAK"<<endl;
		
		int x,y;
		for(int i=1;i<=q;i++)
		{
			cin>>x>>y;
			
			st[b[x]].erase(x);
			st[mp[y]].insert(x);
			
			
			change(1,1,n,b[x]);
			change(1,1,n,mp[y]);
			
			b[x]=mp[y];
			
			if(node[1].flag)
				cout<<"YA"<<endl;
			else
				cout<<"TIDAK"<<endl;
		}
	}
	
	return 0;
}
