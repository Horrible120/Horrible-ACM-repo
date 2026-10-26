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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> col(1);
	for(ll i=1;i<=m;i++){
		ll x;
		cin>>x;
		if(x!=col[col.size()-1])
			col.emplace_back(x);
	}
	ll s=col.size()-1;
	if(s>2*n-1){
		cout<<0<<'\n';
		return;
	}

	vector<vector<ll>> pos(n+1);
	for(ll i=1;i<=s;i++)
		pos[col[i]].emplace_back(i);
	vector<ll> fir(n+1),las(n+1);
	for(ll i=1;i<=n;i++){
		fir[i]=pos[i][0];
		las[i]=pos[i][pos[i].size()-1];
	}

	vector<vector<ll>> dp(s+2,vector<ll>(s+2));
	for(ll i=1;i<=s+1;i++)
		dp[i][i-1]=1;

	for(ll l=s;l>=1;l--){
		ll x=col[l];
		for(ll r=l;r<=s;r++){
			x=min(x,col[r]);
			if(fir[x]<l || las[x]>r)
				continue;

			ll p=fir[x],q=las[x];
			ll le=0,ri=0,mid=1;
			for(ll i=l;i<=p;i++)
				le=(le+dp[l][i-1]*dp[i][p-1])%Mod;
			for(ll i=q;i<=r;i++)
				ri=(ri+dp[q+1][i]*dp[i+1][r])%Mod;
			for(ll j=1;j<(ll)pos[x].size();j++)
				mid=mid*dp[pos[x][j-1]+1][pos[x][j]-1]%Mod;

			dp[l][r]=le*ri%Mod*mid%Mod;
		}
	}

	cout<<dp[1][s]<<'\n';
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
