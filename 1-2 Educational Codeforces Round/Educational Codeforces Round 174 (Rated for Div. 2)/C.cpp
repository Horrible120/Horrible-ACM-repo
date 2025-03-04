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
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++) cin>>v[i];
	
	vector<ll> cnt1(n+2);
	for(ll i=1;i<=n;i++)
		cnt1[i]=cnt1[i-1]+(v[i]==1?1:0);
	
	ll ans=0,tmp=0;
	for(ll i=1;i<=n;i++){
		if(v[i]==1) tmp+=1;
		if(v[i]==2) tmp*=2;
		if(v[i]==3) ans+=tmp;
		ans%=Mod;
		tmp%=Mod;
	}
	for(ll i=1;i<=n;i++)
		if(v[i]==3)
			ans-=cnt1[i];
//	OOO
	
	cout<<(ans%Mod+Mod)%Mod<<endl;
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
