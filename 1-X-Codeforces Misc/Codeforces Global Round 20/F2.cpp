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
	ll n,mx=0;
	cin>>n;
	vector<ll> a(n+1,0),b(n+1,0),cnt(n+1,0),du(2*n+1,0);
	vector<vector<ll>> edge(2*n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
		if(cnt[a[i]]>cnt[mx]){
			mx=a[i];
		}
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
		edge[n+b[i]].emplace_back(i);
	}
	
	for(ll i=1;i<=n;i++){
		if(a[i]!=mx){
			edge[i].emplace_back(n+a[i]);
			du[i]++;
		}
		if(b[i]!=mx){
			edge[n+b[i]].emplace_back(i);
			du[n+b[i]]++;
		}
	}
	
	queue<ll> que;
	for(ll i=1;i<=2*n;i++){
		if(du[i]==0){
			que.push(i);
		}
	}
	
	while(que.size()){
		ll u=que.front();
		que.pop();
		for(auto v:edge[u]){
			du[v]--;
			if(du[v]==0){
				que.push(v);
			}
		}
	}
	
	for(ll i=1;i<=2*n;i++){
		if(du[i]>0){
			cout<<"WA"<<endl;
			return;
		}
	}
	cout<<"AC"<<endl;
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
