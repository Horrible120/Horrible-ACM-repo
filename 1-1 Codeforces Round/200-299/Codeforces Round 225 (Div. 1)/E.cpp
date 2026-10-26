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

const ll B=24, M=1LL<<B;

void solve(){
	ll n;
	cin>>n;
	vector<ll> f(M);
	for(ll i=1;i<=n;i++){
		string s;
		cin>>s;
		ll mask=0;
		for(ll j=0;j<3;j++)
			mask|=1LL<<(s[j]-'a');
		f[mask]++;
	}

	for(ll len=1;len<M;len<<=1)
		for(ll base=0;base<M;base+=len<<1)
			for(ll j=0;j<len;j++)
				f[base+len+j]+=f[base+j];

	ll ans=0;
	for(ll mask=0;mask<M;mask++){
		ll val=n-f[mask];
		ans^=val*val;
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
