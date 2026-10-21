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

const ll B=21, M=1LL<<B;

struct Info{
	ll mx=0,sec=0;

	void add(ll pos){
		if(pos>mx){
			sec=mx;
			mx=pos;
		}else if(pos<mx&&pos>sec)
			sec=pos;
	}
};

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+1);
	vector<Info> dp(M);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		dp[a[i]].add(i);
	}

	for(ll bit=0;bit<B;bit++){
		for(ll mask=0;mask<M;mask++){
			if(mask&(1LL<<bit))
				continue;
			ll nxt=mask|(1LL<<bit);
			dp[mask].add(dp[nxt].mx);
			dp[mask].add(dp[nxt].sec);
		}
	}

	ll ans=0;
	for(ll i=1;i<=n-2;i++){
		ll mask=0;
		for(ll bit=B-1;bit>=0;bit--){
			if(a[i]&(1LL<<bit))
				continue;
			ll nxt=mask|(1LL<<bit);
			if(dp[nxt].sec>i)
				mask=nxt;
		}
		ans=max(ans,a[i]|mask);
	}
	cout<<ans<<'\n';
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
