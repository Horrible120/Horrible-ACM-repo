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
	vector<vector<ll>> eg(n+1);
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	vector<ll> dep(n+1,0),ans(n+1,0),vis(n+1,0);
	queue<ll> que;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			dep[j]=0;
			vis[j]=0;
		}
		que.push(i);
		vis[i]=1;
		ll cnt=1,sum=0;
		ans[1]=n-1;
		while(que.size()){
			ll u=que.front();
			que.pop();
			for(auto v:eg[u]){
				if(!vis[v]){
					que.push(v);
					vis[v]=1;
					dep[v]=dep[u]+1;
					cnt++;
					sum+=dep[v];
					ans[cnt]=max(ans[cnt],cnt*(n-1)-sum*2);
				}
			}
		}
	}
	
	for(ll i=0;i<=n;i++){
		cout<<ans[i]<<" \n"[i==n];
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
