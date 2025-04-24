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
	ll n,m,tot=0,top=0,cnt=0;
	cin>>n>>m;
	v2ct<ll> eg(2*n+1,vector<ll>());
	vector<ll> dfn(2*n+1,0),low(2*n+1,0),col(2*n+1,0),instk(2*n+1,0),stk(2*n+1,0);
	
	auto F=[&](ll x){
		if(x&1)
			return x+1;
		else
			return x-1;
	};
	
	for(ll i=1;i<=m;i++){
		ll a,b;
		cin>>a>>b;
		
		eg[a].emplace_back(F(b));
		eg[b].emplace_back(F(a));
		
//		cout<<F(a)<<" "<<F(b)<<endl;
	}
	
	auto DFS=[&](auto &&self,ll u)->void{
		dfn[u]=++tot;
		low[u]=tot;
		stk[++top]=u;
		instk[u]=1;
		for(auto v:eg[u]){
			if(!dfn[v]){
				self(self,v);
				low[u]=min(low[u],low[v]);
			}
			else if(instk[v])
				low[u]=min(low[u],dfn[v]);
		}
		
		if(low[u]==dfn[u]){
			cnt++;
			while(top>0&&low[stk[top]]>=dfn[u]){
				instk[stk[top]]=false;
				col[stk[top--]]=cnt;
			}
		}
	};
	
	for(ll i=1;i<=2*n;i++)
		if(!dfn[i])
			DFS(DFS,i);
	
	vector<ll> ans(n+1,0);
	
//	for(ll i=1;i<=2*n;i++)
//		cout<<col[i]<<' ';
//	cout<<endl;
	
	for(ll i=1;i<=n;i++){
		ll a=2*i-1,b=2*i;
		if(col[a]==col[b]){
			cout<<"NIE"<<endl;
			return;
		}
		
		if(col[a]<col[b])
			ans[i]=a;
		else
			ans[i]=b;
	}
	
	for(ll i=1;i<=n;i++)
		cout<<ans[i]<<endl;
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
