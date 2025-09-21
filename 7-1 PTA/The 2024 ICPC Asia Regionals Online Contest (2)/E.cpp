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
	ll n,m,d,k;
	cin>>n>>m>>d;
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	cin>>k;
	
	vector<array<ll,2>> fir(n+1);
	
	for(ll i=1;i<=n;i++){
		fir[i][0]=fir[i][1]=-1;
	}
	
	vector<pll> bot;
	for(ll i=1;i<=k;i++){
		ll x;
		cin>>x;
		bot.emplace_back(make_pair(x,0));
		fir[x][0]=0;
	}
	
	for(ll i=1;i<=d;i++){
		if(bot.size()==0) break;
		vector<pll> tmp;
		for(auto [u,x]:bot){
			for(auto v:eg[u]){
				if(x==1){
					if(fir[u][1]>=0&&fir[v][0]==-1){
						fir[v][0]=fir[u][1]+1;
						tmp.emplace_back(v,0);
					}
				}else{
					if(fir[u][0]>=0&&fir[v][1]==-1){
						fir[v][1]=fir[u][0]+1;
						tmp.emplace_back(v,1);
					}
				}
			}
		}
		bot=tmp;
	}
	
	
	
	vector<array<ll,2>> dis(n+1),lst(n+1);
	
	
	for(ll i=1;i<=n;i++){
		dis[i][0]=dis[i][1]=-1;
	}
	
	dis[1][0]=0;
	
	vector<pll> q;
	q.emplace_back(1,0);
	
	while(q.size()){
		vector<pll> tmp;
		for(auto [u,x]:q){
			for(auto v:eg[u]){
				if(x==0){
					if(dis[u][0]>=0&&dis[v][1]==-1&&(fir[v][1]>dis[u][0]+1||fir[v][1]==-1)){
						dis[v][1]=dis[u][0]+1;
						lst[v][1]=u;
						tmp.emplace_back(v,1);
					}
				}else{
					if(dis[u][1]>=0&&dis[v][0]==-1&&(fir[v][0]>dis[u][1]+1||fir[v][0]==-1)){
						dis[v][0]=dis[u][1]+1;
						lst[v][0]=u;
						tmp.emplace_back(v,0);
					}
				}
			}
		}
		q=tmp;
	}
	
	vector<ll> ans;
	ans.emplace_back(n);
	
	if(dis[n][0]==-1&&dis[n][1]==-1){
		cout<<-1<<endl;
		return;
	}else if((dis[n][0]>=0&&dis[n][1]>=dis[n][0])||dis[n][1]==-1){
		ll tmp=0,cur=n;
		while(cur!=1){
			cur=lst[cur][tmp];
			tmp^=1;
			ans.emplace_back(cur);
		}	
	}else{
		ll tmp=1,cur=n;
		while(cur!=1){
			cur=lst[cur][tmp];
			tmp^=1;
			ans.emplace_back(cur);
		}	
	}
	
	cout<<ans.size()-1<<endl;
	for(ll i=ans.size()-1;i>=0;i--){
		cout<<ans[i]<<" \n"[i==0];
	}
	cout.flush();
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
