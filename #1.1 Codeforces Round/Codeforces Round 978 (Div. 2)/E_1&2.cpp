#include<iostream>
#include<vector>
using namespace std;

struct Dsu
{
	int xr,sz;
	int fa;
	Dsu(){}
};

struct Node
{
	int x,xr;
	Node(){}
	Node(int a,int b){x=a,xr=b;}
};

int t,K,flag;
long long m,k,n,q;
long long c[200010];
const int M=1e9+7;

Node get_fa(vector<Dsu> &dsu,int x)
{
	int ans=dsu[x].xr;
	while(dsu[x].fa!=x)
	{
		x=dsu[x].fa;
		ans^=dsu[x].xr;
	}
	return Node(x,ans);
}

void merge(vector<Dsu> &dsu,int x,int y,int num) 
{
	Node a=get_fa(dsu,x),b=get_fa(dsu,y);
	if(a.x==b.x&&a.xr^b.xr^num)
		flag=0;
	else if(a.x!=b.x)
	{
		K--;
		if(dsu[a.x].sz<dsu[b.x].sz)
			swap(a,b);
		dsu[b.x].fa=a.x;
		dsu[b.x].xr=num^a.xr^b.xr;
		dsu[a.x].sz+=dsu[b.x].sz;
	}
	return;	
}

void ans()
{
	if(!flag)
		cout<<0<<endl;
	else
		cout<<c[K-1]<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	c[0]=1,c[1]=1;
	for(int i=1;i<=30;i++)
		c[1]=(2*c[1])%M;
	for(int i=2;i<=200001;i++)
		c[i]=(c[1]*c[i-1])%M;
	
	//for(int i=0;i<=30;i++)
	//	cout<<c[i]<<endl;
	
	while(t--)
	{
		cin>>n>>m>>k>>q;
		
		K=n+m;
		flag=1;
		vector<Dsu> dsu(n+m+1);
		
		for(int i=1;i<=n+m;i++)
			dsu[i].fa=i,dsu[i].sz=1,dsu[i].xr=0;
		
		int x,y,num;
		
		if(k==0)
			ans();
		
		for(int i=1;i<=k+q;i++)
		{
			cin>>x>>y>>num;
			merge(dsu,x,n+y,num);
			if(i>=k) ans();
		}
	}	
	return 0;
}
