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
	ll n,k;
	cin>>n>>k;
	v2ct<ll> a(n+1,vector<ll>(n+1)),dp(n+1,vector<ll>(k+2,-INF));
	for(ll i=1;i<=n;i++)
		for(ll j=i;j<=n;j++)
			cin>>a[i][j];
	
	dp[0][1]=0;
	for(ll i=1;i<=n;i++){
		vector<ll> cnt(n+1,1);
		multiset<pair<ll,ll>,greater<pair<ll,ll>>> s;
		
		for(ll j=1;j<=k;j++)
			if(dp[i-1][j]!=-INF)
				s.insert(make_pair(dp[i-1][j],0));
			else
				break;
		
		for(ll j=i;j>=1;j--)
			s.insert(make_pair(a[j][i]+dp[max(j-2,0ll)][1],j));
		
		ll cur=1;
		while(s.size()&&cur<=k){
			auto [val,x]=*s.begin();
			dp[i][cur++]=val;
			s.erase(s.begin());
			if(dp[max(x-2,0ll)][cnt[x]+1]!=-INF)
				s.insert(make_pair(a[x][i]+dp[max(x-2,0ll)][++cnt[x]],x));
		}
	}
//	OOO
	for(ll i=1;i<=k;i++)
		cout<<dp[n][i]<<' ';
	cout<<endl;
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
