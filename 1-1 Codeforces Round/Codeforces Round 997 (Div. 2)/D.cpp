#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,ans;
	cin>>n;
	ans=n*(n+1)/2;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	for(ll x=1;x<=10;x++){
		vector<ll> b(n+1,0);
		for(ll i=1;i<=n;i++)
			if(v[i]>x) b[i]=b[i-1]+1;
			else if(v[i]<=x) b[i]=b[i-1]-1;
		map<ll,ll> cnt;
		ll j=0;
		for(ll i=1;i<=n;i++){
			
			if(v[i]==x)
				while(j<i)
					cnt[b[j++]]++;
			ans-=cnt[b[i]];
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
