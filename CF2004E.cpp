#include<iostream>
#include<vector>
using namespace std;

const int maxn=10000000;
int t,n;
vector<int> a;
int sg[maxn+1]={};
int book[maxn+1]={};

void pre_processing()
{
	sg[1]=1;
	
	int cur=0;
	
	for(int i=2;i<=maxn;++i)
		if(!book[i])
		{
			if(i==3) cur++;
			sg[i]=cur++;
			book[i]=true;
			for(int j=2;j*i<=maxn;++j)
				if(!book[i*j])
				{
					sg[i*j]=sg[i];
					book[i*j]=true;
				}
		}
	/*for(int i=0;i<=50;i++)
		cout<<i<<' '<<sg[i]<<'\n';*/
}

void solve()
{
	int flag=0;
	for(int i=0;i<a.size();++i)
		flag^=sg[a[i]];
	if(!flag)
		cout<<"Bob"<<'\n';
	else
		cout<<"Alice"<<'\n';
	cout<<flush;
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	pre_processing();
	
	cin>>t;
	for(int i=1;i<=t;i++)
		[](){cin>>n;for(int i=1;i<=n;++i) a.emplace_back([](){int x;cin>>x;return x;}());solve();a={};}();
	return 0;
}
