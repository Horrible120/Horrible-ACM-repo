#include<iostream>
#include<vector> 
#include<map>
#include<set>
#include<algorithm>
using namespace std;

int t;
int n,k,q;

int dp[200010];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	
	for(int i=1;i<=t;++i)
	{
		vector<int> a(n+1);
		[&](){cin>>n>>k>>q;for(int i=1;i<=n;i++) [&](){int x;cin>>x;a[i]=x-i;}();}();
		
		std::map <int,int> mp;
		std::multiset<int> heap;
		
		for(int j=1;j<=n;j++)
		{
			if(!mp[a[j]])
			{
				mp[a[j]]=1;
				heap.insert(1);
			}
			else
			{
				heap.erase(mp[a[j]]);
				mp[a[j]]++;
				heap.insert(mp[a[j]]);
			}
			dp[1]=k-*heap.rbegin();
		}
		
		vector<array<int,3>> que(q);
		vector<int> an(q);
		
		for(int j=1;j<=q;j++)
		{
			
		}
	}
	
	return 0; 
}
