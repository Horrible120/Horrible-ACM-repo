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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	ll cnt=0,low=0,high=0;
	for(ll i=1;i<n;i++){
		if(v[i+1]<=v[i]){
			cnt++;
			if(cnt==1)
				low=i;
			high=i+1;
		}
	}
	ll ans=0;
	
	if(cnt==0){
		cout<<0<<endl;
		return;
	}
	
	if(v[high]-v[low]<=high-low-1)
		cnt--,ans++;
	ans+=(cnt+1)/2;
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
