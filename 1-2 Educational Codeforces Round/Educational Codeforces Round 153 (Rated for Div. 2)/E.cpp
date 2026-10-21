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
	string s{};
	cin>>s;
	
	ll n=s.size();
	ll m=n+26*26;
	
	vector<vector<array<ll,2>>> eg(n+26*26,vector<array<ll,2>>());
	
	for(ll i=1;i<n;i++){
		ll tmp=(s[i-1]-'a')*26+(s[i]-'a');
		eg[i].emplace_back(array<ll,2>{n+tmp,1});
		eg[n+tmp].emplace_back(array<ll,2>{i,0});
		if(i>1){
			eg[i].emplace_back(array<ll,2>{i-1,1});
			eg[i-1].emplace_back(array<ll,2>{i,1});
		}
	}
	
	deque<ll> deq;
	
	vector<vector<ll>> dis(26*26,vector<ll>(m+1,INF));
	for(ll i=0;i<26*26;i++){
		deq.clear();
		
		deq.push_back(n+i);
		dis[i][n+i]=0;
		
		while(!deq.empty()){
			ll u=deq.front();
			deq.pop_front();
			for(auto [v,w]:eg[u]){
				if(dis[i][v]>dis[i][u]+w){
					dis[i][v]=dis[i][u]+w;
					if(w){
						deq.push_back(v);
					}else{
						deq.push_front(v);
					}
				}
				
			}
		}
	}
	
	ll q;
	cin>>q;
	while(q--){
		ll u,v;
		cin>>u>>v;
		
		ll res=abs(u-v);
		
		for(ll i=0;i<26*26;i++){
			res=min(res,dis[i][u]+dis[i][v]+1ll);
		}
		cout<<res<<'\n';
	}
	
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
