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
	ll n,q,mod;
	cin>>n>>q>>mod;
	vector<ll> val(n+1),dif(n+1),fib(n+2);
	for(ll i=1;i<=n;i++)
		cin>>val[i];
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		val[i]=(val[i]-x+mod)%mod;
	}

	fib[1]=1%mod;
	for(ll i=2;i<=n+1;i++)
		fib[i]=(fib[i-1]+fib[i-2])%mod;

	dif[1]=val[1];
	for(ll i=2;i<=n;i++)
		dif[i]=(val[i]-val[i-1]-val[i-2]+2*mod)%mod;
	ll cnt=0;
	for(ll i=1;i<=n;i++)
		cnt+=(dif[i]!=0);

	auto upd=[&](ll pos,ll add){
		if(pos>n)
			return;
		cnt-=(dif[pos]!=0);
		dif[pos]=(dif[pos]+add+mod)%mod;
		cnt+=(dif[pos]!=0);
	};

	while(q--){
		char ch;
		ll l,r;
		cin>>ch>>l>>r;
		ll len=r-l+1,sgn=(ch=='A'?1:-1);

		upd(l,sgn);
		upd(r+1,-sgn*fib[len+1]);
		upd(r+2,-sgn*fib[len]);
		cout<<(cnt==0?"YES":"NO")<<'\n';
	}
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
