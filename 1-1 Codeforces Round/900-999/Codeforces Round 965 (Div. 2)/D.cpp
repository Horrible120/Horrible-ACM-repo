#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
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
	
	v2ct<ll> eg(n+1);
	set<ll> arv;
	vector<ll> dp(n+1,INF);
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		if(u>v)
			swap(u,v);
		eg[u].emplace_back(v);
	}
	
	for(ll i=1;i<=n-1;i++)
		eg[i].emplace_back(i+1);
	
	struct cmp{
		bool operator ()(const pair<ll,ll> &a,const pair<ll,ll> &b)const{
			if(a.second-a.first!=b.second-b.first)
				return a.second-a.first<b.second-b.first;
			return a.first<b.first;
		}
	};
	
	set<pair<ll,ll>,cmp> s;
	
	string ans;
	
	dp[1]=0;
	for(ll i=1;i<=n;i++)
		s.insert(make_pair(i,dp[i]));
	
	for(ll i=1;i<=n-1;i++){
		ll u=i-1;
		if(i>1)
			for(auto v:eg[u]){
				if(dp[u]+1<dp[v]){
					if(s.size())
						s.erase(s.find(make_pair(v,dp[v])));
					dp[v]=dp[u]+1;
					s.insert(make_pair(v,dp[v]));
				}
			}
		
		if(i==1)
			ans+='1';
		else if(s.size()){
			auto [idx,dis]=*s.begin();
//			cout<<idx<<' '<<dis<<endl;
			if(dis<idx-i)
				ans+='0';
			else
				ans+='1';
		}
		else
			ans+='1';
		
		s.erase(s.find(make_pair(i,dp[i])));
	}
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
