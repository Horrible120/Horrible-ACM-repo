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
	vector<ll> w(n+1,0),cnt(n+1,0),ans(m+1,0),vis(n+1,0),vism(m+1,0);
	vector<pair<ll,ll>> v(m+1);
	vector<vector<ll>> stk(n+1);
	
	
	for(ll i=1;i<=n;i++){
		cin>>w[i];
	}
	
	for(ll i=1;i<=m;i++){
		auto &[x,y]=v[i];
		cin>>x>>y;
		cnt[x]++;
		cnt[y]++;
		stk[x].emplace_back(i);
		stk[y].emplace_back(i);
	}
	
	queue<ll> que;
	for(ll i=1;i<=n;i++){
		if(cnt[i]<=w[i]){
			que.push(i);
			vis[i]=1;
		}
	}
	
	ll top=0;
	
	while(que.size()){
		ll u=que.front();
		que.pop();
		
		
		
		for(auto it:stk[u]){
			if(!vism[it]){
				ans[++top]=it;
				auto &[x,y]=v[it];
				vism[it]=1;
				cnt[x]--;
				cnt[y]--;
				if(cnt[x]<=w[x]&&!vis[x]){
					que.push(x);
					vis[x]=1;
				}
				if(cnt[y]<=w[y]&&!vis[y]){
					que.push(y);
					vis[y]=1;
				}
			}
		}
	}
	
//	OOO
//	cout<<top<<endl;
	
	if(top==m){
		cout<<"ALIVE"<<endl;
		for(ll i=m;i>=1;i--){
			cout<<ans[i]<<' ';
		}
		cout<<endl;
	}else{
		cout<<"DEAD"<<endl;
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
