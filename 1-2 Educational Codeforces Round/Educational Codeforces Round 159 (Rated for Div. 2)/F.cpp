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

class H_basis{
public:
	ll dg,zero_flag;
	vector<ll> d,p,ti;
	
	H_basis(ll _dg){
		dg=_dg;
		zero_flag=0;
		d.assign(dg+1,0);
		ti.assign(dg+1,0);
	}
	
	void print(){
		for(ll i=0;i<=dg;i++)
			cout<<i<<' '<<d[i]<<' '<<ti[i]<<endl;
	}
	
	bool insert(ll val,ll tg){
		for(ll i=dg;i>=0;i--){
			if((val>>i)&1){
				if(!d[i]){
					ti[i]=tg;
					d[i]=val;
					return true;
				}
				else{
					if(ti[i]>tg){
						val^=d[i];
					}else{
						swap(val,d[i]);
						swap(tg,ti[i]);
						val^=d[i];
					}
				}
			}
		}
		zero_flag=true;
		return false;
	}
	
	bool check(ll val){
		for(ll i=dg;i>=0;i--){
			if((val>>i)&1){
				if(!d[i]){
					return false;
				}
				val^=d[i];
			}
		}
		return true;
	}
};

void solve(){
	ll n;
	cin>>n;
	
	vector<ll> val(n+1,0),dep(n+1,0);
	vector<vector<ll>> fa(n+1,vector<ll>(21,0));
	
	vector<H_basis> preb(n+1,H_basis(20ll));
	
	for(ll i=1;i<=n;i++){
		cin>>val[i];
	}
	
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	auto DFS=[&](this auto &&self,ll u)->void{
		preb[u].insert(val[u],dep[u]);
		for(auto v:eg[u]) if(v!=fa[u][0]){
			dep[v]=dep[u]+1;
			fa[v][0]=u;
			preb[v]=preb[u];
			self(v);
		}
	};
	
	dep[1]=1;
	fa[1][0]=1;
	DFS(1);
	
	for(ll i=1;i<=20;i++){
		for(ll j=1;j<=n;j++){
			fa[j][i]=fa[fa[j][i-1]][i-1];
		}
	}
	
	auto glca=[&](ll u,ll v,ll k){
		if(dep[u]<dep[v]) swap(u,v);
		
		ll ou=u,ov=v;
		
		for(ll i=20;i>=0;i--){
			if((dep[u]-dep[v])>>i&1){
				u=fa[u][i];
			}
		}
		
		if(u!=v){
			for(ll i=20;i>=0;i--){
				if(fa[u][i]!=fa[v][i]){
					u=fa[u][i];
					v=fa[v][i];
				}
			}
			u=fa[u][0];
			v=fa[v][0];
		}
		
		ll tp=dep[u];
		H_basis tmp(20);
		
		auto &ub=preb[ou];
		auto &vb=preb[ov];
		
		for(ll i=0;i<=20;i++){
			if(ub.ti[i]>=tp)
				tmp.insert(ub.d[i],ub.ti[i]);
			if(vb.ti[i]>=tp)
				tmp.insert(vb.d[i],ub.ti[i]);
		}
		
		return tmp.check(k);
	};
	
	ll q;
	cin>>q;
	
	while(q--){
		ll u,v,k;
		cin>>u>>v>>k;
		cout<<(glca(u,v,k)?"YES":"NO")<<endl;
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
