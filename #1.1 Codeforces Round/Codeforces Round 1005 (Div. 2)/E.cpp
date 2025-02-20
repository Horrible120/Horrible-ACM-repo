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

const ll INF = 4e18, Mod = 998244353;

ll tt=1;

void solve(){
	ll n,ans=1;
	cin>>n;
	vector<ll> c(n+2),p(n+2),pre(n+2),nxt(n+2),siz(n+2),fa(n+2);
	vector<pair<ll,ll>> od(n+1);
	
	function<ll(ll)> Gf=[&](ll x){
		if(fa[x]==x) return x;
		return fa[x]=Gf(fa[x]);
	};
	
	auto merge=[&](ll x,ll y){
		if(Gf(x)==Gf(y)) return;
		siz[Gf(x)]+=siz[Gf(y)];
		fa[Gf(y)]=Gf(x);
	};
	
	for(ll i=1;i<=n;i++) cin>>p[i];
	for(ll i=1;i<=n;i++){
		od[i].first=p[i];
		od[i].second=i;
		cin>>c[i];
		pre[i]=i-1;
		nxt[i]=i+1;
		siz[i]=1;
		fa[i]=i;
	}
	c[n+1]=INF;
	c[0]=-INF;
	sort(od.begin()+1,od.end());
	for(ll i=2;i<=n;i++)
		if(c[i]==c[i-1])
			merge(i,i-1);
	for(ll i=1;i<=n;i++){
		ll cur=od[i].second;
		ans=ans*siz[Gf(cur)]%Mod;
		siz[Gf(cur)]--;
		if(c[nxt[cur]]==c[pre[cur]]) merge(nxt[cur],pre[cur]);
		nxt[pre[cur]]=nxt[cur];
		pre[nxt[cur]]=pre[cur];
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
