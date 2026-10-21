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
	int n;
	cin>>n;

	vector<vector<pair<int,int>>> g(n+1);
	int W=0;
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
		W=max(W,w);
	}

	if(W==0){
		for(int i=1;i<=n;i++) cout<<0<<" \n"[i==n];
		return;
	}

	vector<int> fa(n+1),ord(1,1);
	for(int i=0;i<(int)ord.size();i++){
		int u=ord[i];
		for(auto [v,w]:g[u]){
			if(v==fa[u]) continue;
			fa[v]=u;
			ord.push_back(v);
		}
	}

	using us=unsigned short;
	const us inf=numeric_limits<us>::max();
	int S=2*W;
	vector<us> dp(1ll*(n+1)*S);
	vector<int> ans(n+1);

	for(int k=n-1;k>=0;k--){
		int u=ord[k];
		us *fu=&dp[1ll*u*S];
		for(int x=0;x<S;x++) fu[x]=x;

		for(auto [v,w]:g[u]){
			if(fa[v]!=u) continue;
			us *fv=&dp[1ll*v*S];
			for(int x=0;x<S;x++){
				us cur=inf;
				if(x>=w) cur=min(cur,fv[x-w]);
				if(x+w<S) cur=min(cur,fv[x+w]);
				fu[x]=max(fu[x],cur);
			}
		}

		ans[u]=S;
		for(int x=0;x<S;x++) ans[u]=min(ans[u],(int)fu[x]);
	}

	for(int i=1;i<=n;i++) cout<<ans[i]<<" \n"[i==n];
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
