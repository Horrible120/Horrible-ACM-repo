#include <bits/stdc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
//using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
//template <typename T, typename Compare = std::less<T>>
//using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	ll n=0;
	cin>>n;
	ll cb[13][13][13]={};
	
	for(ll i=0;i<n;i++)
		for(ll j=0;j<n;j++)
			for(ll k=0;k<n;k++)
				cin>>cb[i][j][k];
	
	vector<vector<ll>> dp(5000,vector<ll>(5000));
	
	for(ll i=0;i<5000;i++)
		for(ll j=0;j<5000;j++)
			dp[i][j]=INF;
	
	dp[0][0]=0;
	
	for(ll i=0;i<n;i++)
		for(ll x=0;x<(1<<n);x++)
			if(__builtin_popcount(x)!=i) continue;
			else
				for(ll y=0;y<(1<<n);y++)
					if(__builtin_popcount(y)!=i) continue;
					else
						for(ll s=0;s<n;s++)
							if(x<<s&1) continue;
							else
								for(ll t=0;t<n;t++)
									if(y<<t&1) continue;
									else
										dp[x|1<<s][y|1<<t]=min(dp[x|1<<s][y|1<<t],dp[x][y]+cb[i][s][t]);
										
	
	cout<<dp[(1<<n)-1][(1<<n)-1]<<endl;
	
	cout.flush();
	
	return 0;
}
