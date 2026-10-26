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
	ll n,m,k;
	cin>>n>>m>>k;
	vector<vector<ll>> eg(n+1);
	for(ll i=0;i<m;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}

	vector<ll> fa(n+1),dep(n+1),leaf;
	ll far=1;
	auto dfs=[&](auto &&self,ll u)->void{
		bool isleaf=true;
		for(ll i=0;i<(ll)eg[u].size();i++){
			ll v=eg[u][i];
			if(dep[v])
				continue;
			isleaf=false;
			fa[v]=u;
			dep[v]=dep[u]+1;
			if(dep[v]>dep[far])
				far=v;
			self(self,v);
		}
		if(isleaf)
			leaf.emplace_back(u);
	};
	dep[1]=1;
	dfs(dfs,1);

	if(dep[far]>=(n+k-1)/k){
		cout<<"PATH\n"<<dep[far]<<'\n';
		for(ll u=far;u;u=fa[u])
			cout<<u<<' ';
		cout<<'\n';
		return;
	}

	cout<<"CYCLES\n";
	vector<ll> cyc;
	auto climb=[&](ll u,ll v)->void{
		while(u!=v){
			cyc.emplace_back(u);
			u=fa[u];
		}
		cyc.emplace_back(v);
	};
	for(ll i=0;i<k;i++){
		ll u=leaf[i],a=0,b=0;
		for(ll j=0;j<(ll)eg[u].size();j++){
			ll v=eg[u][j];
			if(v==fa[u])
				continue;
			if(!a)
				a=v;
			else{
				b=v;
				break;
			}
		}
		if(dep[a]>dep[b])
			swap(a,b);
		cyc.clear();
		if((dep[u]-dep[a]+1)%3)
			climb(u,a);
		else if((dep[u]-dep[b]+1)%3)
			climb(u,b);
		else{
			cyc.emplace_back(u);
			climb(b,a);
		}
		cout<<cyc.size()<<'\n';
		for(ll j=0;j<(ll)cyc.size();j++)
			cout<<cyc[j]<<' ';
		cout<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
