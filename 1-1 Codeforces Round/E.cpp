#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,q,f=0;
	cin>>n>>q;
	v2ct<ll> eg(n+1,vector<ll>());
	vector<ll> col(n+1,0),v(n+1,0),fa(n+1,0),vis(n+1,0),Bson(n+1,0);
	set<ll> c2,c3;
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	for(ll i=1;i<=n-1;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	
	function<void(ll)> DFS=[&](ll u){
		vis[u]=1;
		for(auto v:eg[u]){
			if(!vis[v]){
				fa[v]=u;
				DFS(v);
			}
		}
	};
	
	fa[1]=0;
	DFS(1);
	
	auto shift=[&](ll u){
		ll fu=fa[u];
		
		if(col[u]==0){
			Bson[fu]++;
			if(Bson[fu]==2)
				c2.insert(fu);
			else if(Bson[fu]==3)
				c2.erase(fu),c3.insert((fu));
			f-=Bson[u];
			if(col[fu]==0)
				f++;
			col[u]=1;
		}
		else{
			Bson[fu]--;
			if(Bson[fu]==2)
				c3.erase(fu),
				c2.insert(fu);
			if(Bson[fu]==1)
				c2.erase(fu);
			f+=Bson[u];
			if(col[fu]==0)
				f--;
			col[u]=0;
		}
	};
	
	for(ll i=1;i<=n;i++)
		if(v[i])
			shift(i);
	
	while(q--){
		ll u;
		cin>>u;
		shift(u);
//		OOO
		if(c3.size()==0){
			if(c2.size()==1&&f==1&&col[fa[*c2.begin()]]==0){
				cout<<"YES"<<endl;
			}
			else if(c2.size()==0&&f==1){
				cout<<"YES"<<endl;
			}
			else{
				cout<<"NO"<<endl;
			}
		}
		else
			cout<<"NO"<<endl;
	}
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
