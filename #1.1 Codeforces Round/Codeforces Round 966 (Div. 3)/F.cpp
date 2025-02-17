#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

struct cmp1{
	operator ()(pair<ll,ll> a,pair<ll,ll> b){
		if(min(a.first,a.second)!=min(b.first,b.second))
			return min(a.first,a.second)<min(b.first,b.second);
		else
			return a.first*a.second<b.first*b.second;
	};
};

void solve(){
	ll n,k,cnt=0,flag=1;
	cin>>n>>k;
	vector<pair<ll,ll>> rec(n+1);
	vector<vector<ll>> w(n+1,vector<ll>(201,INF));
	vector<ll> dp(k+1,INF);
	dp[0]=0;
	
	for(ll i=1;i<=n;i++){
		auto &[x,y]=rec[i];
		cin>>x>>y;
		if(x>y) swap(x,y);
		
		w[i][0]=0;
		for(ll j=1;j<=x+y;j++)
			w[i][j]=x*y-min((x+y-j)/2,x)*((x+y-j)-min((x+y-j)/2,x));
		w[i][x+y-1]=w[i][x+y];
		
		for(ll j=k;j>=1;j--)
			for(ll m=1;m<=x+y;m++)
				if(j-m>=0)
					dp[j]=min(dp[j],dp[j-m]+w[i][m]);
//		for(ll j=0;j<=k;j++)
//			cout<<dp[i]<<' ';
//		cout<<endl;
	}
//	OOO
	if(dp[k]>=INF) cout<<-1<<endl;
	else cout<<dp[k]<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
