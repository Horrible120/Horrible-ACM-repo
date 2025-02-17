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

const ll INF = 1e18, Mod = 998244353;

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++) cin>>v[i];
	vector<ll> dp0(n+1),dp1(n+1);	//T F
	if(v[1]==0) dp0[1]=1;
	dp1[1]=1;
	
	for(ll i=2;i<=n;i++){
		if(i==2){
			if(v[2]==1) dp0[2]+=dp1[1];
			if(v[2]==0&&v[1]==0) dp0[2]+=1;
			dp1[2]+=dp0[1];
		}
		else{
			dp1[i]=dp0[i-1];
			
			if(v[i]-v[i-2]==1) dp0[i]+=dp1[i-1];
			if(v[i]-v[i-1]==0) dp0[i]+=dp0[i-1];
		}
		dp0[i]%=Mod;
		dp1[i]%=Mod;
	}
//	OOO
//	for(ll i=2;i<=n;i++) cout<<dp0[i]<<'|'<<dp1[i]<<"  ";
//	cout<<endl;
	cout<<(dp1[n]+dp0[n])%Mod<<endl;
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
