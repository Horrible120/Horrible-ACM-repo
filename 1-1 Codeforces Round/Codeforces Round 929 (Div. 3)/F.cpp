#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	v2ct<ll> dis(n+1,vector<ll>(m+1,INF)),mp(n+1,vector<ll>(m+1,0)),vis(n+1,vector<ll>(m+1,0));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			cin>>mp[i][j];
			if(mp[i][j])
				vis[i][j]=1;
		}
	}
	dis[1][1]=0;
	
	queue<pair<ll,ll>> q;
	q.push(make_pair(1,1));
	vis[1][1]=1;
	while(!q.empty()){
		auto [x,y]=q.front();
		q.pop();
		
		if(mp[(x+1)%n+1][y]==0&&mp[x%n+1][y]==0)
			if(!vis[(x+1)%n+1][y]){
				dis[(x+1)%n+1][y]=dis[x][y]+1;
				vis[(x+1)%n+1][y]=1;
				q.push(make_pair((x+1)%n+1,y));
			}
		if(y<m)
			if(mp[x%n+1][y+1]==0)
				if(!vis[x%n+1][y+1]){
					dis[x%n+1][y+1]=dis[x][y]+1;
					vis[x%n+1][y+1]=1;
					q.push(make_pair(x%n+1,y+1));
					
				}
	}
	
//	for(ll i=1;i<=n;i++){
//		for(ll j=1;j<=m;j++)
//			cout<<(dis[i][j]<n*m?dis[i][j]:-1)<<' ';
//		cout<<endl;
//	}
	
	ll ans=INF;
	for(ll i=1;i<=n;i++){
		ans=min(ans,dis[i][m-1]+(n*m+i-dis[i][m-1])%n+1);
		ans=min(ans,dis[i][m-1]+(n*m+-i+dis[i][m-1])%n+1);
	}
//	OOO
	if(ans<=n*m)
		cout<<ans<<endl;
	else
		cout<<-1<<endl;
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
