#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

using namespace std;
using namespace __gnu_pbds;

typedef int ll;
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
	ll n,tot=0;
	cin>>n;
	v2ct<ll> eg(n+1);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	class Node{
	public:
		vector<ll> dp;
		ll len,dfn,fa;
		ll hson,top;
		Node()=default;
	};
	
	vector<Node> tr(n+1,Node());
	vector<ll> ans(n+1,0);
	
	auto DFS1=[&](auto &&self,ll u)->void{
		tr[u].len=0;
		for(auto v:eg[u]){
			if(v!=tr[u].fa){
				tr[v].fa=u;
				self(self,v);
				if(tr[v].len+1>tr[u].len){
					tr[u].len=tr[v].len+1;
					tr[u].hson=v;
				}
			}
		}
	};
	
	auto DFS2=[&](auto &&self,ll u,ll top)->void{
		tr[u].dfn=++tot;
		tr[u].top=top;
		
		if(tr[u].hson){
			self(self,tr[u].hson,top);
		}
		
		for(auto v:eg[u]){
			if(!tr[v].dfn&&v!=tr[u].hson){
				self(self,v,v);
			}
		}
		
		if(tr[u].top==u)
			tr[u].dp.assign(tot-tr[u].dfn+2,0);
	};
	
	auto DFS3=[&](auto &&self,ll u)->void{
		auto &dp=tr[tr[u].top].dp;
		ll dlen=tr[tr[u].top].len-tr[u].len;
		
		for(auto v:eg[u])
			if(v!=tr[u].fa)
				self(self,v);
		
		dp[dlen]+=1;
		if(tr[u].hson)
			ans[u]=ans[tr[u].hson];
		
		for(auto v:eg[u]){
			if(v!=tr[u].hson&&v!=tr[u].fa){
				for(ll i=0;i<=tr[v].len;i++){
					dp[dlen+i+1]+=tr[v].dp[i];
					if(dp[dlen+i+1]>dp[ans[u]])
						ans[u]=dlen+i+1;
					else if(dp[dlen+i+1]==dp[ans[u]]&&dlen+i+1<ans[u])
						ans[u]=dlen+i+1;
				}
			}
		}
		
		if(dp[ans[u]]<=1)
			ans[u]=dlen;
	};
	
	tr[1].fa=1;
	DFS1(DFS1,1);
	
	tr[1].top=1;
	DFS2(DFS2,1,1);
	
//	for(ll i=1;i<=n;i++)
//		cout<<i<<' '<<tr[i].len<<' '<<tr[i].hson<<' '<<tr[i].top<<endl;
	
	DFS3(DFS3,1);
	
	for(ll i=1;i<=n;i++)
		cout<<ans[i]-(tr[tr[i].top].len-tr[i].len)<<endl;
	
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
