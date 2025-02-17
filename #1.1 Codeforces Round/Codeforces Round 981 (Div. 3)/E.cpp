#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

int t;

int get_fa(vector<int> &dsu,int x)
{
	if(dsu[x]==x)
		return x;
	else
		return dsu[x]=get_fa(dsu,dsu[x]);
}

void join(vector<int> &dsu,vector<int> &sz,int x,int y)
{
	if(get_fa(dsu,x)==get_fa(dsu,y))
		return;
	else
	{
		sz[get_fa(dsu,x)]+=sz[get_fa(dsu,y)];
		dsu[get_fa(dsu,y)]=get_fa(dsu,x);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		int n,ans=0;
		cin>>n;
		vector<int> v(n+1),dsu(n+1),sz(n+1);
		
		for(int i=1;i<=n;i++)
			dsu[i]=i,sz[i]=1;
			
		for(int i=1;i<=n;i++)
			cin>>v[i];
			
		for(int i=1;i<=n;i++)
			join(dsu,sz,i,v[i]);
		
		vector<bool> book(n+1,0);
		
		for(int i=1;i<=n;i++)
		{
			if(!book[get_fa(dsu,i)])
			{
				//cout<<"!!!"<<i<<' '<<get_fa(dsu,i)<<' '<<sz[get_fa(dsu,i)]<<endl;
				book[get_fa(dsu,i)]=true;
				if(sz[get_fa(dsu,i)]>2)
					ans+=(sz[get_fa(dsu,i)]-1)/2;
			}
		}
		//cout<<">>";
		cout<<ans<<endl;
	}

	return 0;
}

