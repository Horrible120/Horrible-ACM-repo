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
	ll n,m;
	cin>>n>>m;
	vector<vector<pair<ll,ll>>> eg(n+1);
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		eg[u].emplace_back(v,w);
		eg[v].emplace_back(u,w);
	}

	vector<array<array<ll,2>,2>> dis(n+1);
	for(ll i=1;i<=n;i++)
		for(ll j=0;j<2;j++)
			for(ll k=0;k<2;k++) dis[i][j][k]=INF;

	std::priority_queue<array<ll,4>,vector<array<ll,4>>,greater<array<ll,4>>> que;
	dis[1][0][0]=0;
	que.push({0,1,0,0});
	while(!que.empty()){
		auto [d,u,a,b]=que.top();
		que.pop();
		if(d!=dis[u][a][b]) continue;
		for(ll i=0;i<(ll)eg[u].size();i++){
			auto [v,w]=eg[u][i];
			for(ll j=0;j<=1-a;j++){
				for(ll k=0;k<=1-b;k++){
					ll x=a|j,y=b|k,nd=d+(1-j+k)*w;
					if(dis[v][x][y]>nd){
						dis[v][x][y]=nd;
						que.push({nd,v,x,y});
					}
				}
			}
		}
	}
	for(ll i=2;i<=n;i++) cout<<dis[i][1][1]<<(i==n?'\n':' ');
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

//	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
