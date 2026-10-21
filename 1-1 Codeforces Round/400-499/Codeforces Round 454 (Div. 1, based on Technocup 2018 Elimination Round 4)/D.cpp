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

vector<ll> val,ph;

ll phi(ll n){
	ll ans=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0)
				n/=i;
		}
	}
	if(n>1)
		ans=ans/n*(n-1);
	return ans;
}

ll qpow(ll a,ll b,ll mod){
	ll ans=1%mod;
	a%=mod;
	while(b){
		if(b&1)
			ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

bool big(ll l,ll r,ll lim){
	if(lim<=1)
		return true;
	if(l==r)
		return val[l]>=lim;
	if(val[l]==1)
		return false;

	ll cur=1,cnt=0;
	while(cur<lim){
		cur*=val[l];
		cnt++;
	}
	return big(l+1,r,cnt);
}

ll calc(ll l,ll r,ll dep){
	ll mod=ph[dep];
	if(mod==1)
		return 0;
	if(l==r)
		return val[l]%mod;

	ll nxt=ph[dep+1];
	ll exp=calc(l+1,r,dep+1);
	if(big(l+1,r,nxt))
		exp+=nxt;
	return qpow(val[l],exp,mod);
}

void solve(){
	ll n,m;
	cin>>n>>m;
	val.assign(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>val[i];

	ph.clear();
	ph.emplace_back(m);
	while(ph[ph.size()-1]!=1)
		ph.emplace_back(phi(ph[ph.size()-1]));

	ll q;
	cin>>q;
	while(q--){
		ll l,r;
		cin>>l>>r;
		cout<<calc(l,r,0)<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
