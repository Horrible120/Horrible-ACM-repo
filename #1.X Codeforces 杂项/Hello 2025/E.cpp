#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
typedef vector<ll> vll;
typedef vector<vector<ll>> v2ll;
typedef vector<vector<vector<ll>>> v3ll;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

ll get_fa(vll &fa,ll x){
	if(x==fa[x]) return x;
	else return fa[x]=get_fa(fa,fa[x]);
}

void solve(){
	ll n,m,q;
	cin>>n>>m>>q;
	
	vll fa(n+1);
	vector<tuple<ll,ll,ll>> eg;
	
	v2ll dis(n+1,vll(n+1,INF));
	
	v3ll ans(n+1,v2ll(n+1,vll(n+1,INF)));
	
	for(ll i=1;i<=n;i++) fa[i]=i,dis[i][i]=0;
	
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		dis[u][v]=dis[v][u]=1;
		eg.emplace_back(make_tuple(u,v,w));
	}
	
	sort(eg.begin(),eg.end(),[](tuple<ll,ll,ll> a,tuple<ll,ll,ll> b){
		auto [x1,y1,z1]=a;
		auto [x2,y2,z2]=b;
		return z1<z2;
	});
	
//	for(auto [x,y,z]:eg){
//		OOO
//		cout<<x<<' '<<y<<' '<<z<<endl;
//	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			for(ll k=1;k<=n;k++){
				dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
			}
		}
	}
	
	for(ll k=0;k<m;k++){
		
		auto [u,v,w]=eg[k];
		if(get_fa(fa,u)==get_fa(fa,v)) continue;
		
		for(ll i=1;i<=n;i++){
			for(ll j=i+1;j<=n;j++){
				dis[i][j]=dis[j][i]=min(dis[i][j],min(dis[i][u]+dis[v][j],dis[i][v]+dis[u][j]));
				ans[i][j][dis[i][j]+1]=ans[j][i][dis[i][j]+1]=min(ans[i][j][dis[i][j]+1],w);
			}
		}
		fa[get_fa(fa,v)]=get_fa(fa,u);
	}
	
//	OOO
	
	while(q--){
		ll u,v,k;
		cin>>u>>v>>k;
		cout<<ans[u][v][min(k,n-1)]<<' ';
	}
	
	cout<<'\n';
	
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
