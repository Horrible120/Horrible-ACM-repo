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

vector fct(200001,vector<ll>());

void init(){
	ll n=200000;
	for(ll i=1;i<=n;i++){
		for(ll j=i;j<=n;j+=i){
			fct[j].emplace_back(i);
		}
	}
}

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+1,0),b(n+1,0),diff(n+2,0),book(n+1,0),ans;
	
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	
	for(ll i=1;i<=n;i++){
		cin>>b[i];
	}
	
	for(ll i=1;i<=n;i++){
		if(a[i]<=b[i]){
			continue;
		}else{
			diff[b[i]]+=1;
			diff[a[i]]-=1;
		}
	}
	
	for(ll i=1;i<=n;i++){
		diff[i]+=diff[i-1];
		if(diff[i]){
			for(auto it:fct[i]){
				book[it]=1;
			}
		}
	}
	
	for(ll i=1;i<=n;i++){
		if(!book[i]){
			ans.emplace_back(i);
		}
	}
	
//	OOO
	cout<<ans.size()<<endl;
	for(auto it:ans){
		cout<<it<<' ';
	}
	cout<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
