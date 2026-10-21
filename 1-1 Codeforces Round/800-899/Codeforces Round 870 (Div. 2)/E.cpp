#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll m,n;
	cin>>m>>n;
	vector<vector<ll>> v(m+1,vector<ll>(n+1,0));
	vector<ll> p(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>p[i];
	}
	
	for(ll i=1;i<=m;i++){
		for(ll j=1;j<=n;j++){
			cin>>v[i][j];
		}
	}
	
	vector<ll> rnk(n+1,0);
	vector<bitset<5001>> bt(n+1);
	
	for(ll i=1;i<=n;i++){
		rnk[i]=i;
		bt[i].flip();
	}
	
	
	
	for(ll i=1;i<=m;i++){
		sort(rnk.begin()+1,rnk.end(),[&](const ll a,const ll b){return v[i][a]<v[i][b];});
		bitset<5001> tmp;
		ll r=1;
		for(ll j=1;j<=n;j++){
			if(j>1&&v[i][rnk[j]]>v[i][rnk[j-1]]){
				while(r<j) tmp.set(rnk[r++]);
			}
			bt[rnk[j]]&=tmp;
		}
	}
	
	ll ans=0;
	
//	for(ll i=1;i<=n;i++){
//		for(ll j=1;j<=n;j++){
//			cout<<bt[i][j]<<' ';
//		}
//		cout<<endl;
//	}
	
	vector<ll> dp(n+1,0);
	
	for(ll i=1;i<=n;i++){
		dp[rnk[i]]=p[rnk[i]];
		for(ll j=1;j<i;j++){
			if(bt[rnk[i]][rnk[j]]){
				dp[rnk[i]]=max(dp[rnk[i]],dp[rnk[j]]+p[rnk[i]]);
			}
		}
		ans=max(ans,dp[rnk[i]]);
	}
	
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
