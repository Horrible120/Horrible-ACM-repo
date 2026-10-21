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
	ll n;
	cin>>n;
	vector<vector<vector<ll>>> w(n+1,vector<vector<ll>>(n+1,vector<ll>(n+1,0)));
	for(ll i=1;i<n;i++){
		for(ll j=i+1;j<=n;j++){
			string s;
			cin>>s;
			for(ll k=0;k<n;k++){
				w[i][j][k+1]=s[k]-'0';
				w[j][i][k+1]=s[k]-'0';
			}
		}
	}
	
//	OOO
	
	vector<vector<ll>> eg(n+1),lca(n+1,vector<ll>(n+1,0));
	for(ll i=2;i<=n;i++){
		for(ll j=1;j<=n;j++){
			eg[j].assign(n+1,0);
		}
		
//		OOO
		
		eg[1][i]=1;
		eg[i][1]=1;
		
		vector<ll> vis(n+1,0);
		vector<ll> adj(n+1,0);
		queue<ll> que;
		que.push(1);
		vis[1]=1;
		adj[1]=i;
		que.push(i);
		vis[i]=1;
		adj[i]=1;
		
		ll cnt=0;
		
		while(que.size()){
			ll u=que.front();
			que.pop();
			++cnt;
			
//			cout<<u<<endl;
			
			for(ll j=1;j<=n;j++){
				if(w[j][adj[u]][u]){
					eg[u][j]=1;
					eg[j][u]=1;
					if(!vis[j]){
						que.push(j);
						vis[j]=1;
						adj[j]=u;
					}
				}
			}
		}
		
//		OOO
		
		if(cnt<n) continue;
		
		vector<ll> fa(n+1,0),dep(n+1,0);
		auto DFS=[&](auto &&self,ll u)->void{
			for(ll j=1;j<=n;j++) if(eg[u][j]&&!fa[j]){
				fa[j]=u;
				dep[j]=dep[u]+1;
				self(self,j);
			}
		};
		
		fa[1]=1;
		dep[1]=1;
		
		DFS(DFS,1);
		
		for(ll j=1;j<=n;j++){
			for(ll k=1;k<=n;k++){
				ll a=j,b=k;
				if(dep[a]<dep[b]) swap(a,b);
				while(dep[a]>dep[b]) a=fa[a];
				while(a!=b) a=fa[a],b=fa[b];
				lca[j][k]=lca[k][j]=a;
			}
		}
		
		ll flag=1;
		
		for(ll j=1;j<n&&flag;j++){
			for(ll k=j+1;k<=n;k++){
				for(ll l=1;l<=n;l++){
					if((dep[j]+dep[l]-2*dep[lca[j][l]]==dep[k]+dep[l]-2*dep[lca[k][l]])^(w[j][k][l])) flag=0;
				}
			}
		}
		
		if(flag){
			cout<<"YES"<<endl;
			for(ll j=1;j<=n;j++){
				for(ll k=j+1;k<=n;k++){
					if(eg[j][k]){
						cout<<j<<' '<<k<<endl;
					}
				}
			}
			return ;
		}
	}
	cout<<"NO"<<endl;
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
