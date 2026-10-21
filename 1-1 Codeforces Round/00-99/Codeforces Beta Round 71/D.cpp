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
	ll n,k,l;
	cin>>n>>k>>l;
	vector<ll> pos(n+2,0),op(l+1,0);
	for(ll i=1;i<=k;i++){
		ll x;
		cin>>x;
		pos[x]=1;
	}
	
	n++;
	for(ll i=n;i>1;i--){
		pos[i]^=pos[i-1];
		pos[i]&=1;
	}
	
	vector<ll> point;
	for(ll i=1;i<=n;i++){
		if(pos[i]){
//			cout<<i<<' ';
			point.emplace_back(i);
		}
	}
//	cout<<endl;
	
	for(ll i=1;i<=l;i++){
		cin>>op[i];
	}
	
//	vector<vector<ll>> eg(n+1,0);
	
	queue<ll> que;
	ll m=point.size();
	vector<vector<ll>> w(m,vector<ll>(m,INF));
	for(ll i=0;i<m;i++){
		while(que.size()) que.pop();
		
		vector<ll> dis(n+1,INF),vis(n+1,0);
		que.push(point[i]);
		dis[point[i]]=0;
		vis[point[i]]=1;
		
		while(que.size()){
			ll u=que.front();
			que.pop();
			for(auto it:op){
				if(u+it<=n&&!vis[u+it]){
					dis[u+it]=dis[u]+1;
					que.push(u+it);
					vis[u+it]=1;
				}
				if(u-it>=1&&!vis[u-it]){
					dis[u-it]=dis[u]+1;
					que.push(u-it);
					vis[u-it]=1;
				}
			}
		}
		
		for(ll j=0;j<m;j++) if(j!=i){
			w[i][j]=dis[point[j]];
		}
	}
	
//	for(ll u1=0;u1<m;u1++){
//			for(ll u2=0;u2<m;u2++){
//				cout<<w[u1][u2]<<' ';
//			}
//		cout<<endl;
//	}
	
	vector<ll> dp((1<<m)+1,INF);
	dp[0]=0;
	for(ll i=0;i<(1<<m);i++){
		if(~__builtin_popcount(i)&1){
			for(ll u1=0;u1<m;u1++){
				if(~(i>>u1)&1){
					for(ll u2=0;u2<m;u2++){
						if(u2^u1&&~(i>>u2)&1){
							dp[i^(1<<u1)^(1<<u2)]=min(dp[i^(1<<u1)^(1<<u2)],dp[i]+w[u1][u2]);
						}
					}
				}
			}
		}
	}
	if(dp[(1<<m)-1]<INF){
		cout<<dp[(1<<m)-1]<<endl;
	}else{
		cout<<-1<<endl;
	}
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
