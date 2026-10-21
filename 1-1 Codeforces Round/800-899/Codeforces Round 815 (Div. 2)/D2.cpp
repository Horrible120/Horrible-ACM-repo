#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef int ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),dp(n+1,0);
	vector<ll> ls(n*60+1,0),rs(n*60+1,0);
	vector<array<ll,2>> tr(n*60+1);
	ll tot=1;
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	auto add=[&](ll x){
		ll u=1;
		for(ll i=30;i>=0;i--){
			if(!rs[u]) rs[u]=++tot;
			if(!ls[u]) ls[u]=++tot;
			if(((v[x]^(x-1))>>i)&1){
				u=rs[u];
			}else{
				u=ls[u];
			}
			tr[u][(x-1>>i)&1]=max(tr[u][(x-1>>i)&1],dp[x]);
		}
	};
	
	auto query=[&](ll x)->ll{
		ll res=0;
		
		ll u=1;
		
		for(ll i=30;i>=0&&u;i--){
			if(((v[x]^(x-1))>>i)&1){
				res=max(res,tr[ls[u]][((v[x]>>i)&1)^1]);
				u=rs[u];
			}else{
				res=max(res,tr[rs[u]][((v[x]>>i)&1)^1]);
				u=ls[u];
			}
		}
		
		return res;
	};
	
	dp[1]=1;
	add(1);
	
	ll ans=dp[1];
	
	for(ll i=2;i<=n;i++){
		dp[i]=query(i)+1;
		add(i);
		ans=max(ans,dp[i]);
	}
	
//	OOO
	cout<<ans<<endl;
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
