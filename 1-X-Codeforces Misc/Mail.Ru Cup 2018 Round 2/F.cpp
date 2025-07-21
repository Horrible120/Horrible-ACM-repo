#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll n,k,ans=0;
	cin>>n>>k;
	
	vector<vector<pair<ll,ll>>> eg(n+1);
	
	for(ll i=2;i<=n;i++){
		ll v,w;
		cin>>v>>w;
		eg[v].emplace_back(make_pair(i,w));
		eg[i].emplace_back(make_pair(v,w));
	}
	
	vector<ll> val(n+1,0),vis(n+1,0);
	
	auto DFS=[&](auto &&self,ll u)->void{
		vis[u]=1;
		for(auto [v,w]:eg[u]){
			if(!vis[v]){
				val[v]=val[u]^w;
				self(self,v);
			}
		}
	};
	
	val[1]=0;
	DFS(DFS,1);
	
//	for(ll i=1;i<=n;i++)
//		cout<<i<<' '<<val[i]<<endl;
	
	vector<array<ll,2>> trie(2*n+1,{0,0});	//01trie前一层向这一层映射的儿子节点信息  
	vector<ll> last(2*n+1,0);	//节点在的编号
	vector<ll> now(2*n+1,0);	//节点对应的异或值编号
	vector<ll> siz(2*n+1,0);	//trie-siz
	
	ll cnt=0,tot=0;
	
//	for(ll i=1;i<=n;i++)
//		last[i]=now[i]=1;
	
	for(ll g=61;g>=0;g--){
		
		for(ll i=1;i<=tot;i++)
			siz[i]=trie[i][0]=trie[i][1]=0;
		
		cnt=0,tot=0;
		
		for(ll i=1;i<=n;i++){
			ll c=(val[i]>>g&1ll);
			if(!trie[last[i]][c]){
				tot++;
				trie[last[i]][c]=tot;
			}
			
			last[i]=trie[last[i]][c];
			
			siz[last[i]]++;
		}
		
		for(ll i=1;i<=n;i++){
			ll c=(val[i]>>g&1ll);
			cnt+=siz[trie[now[i]][c]];
		}
		
		if(k>cnt){
			k-=cnt;
			ans+=1ll<<g;
			for(ll i=1;i<=n;i++){
				ll c=(val[i]>>g&1ll);
				now[i]=trie[now[i]][c^1];
			}
		}
		else{
			for(ll i=1;i<=n;i++){
				ll c=(val[i]>>g&1ll);
				now[i]=trie[now[i]][c];
			}
		}
	}
	
//	OOO
	cout<<ans<<endl;
	
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
