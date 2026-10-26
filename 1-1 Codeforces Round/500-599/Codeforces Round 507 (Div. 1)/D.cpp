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
	ll n;
	cin >> n;
	vector<vector<ll>> eg(n+1),son(n+1);
	vector<ll> fa(n+1),ord,f(n+1),ans(n+1);
	ord.reserve(n);
	for (ll i=1;i<n;i++){
		ll u,v;
		cin >> u >> v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}

	ord.emplace_back(1);
	for (ll i=0;i<n;i++){
		ll u=ord[i];
		for (ll j=0;j<(ll)eg[u].size();j++){
			ll v=eg[u][j];
			if (v==fa[u])
				continue;
			fa[v]=u;
			son[u].emplace_back(v);
			ord.emplace_back(v);
		}
	}

	auto calc=[&](ll k)->ll{
		ll cnt=0;
		for (ll i=n-1;i>=0;i--){
			ll u=ord[i],mx=0,se=0;
			for (ll j=0;j<(ll)son[u].size();j++){
				ll v=son[u][j];
				if (f[v]>mx){
					se=mx;
					mx=f[v];
				}
				else if (f[v]>se)
					se=f[v];
			}
			if (mx+se+1>=k){
				cnt++;
				f[u]=0;
			}
			else
				f[u]=mx+1;
		}
		return cnt;
	};

	auto divide=[&](auto &&self,ll l,ll r)->void{
		if (r-l<=1)
			return;
		if (ans[l]==ans[r]){
			for (ll i=l+1;i<r;i++)
				ans[i]=ans[l];
			return;
		}
		ll mid=(l+r)/2;
		ans[mid]=calc(mid);
		self(self,l,mid);
		self(self,mid,r);
	};

	ans[1]=n;
	ans[n]=calc(n);
	divide(divide,1,n);
	for (ll i=1;i<=n;i++)
		cout << ans[i] << '\n';
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
