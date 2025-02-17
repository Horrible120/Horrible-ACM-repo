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

struct Pair
{
	long long k=0,num=0;
};

bool cmp(Pair a,Pair b)
{
	return a.num<b.num;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		int n;
		long long ans=0;
		cin>>n;
		vector<Pair> v(n);
		
		map<long long,long long> dp;
		
		for(int i=0;i<n;i++)
		{
			cin>>v[i].num;
			v[i].num-=n-i;
			v[i].k=i;
		}
		
		dp[0]=0;
		
		sort(v.begin(),v.end(),cmp);
		
		
		//for(int i=0;i<n;i++)
		//	cout<<v[i].k<<' '<<v[i].num<<' '<<dp[v[i].num]<<endl;
		
		for(int i=0;i<n;i++)
		{
			if(dp[v[i].num]||(v[i].num==0))
			{
				//cout<<"KKK"<<v[i].k<<endl;
				dp[v[i].num+v[i].k]=max(dp[v[i].num+v[i].k],dp[v[i].num]+v[i].k);
				ans=max(ans,dp[v[i].num+v[i].k]);
			}
		}
		//cout<<">>";
		cout<<ans+n<<endl;
	}

	return 0;
}

