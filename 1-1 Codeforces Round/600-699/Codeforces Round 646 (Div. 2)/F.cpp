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
	ll n;
	string s,t;
	cin>>n>>s>>t;
	s=" "+s;
	t=" "+t;

	vector<array<ll,26>> sufs(n+2),suft(n+2);
	for(ll i=n;i>=1;i--){
		sufs[i]=sufs[i+1];
		suft[i]=suft[i+1];
		sufs[i][s[i]-'a']++;
		suft[i][t[i]-'a']++;
	}
	if(sufs[1]!=suft[1]){
		cout<<-1<<'\n';
		return;
	}

	vector<vector<ll>> dp(n+1,vector<ll>(n+1,INF));
	dp[n][n]=0;
	for(ll i=n;i>=0;i--){
		for(ll j=n;j>=0;j--){
			ll cur=dp[i][j];
			if(cur==INF)
				continue;

			if(i&&j&&s[i]==t[j])
				dp[i-1][j-1]=min(dp[i-1][j-1],cur);
			if(i)
				dp[i-1][j]=min(dp[i-1][j],cur+1);
			if(j){
				ll ch=t[j]-'a';
				if(sufs[i+1][ch]>suft[j+1][ch])
					dp[i][j-1]=min(dp[i][j-1],cur);
			}
		}
	}

	cout<<dp[0][0]<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
