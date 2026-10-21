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
	ll n,m,k;
	cin>>n>>m>>k;
	
	vector<vector<ll>> row(n+1,vector<ll>());
	
	for(ll i=1;i<=k;i++){
		ll x,y;
		cin>>x>>y;
		row[x].emplace_back(y);
	}
	
	
	for(ll i=1;i<=n;i++){
		sort(row[i].begin(),row[i].end());
	}
	
	set<ll> L,W;
	
	for(ll i=1;i<=m;i++) W.insert(i);
	
	for(ll i=n;i>=1;i--){
		ll cmax=row[i].size()?row[i].back():0;
		for(auto it:row[i]) W.erase(it);
		if(i>1){
			if(W.size()&&cmax<*W.rbegin()){
				W.erase(*W.rbegin());
			}
		}else{
			if(W.size()&&cmax<*W.rbegin()&&*W.rbegin()==1){
				cout<<"Bhinneka"<<endl;
			}else{
				cout<<"Chaneka"<<endl;
			}
		}
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
