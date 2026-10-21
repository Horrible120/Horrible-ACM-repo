#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

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
	ll l,r,n;
	cin>>l>>r>>n;

	vector<ll> p;
	ll tmp=n;
	for(ll i=2;i*i<=tmp;i++){
		if(tmp%i) continue;
		p.push_back(i);
		while(tmp%i==0) tmp/=i;
	}
	if(tmp>1) p.push_back(tmp);

	auto calc=[&](ll x)->ll{
		ll res=x;
		for(ll s=1;s<(1<<p.size());s++){
			ll mul=1;
			ll cnt=0;
			for(ll i=0;i<p.size();i++){
				if(s>>i&1) mul*=p[i],cnt++;
			}
			if(cnt&1) res-=x/mul;
			else res+=x/mul;
		}
		return res;
	};

	const ll B=4096;
	ll L=max(1ll,n-B);
	vector<ll> dp(n-L+1);

	for(ll i=n-1;i>=L;i--){
		dp[i-L]=gcd(i,n);
		if(dp[i-L]<=2) continue;
		for(ll j=i+1;j<n;j++){
			dp[i-L]=min(dp[i-L],gcd(i,j-i)+dp[j-L]);
			if(dp[i-L]==2) break;
		}
	}

	ll ans=0;
	ll R=min(r,L-1);
	if(l<=R){
		ans=2ll*(R-l+1)-(calc(R)-calc(l-1));
	}
	for(ll i=max(l,L);i<=r;i++) ans+=dp[i-L];
	cout<<ans<<'\n';
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
