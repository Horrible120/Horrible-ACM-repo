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

ll n,k;
vector<vector<ll>> sum;
vector<ll> f,g;

ll cost(ll l,ll r){
	return (sum[r][r]-sum[l][r]-sum[r][l]+sum[l][l])/2;
}

void calc(ll l,ll r,ll optl,ll optr){
	if(l>r)
		return;
	ll mid=(l+r)/2,pos=optl;
	for(ll j=optl;j<=min(optr,mid-1);j++){
		ll val=f[j]+cost(j,mid);
		if(val<=g[mid]){
			g[mid]=val;
			pos=j;
		}
	}

	calc(l,mid-1,optl,pos);
	calc(mid+1,r,pos,optr);
}

void solve(){
	cin>>n>>k;
	sum.assign(n+1,vector<ll>(n+1));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			cin>>sum[i][j];
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	}

	f.assign(n+1,INF);
	g.assign(n+1,INF);
	f[0]=0;
	for(ll t=1;t<=k;t++){
		for(ll i=0;i<=n;i++)
			g[i]=INF;
		calc(t,n,t-1,n-1);
		f.swap(g);
	}
	cout<<f[n]<<'\n';
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
