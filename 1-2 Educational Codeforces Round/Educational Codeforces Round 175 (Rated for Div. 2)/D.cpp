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

const ll INF = 4e18, Mod = 998244353;

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> eg[n+1],fa(n+1);
	for(ll i=2;i<=n;i++){
		ll x;
		cin>>x;
		fa[i]=x;
		eg[x].emplace_back(i);
		eg[i].emplace_back(x);
	}
	vector<ll> dep(n+1),cnt(n+1),vis(n+1);
	dep[1]=1;
	queue<ll> que;
	map<ll,ll> mp;
	que.push(1);
	while(que.size()){
		ll u=que.front();
		que.pop();
		vis[u]=1;
		if(u==1||fa[u]==1){
			cnt[u]=1;
			mp[dep[u]]++;
		}
		else{
			cnt[u]=((mp[dep[u]-1]-cnt[fa[u]])%Mod+Mod)%Mod;
			mp[dep[u]]=(mp[dep[u]]+cnt[u])%Mod;
		}
		for(auto v:eg[u]){
			if(vis[v]) continue;
			dep[v]=dep[u]+1;
			que.push(v);
		}
	}
	
	ll ans=0;
	for(ll i=1;i<=n;i++)
		ans=(ans+cnt[i])%Mod;
//	OOO
	cout<<ans<<endl;
	
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
