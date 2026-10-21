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

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<ll>> eg(n+1);
	vector<ll> adj(n+1,0);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		u--;v--;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
		adj[u]|=(1<<v);
		adj[v]|=(1<<u);
	}
	
	vector<ll> dp((1<<n)+1,0);
	
	dp[0]=(1<<n)-1;
	
	for(ll i=1;i<(1<<n);i++){
		ll st=n,flag=1;
		
		for(ll k=0;k<n;k++){
			if((i>>k)&1){
				if(st==n){
					st=k;
					if((i&i-1)==0){
						dp[i]|=adj[st];
					}
				}else if((dp[i^(1<<k)]>>k)&1){
					dp[i]|=adj[k];
				}
			}else if(!(adj[k]&i)){
				flag=0;
			}
		}
		
		if(flag&&(dp[i]>>st&1)){
			
//			cout<<st<<' '<< bitset<sizeof(i)*8>(i) << endl;
			
			vector<ll> ans(n+1,0);
			
			auto gen=[&](auto &&self,ll cur,ll tar)->void{
				if((cur^(1<<st))==0){
					ans[st]=tar+1;
					return;
				}
				for(ll j=0;j<n;j++){
					if(j!=st){
						if(cur>>j&1){
							if((dp[cur^(1<<j)]>>j&1)&&(adj[j]>>tar&1)){
								ans[j]=tar+1;
								self(self,cur^(1<<j),j);
								return;
							}
						}
					}
				}
			};
			
			if((i&i-1)==0){
				ans[st]=eg[st][0]+1;
			}else{
				gen(gen,i,st);
			}
			
			for(ll j=0;j<n;j++){
				if(!(i>>j&1)){
					for(auto it:eg[j]){
						if(i>>it&1){
							ans[j]=it+1;
						}
					}
				}
			}
			
			cout<<"YES"<<endl;
			for(ll i=0;i<n;i++){
				cout<<ans[i]<<' ';
			}
			cout<<endl;
			return;
		}
	}
	cout<<"NO"<<endl;
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
