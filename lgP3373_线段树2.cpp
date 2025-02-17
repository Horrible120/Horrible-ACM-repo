#include<iostream>
#include<vector>
using namespace std;

long long n,q,m; 
long long v[100010];

struct Lazy
{
	long long op,k;
	Lazy(int a,int b){op=a,k=b;}
};

struct Node
{
	long long lazyt,lazya;
	long long num;
	Node(){}
}node[400010];

void build_tree(int x,int l,int r)
{
	node[x].lazyt=1;
	node[x].lazya=0;
	if(l==r)
	{
		node[x].num=v[l]%m;
		return;
	}
	int mid=l+((r-l)>>1);
	build_tree(x<<1,l,mid);
	build_tree((x<<1)+1,mid+1,r);
	
	node[x].num=(node[x<<1].num+node[(x<<1)+1].num)%m;
	
	return;
}

void push_down(int x,int l,int r)
{
	long long mid=l+((r-l)>>1);
	//cout<<"push"<<l<<' '<<r<<' '<<node[x].lazyt<<' '<<node[x].lazya<<endl;
	
	node[x<<1].num=(node[x<<1].num*node[x].lazyt+node[x].lazya*(mid-l+1))%m;
	node[(x<<1)+1].num=(node[(x<<1)+1].num*node[x].lazyt+node[x].lazya*(r-mid))%m;		
	
	node[x<<1].lazyt=node[x<<1].lazyt*node[x].lazyt%m;
	node[(x<<1)+1].lazyt=node[(x<<1)+1].lazyt*node[x].lazyt%m;
	
	node[x<<1].lazya=(node[x<<1].lazya*node[x].lazyt+node[x].lazya)%m;
	node[(x<<1)+1].lazya=(node[(x<<1)+1].lazya*node[x].lazyt+node[x].lazya)%m;
	
	node[x].lazya=0;
	node[x].lazyt=1;
	
	return;
}

void range_op(int x,int l,int r,int s,int t,int op,int k)
{
	//cout<<"op"<<l<<' '<<r<<endl;
	if(l>=s&&r<=t)
	{
		if(op==2)
			node[x].num=(node[x].num+k*(r-l+1))%m;
		else if(op==1)
			node[x].num=(node[x].num*k)%m;
		
		if(l!=r)
		{
			if(op==2)
				node[x].lazya=(node[x].lazya+k)%m;
			else if(op==1)
			{
				node[x].lazya=(node[x].lazya*k)%m;
				node[x].lazyt=(node[x].lazyt*k)%m;
			}
		}
		return;
	}
		
	if(!(node[x].lazya==0&&node[x].lazyt==1))
		push_down(x,l,r);
	
	long long mid=l+((r-l)>>1);
	
	if(mid>=s)
		range_op(x<<1,l,mid,s,t,op,k);
	if(mid+1<=t)
		range_op((x<<1)+1,mid+1,r,s,t,op,k);
	
	node[x].num=(node[x<<1].num+node[(x<<1)+1].num)%m;
	
	return;
}

long long get_sum(int x,int l,int r,int s,int t)
{
	
	if(l>=s&&r<=t)
	{
		//cout<<"sum"<<l<<' '<<r<<' '<<node[x].num<<endl;
		return node[x].num;
	}
		
	
	if(!(node[x].lazya==0&&node[x].lazyt==1))
		push_down(x,l,r);
	
	long long mid=l+((r-l)>>1),sum=0;
	
	if(mid>=s)
		sum+=get_sum(x<<1,l,mid,s,t);
	if(mid+1<=t)
		sum+=get_sum((x<<1)+1,mid+1,r,s,t);
	
	return (sum%m);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>q>>m;
	
	
	
	for(int i=1;i<=n;i++)
		cin>>v[i];
	
	build_tree(1,1,n);
	
	int op,x,y,k;
	for(int i=1;i<=q;i++)
	{
		cin>>op;
		switch(op)
		{
			case 1:
			case 2:
				cin>>x>>y>>k;
				if(x>y)
					swap(x,y);
				range_op(1,1,n,x,y,op,k);
				break;
			case 3:
				cin>>x>>y;
				if(x>y)
					swap(x,y);
				cout<<get_sum(1,1,n,x,y)<<endl;
				break;
		}
	}
	
	return 0;
}
