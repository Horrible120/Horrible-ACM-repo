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
	ll n,k,ans=INF;
	cin>>n>>k;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		ans=min(ans,v[i]);
	}
	
	if(k>=3){
		cout<<0<<endl;
		return;
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			if(i!=j) ans=min(ans,abs(v[i]-v[j]));
		}
	}
	
	if(k==2){
		vector<ll> su;
		for(ll i=1;i<=n;i++){
			for(ll j=1;j<=n;j++){
				su.emplace_back(abs(v[i]+v[j]));
			}
		}
		
		sort(su.begin(),su.end());
		sort(v.begin()+1,v.end());
		
		ll pos=1;
		for(auto it:su){
			while(pos<n&&v[pos+1]<=it){
				pos++;
			}
			ans=min(ans,it-v[pos]);
			if(pos<n) ans=min(ans,v[pos+1]-it);
		}
	}
	
	
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
