#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

const ll MAXN=1e7;
vector<int> minp,prm,mob;
void sieve(){
	minp.resize(MAXN);
	mob.resize(MAXN);
	
	mob[1]=1;
	
	for(ll i=2;i<=MAXN;i++){
		if(!minp[i]){
			minp[i]=i;
			mob[i]=-1;
			prm.emplace_back(i);
		}
		for(auto j:prm){
			if(j>minp[i]||i*j>MAXN){
				break;
			}
			minp[i*j]=j;
			if(i%j) mob[i*j]=-mob[i];
			else mob[i*j]=0;
		}
	}
}

ll tt=1;



void solve(){
	ll n,x,ans=0;
	cin>>n>>x;
	vector<vector<ll>> eg(n+1);
	vector<ll> vis(n+1,0);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<int> fct,v(n+1,0);
	vector<int> sum(n+1,0);
	ll paths=0;
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	auto DFS=[&](auto &&self,ll u,ll y)->void{
		vis[u]=1;
		if(y%v[u]==0){
			sum[u]=1;
			paths+=1;
		}else{
			sum[u]=0;
		}
		
		for(auto it:eg[u]){
			if(!vis[it]){
				self(self,it,y);
				if(y%v[u]==0){
					paths+=sum[u]*sum[it];
					sum[u]+=sum[it];
				}
			}
		}
	};
	
	for(ll i=1;i<=sqrtl(x);i++){
		if(x%i==0){
			fct.emplace_back(i);
			if(x!=i*i){
				fct.emplace_back(x/i);
			}
		}
	}
	
	for(auto it:fct){
		paths=0;
		for(ll i=1;i<=n;i++){
			vis[i]=0;
		}
		DFS(DFS,1,it);
//		cout<<it<<' '<<paths<<endl;
		ans+=paths*mob[x/it];
	}
	
//	OOO
	cout<<ans<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	sieve();
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
