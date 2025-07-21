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

bitset<100001> dp0,dp1;

void solve(){
	ll n,m,c;
	cin>>n>>m>>c;
	v2ct<ll> eg(n+1,vector<ll>());
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> col(n+1,0),dfn(n+1,0),low(n+1,0),stk(n+1,0),instk(n+1,0),fa(n+1,0),nsiz(n+1,0);
	ll tot=0,cnt=0,top=0;
	
	auto DFS=[&](auto &&self,ll u)->void{
		ll flag=0;
		
		dfn[u]=++tot;
		low[u]=dfn[u];
		stk[++top]=u;
		instk[u]=1;
		
		for(auto v:eg[u]){
			if(!dfn[v]){
				fa[v]=u;
				self(self,v);
				low[u]=min(low[u],low[v]);
			}
			else if(v!=fa[u]||flag)
				low[u]=min(low[u],dfn[v]);
			else
				flag=1;
		}
		
		if(low[u]==dfn[u]){
			cnt++;
			while(top>0&&low[stk[top]]>=dfn[u]){
				col[stk[top]]=cnt;
				nsiz[cnt]++;
				top--;
			}
		}
	};
	
	for(ll i=1;i<=n;i++)
		if(!dfn[i])
			DFS(DFS,i);
	
	if(cnt==1){
//		OOO
		cout<<-1<<endl;
		return;
	}
	
	v2ct<ll> eg2(cnt+1,vector<ll>());
	
//	for(ll i=1;i<=n;i++)
//		cout<<">>> "<<i<<' '<<col[i]<<endl;
	
	vector<ll> vis(cnt+1,0),siz(cnt+1,0);
	
	for(ll u=1;u<=n;u++)
		for(auto v:eg[u])
			if(col[u]!=col[v])
				eg2[col[u]].emplace_back(col[v]);
	
	ll trs=0;
	v2ct<ll> tr(1);
	
	auto DFS2=[&](auto &&self,ll u)->void{
		vis[u]=1;
		siz[u]=nsiz[u];
		tr[trs].emplace_back(u);
		for(auto v:eg2[u]){
			if(!vis[v]){
				self(self,v);
				siz[u]+=siz[v];
			}
		}
	};
	
	for(ll i=1;i<=cnt;i++){
		if(!vis[i]){
			trs++;
			tr.emplace_back(vector<ll>());
			DFS2(DFS2,i);
//			cout<<">>> "<<i<<' '<<siz[i]<<endl;
		}
	}
	
	dp0.reset();
	dp1.reset();
	
	dp0[0]=1;
//	dp1[0]=1;
	
	for(ll i=1;i<=trs;i++){
		ll ti=tr[i].size();
		
		dp1|=dp1<<siz[tr[i][0]];
		
		for(ll v=1;v<ti;v++){
			dp1|=dp0<<siz[tr[i][v]];
//			dp1|=dp0<<(siz[tr[i][0]]-siz[tr[i][v]]);
		}
		
		dp0|=dp0<<siz[tr[i][0]];
	}
	
	ll ans=INF;
	for(ll i=0;i<=n;i++){
		if(dp0[i]||dp1[i])
			ans=min(ans,i*i+(n-i)*(n-i));
	}
	
	
//	OOO
	cout<<ans+c*(trs-1)<<endl;
	
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
