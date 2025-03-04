#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

ll Gf(vector<ll> &fa,ll x){
	if(x==fa[x]) return x;
	return fa[x]=Gf(fa,fa[x]);
}

void merge(vector<ll> &fa,ll x,ll y){
	ll fx=Gf(fa,x),fy=Gf(fa,y);
	if(fx==fy) return;
	fa[fx]=fy;
}

void solve(){
	ll n,q;
	cin>>n>>q;
	
	vector<ll> fa(n+1),home(n+1),rnk(n+1);
	for(ll i=1;i<=n;i++)
		fa[i]=home[i]=rnk[i]=i;
	
	for(ll i=1;i<=q;i++){
		ll op;
		cin>>op;
		if(op==1){
			ll a,b;
			cin>>a>>b;
//			merge(fa,a,b);
			fa[a]=rnk[b];
		}
		if(op==2){
			ll a,b;
			cin>>a>>b;
//			swap(home[Gf(fa,a)],home[Gf(fa,b)]);
			
			swap(rnk[a],rnk[b]);
			swap(home[rnk[a]],home[rnk[b]]);
			
		}
		if(op==3){
			ll a;
			cin>>a;
//			OOO
			cout<<home[fa[a]]<<endl;
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
