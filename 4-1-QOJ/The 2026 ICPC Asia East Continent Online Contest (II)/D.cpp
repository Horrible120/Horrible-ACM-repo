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
	ll n,q;
	cin>>n>>q;
	ll m=1ll<<n;
	vector<ll> l(2*m),r(2*m),b(2*m,m);
	for(ll i=m;i<2*m;i++) l[i]=r[i]=i-m+1;
	for(ll i=m-1;i>=1;i--){
		l[i]=l[2*i];
		r[i]=r[2*i+1];
	}

	vector<ll> L(m+1,1),R(m+1,m),vis(m+1),cnt(m+1),num(m+1);
	ll flag=1;
	while(q--){
		ll u,x;
		cin>>u>>x;
		b[u]=min(b[u],x);
		L[x]=max(L[x],l[u]);
		R[x]=min(R[x],r[u]);
		vis[x]=1;
		if(L[x]>R[x]) flag=0;
	}
	if(!flag){
		cout<<0<<'\n';
		return;
	}

	for(ll i=2;i<2*m;i++) b[i]=min(b[i],b[i/2]);
	for(ll i=1;i<=m;i++){
		ll x=b[m+i-1];
		cnt[x]++;
		if(vis[x]&&L[x]<=i&&i<=R[x]) num[x]++;
	}

	ll ans=1,s=0;
	for(ll x=m;x>=1;x--){
		s+=cnt[x];
		ll k=vis[x]?num[x]:s;
		if(k<=0){
			cout<<0<<'\n';
			return;
		}
		ans=ans*k%Mod;
		s--;
	}
	cout<<ans<<'\n';
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

