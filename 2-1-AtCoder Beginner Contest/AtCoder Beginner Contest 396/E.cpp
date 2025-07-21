#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

ll fa[200001],xo[200001],ans[200001];

ll GF(ll x){
	if(fa[x]==x) return x;
	GF(fa[x]);
	xo[x]^=xo[fa[x]];
	return fa[x]=fa[fa[x]];
}

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> X(m+1),Y(m+1),Z(m+1);
	for(ll i=1;i<=m;i++)
		cin>>X[i]>>Y[i]>>Z[i];
	for(ll i=1;i<=n;i++)
		fa[i]=i;
	for(ll i=1;i<=m;i++){
		ll x=X[i],y=Y[i],z=Z[i];
		if(GF(x)!=GF(y)){
			fa[GF(x)]=GF(y);
			for(ll i=0;i<=30;i++){
				if((z>>i)&()) ans[x]+=(1<<i);
			}
		}
	}
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
