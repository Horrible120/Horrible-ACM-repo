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
	ll n;
	cin>>n;
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> vis(n+1,0);
	vector<array<ll,2>> dp(n+1,{{}});
	vector<array<ll,2>> ans;
	
	auto DFS=[&](this auto &&self,ll u)->void{
		vis[u]=1;
		bool flag=0;
		ll cnt=0;
		vector<ll> tmp;
		for(auto v:eg[u]) if(!vis[v]){
			tmp.emplace_back(v);
			self(v);
			flag|=dp[v][1];
			cnt++;
		}
		if(u!=1){
			if(cnt&1){
				dp[u][0]=flag;
				ll d=0;
				for(auto v:tmp){
					if(!dp[u][1]){
						dp[u][1]=dp[v][1]?dp[v][1]:v;
					}else if(!d){
						d=dp[v][1]?dp[v][1]:v;
					}else{
						ans.push_back({{d,dp[v][1]?dp[v][1]:v}});
						d=0;
					}
				}
			}else{
				dp[u][0]=1;
				ll d=0,kl=0;
				if(flag){
					for(auto v:tmp){
						if(kl==0&&dp[v][1]){
							ans.push_back({{dp[v][1],u}});
							kl=v;
							break;
						}
					}
					
					for(auto v:tmp) if(v!=kl){
						if(!dp[u][1]){
							dp[u][1]=dp[v][1]?dp[v][1]:v;
						}else if(!d){
							d=dp[v][1]?dp[v][1]:v;
						}else{
							ans.push_back({{d,dp[v][1]?dp[v][1]:v}});
							d=0;
						}
					}
					
				}else{
					for(auto v:tmp){
						if(!d){
							d=dp[v][1]?dp[v][1]:v;
						}else{
							ans.push_back({{d,dp[v][1]?dp[v][1]:v}});
							d=0;
						}
					}
				}
			}
		}else{
			if(cnt&1){
				dp[u][0]=flag;
				ll kl=0,d=0;
				for(auto v:tmp){
					if(kl==0&&dp[v][1]){
						ans.push_back({{dp[v][1],u}});
						kl=v;
						break;
					}
				}
				for(auto v:tmp) if(v!=kl){
					if(!d){
						d=dp[v][1]?dp[v][1]:v;
					}else{
						ans.push_back({{d,dp[v][1]?dp[v][1]:v}});
						d=0;
					}
				}
			}else{
				dp[u][0]=1;
				if(dp[1][0]){
					ll d=0;
					for(auto v:tmp){
						if(!d){
							d=dp[v][1]?dp[v][1]:v;
						}else{
							ans.push_back({{d,dp[v][1]?dp[v][1]:v}});
							d=0;
						}
					}
				}
			}
			
			
			
		}
		
	};
	
	DFS(1);
	
	if(dp[1][0]){
		cout<<ans.size()<<endl;
		for(auto [u,v]:ans) cout<<u<<' '<<v<<'\n';
	}else{
		cout<<-1<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
		cout.flush();
	}
	cout.flush();
	
	return 0;
}
