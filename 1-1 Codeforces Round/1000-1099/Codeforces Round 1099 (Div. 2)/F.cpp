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
	ll n,q;
	cin>>n>>q;
	vector<ll> sq(1),f(n,INF),g(n,INF);
	f[0]=0;
	for(ll i=1;i*i<n;i++){
		sq.emplace_back(i*i);
		f[i*i]=1;
	}
	ll len=sq.size()-1;

	for(ll i=1;i<=len;i++){
		for(ll j=1;j<=len;j++){
			ll sum=sq[i]+sq[j];
			if(sum<n)
				f[sum]=min(f[sum],2LL);
			if(i>j)
				g[sq[i]-sq[j]]=min(g[sq[i]-sq[j]],sq[j]);
		}
	}

	auto dist=[&](ll u,ll v)->ll{
		if(u>v)
			swap(u,v);
		ll d=v-u;
		if(f[d]<=2)
			return f[d];
		if(g[d]<=max(u-1,n-v))
			return 2;
		return INF;
	};

	while(q--){
		ll a,b;
		cin>>a>>b;
		ll ans=dist(a,b);
		if(ans>2){
			ans=4;
			for(ll i=1;i<=len;i++){
				ll x=a-sq[i];
				if(x>=1 && dist(x,b)<=2){
					ans=3;
					break;
				}
				x=a+sq[i];
				if(x<=n && dist(x,b)<=2){
					ans=3;
					break;
				}
			}
		}
		cout<<ans<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
