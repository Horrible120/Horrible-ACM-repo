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
	ll n,m,cost,sum=0;
	cin>>n>>m>>cost;
	vector<ll> val(n+1);
	for(ll i=1;i<=n;i++){
		cin>>val[i];
		sum+=val[i];
	}

	vector<vector<pair<ll,ll>>> eg(n+1);
	for(ll id=1;id<=m;id++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v,id);
		eg[v].emplace_back(u,id);
	}
	if(sum<(n-1)*cost){
		cout<<"NO\n";
		return;
	}

	vector<ll> fa(n+1),eid(n+1),ord;
	fa[1]=1;
	ord.emplace_back(1);
	for(ll i=0;i<(ll)ord.size();i++){
		ll u=ord[i];
		for(ll j=0;j<(ll)eg[u].size();j++){
			ll v=eg[u][j].first,id=eg[u][j].second;
			if(fa[v])
				continue;
			fa[v]=u;
			eid[v]=id;
			ord.emplace_back(v);
		}
	}

	vector<ll> pre,suf;
	for(ll i=n-1;i>0;i--){
		ll u=ord[i],v=fa[u];
		if(val[u]+val[v]>=cost){
			pre.emplace_back(eid[u]);
			val[v]+=val[u]-cost;
		}else
			suf.emplace_back(eid[u]);
	}

	cout<<"YES\n";
	for(ll i=0;i<(ll)pre.size();i++)
		cout<<pre[i]<<'\n';
	for(ll i=(ll)suf.size()-1;i>=0;i--)
		cout<<suf[i]<<'\n';
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
