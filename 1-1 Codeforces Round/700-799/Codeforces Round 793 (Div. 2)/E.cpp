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
	vector<ll> v(n+1,0),rnk(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		rnk[v[i]]=i;
	}
	
	vector<vector<ll>> ans(n+1),que(n+1);
	map<pair<ll,ll>,ll> id;
	for(ll i=1;i<=m;i++){
		ll x,y;
		cin>>x>>y;
		id[make_pair(x,y)]=i;
		id[make_pair(y,x)]=i;
		ans[x].emplace_back(y);
		ans[y].emplace_back(x);
	}
	
	vector<ll> vis(n+1,0),fa(n+1,0),val(n+1,0);
	
	auto tcmp=[&](const ll &aa,const ll &bb)->bool{
		return val[aa]>val[bb];
	};
	
	vector<vector<ll>> eg(n+1);
	vector<ll> in(n+1,0);
	
	for(ll i=1;i<=n;i++){
		if(vis[i]) continue;
		ll u=i;
		while(!vis[u]){
			vis[u]=1;
			que[i].emplace_back(u);
			fa[u]=i;
			u=rnk[u];
		}
		
		ll k=que[i].size();
		
		for(ll j=0;j<k;j++){
			val[que[i][j]]=j;
		}
		
		for(ll j=0;j<k;j++){
			sort(ans[que[i][j]].begin(),ans[que[i][j]].end(),tcmp);
			for(ll l=0;l<ans[que[i][j]].size();l++){
				if(l>0) eg[id[make_pair(que[i][j],ans[que[i][j]][l-1])]].emplace_back(id[make_pair(que[i][j],ans[que[i][j]][l])]),in[id[make_pair(que[i][j],ans[que[i][j]][l])]]++;
			}
			val[que[i][j]]+=k;
		}
		
	}
	
//	for(ll i=1;i<=m;i++){
//		cout<<">>> "<<i<<' ';
//		for(auto it:eg[i]){
//			cout<<it<<' ';
//		}
//		cout<<endl;
//	}
	
	queue<ll> q;
	for(ll i=1;i<=m;i++){
		if(in[i]==0){
			q.push(i);
		}
	}
	
	while(q.size()){
		ll u=q.front();
		q.pop();
		cout<<u<<' ';
		for(auto it:eg[u]){
			in[it]--;
			if(in[it]==0) q.push(it);
		}
	}
	
	cout<<endl;
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
