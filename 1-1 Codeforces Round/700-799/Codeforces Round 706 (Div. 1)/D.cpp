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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<vector<ll>> eg(n+1);
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}

	vector<vector<ll>> dis(n+1,vector<ll>(n+1,-1));
	for(ll s=1;s<=n;s++){
		queue<ll> que;
		que.push(s);
		dis[s][s]=0;
		while(!que.empty()){
			ll u=que.front();
			que.pop();
			for(ll i=0;i<(ll)eg[u].size();i++){
				ll v=eg[u][i];
				if(dis[s][v]!=-1)
					continue;
				dis[s][v]=dis[s][u]+1;
				que.push(v);
			}
		}
	}

	vector<vector<ll>> ans(n+1,vector<ll>(n+1));
	for(ll x=1;x<=n;x++){
		for(ll y=x;y<=n;y++){
			ll len=dis[x][y],cnt=0;
			for(ll v=1;v<=n;v++)
				if(dis[x][v]+dis[y][v]==len)
					cnt++;
			if(cnt!=len+1)
				continue;

			ll res=1;
			for(ll v=1;v<=n;v++){
				if(dis[x][v]+dis[y][v]==len)
					continue;
				ll ways=0;
				for(ll i=0;i<(ll)eg[v].size();i++){
					ll p=eg[v][i];
					if(dis[x][p]==dis[x][v]-1&&dis[y][p]==dis[y][v]-1)
						ways++;
				}
				res=res*ways%Mod;
			}
			ans[x][y]=ans[y][x]=res;
		}
	}

	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			cout<<ans[i][j]<<" \n"[j==n];
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
