#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m,k,mx=0;
	cin>>n>>m>>k;
	v2ct<ll> v(n+1,vector<ll>(m+1,0));
	for(ll i=1;i<=n;i++){
		string s;
		cin>>s;
		for(ll j=1;j<=m;j++)
			v[i][j]=s[j-1]=='#'?1:0;
	}
	
	v2ct<ll> a=v;
	v2ct<ll> pre(n+1,vector<ll>(m+1,0)),pres(n+1,vector<ll>(m+1,0));
	auto row=[&](ll i,ll j){
		return pre[i][min(m,j)];
	};
	auto prs=[&](ll i,ll j)->ll{
		if(i>=0&&i<=n&&j<=m)
			return pres[i][j];
		else if(i>n&&j+(i-n)<=m)
			return pres[n][j+(i-n)];
		else
			return 0ll;
	};
	
	{
		pre=v2ct<ll>(n+1,vector<ll>(m+1,0));
		pres=v2ct<ll>(n+1,vector<ll>(m+1,0));
		v2ct<ll> ans(n+1,vector<ll>(m+1,0));
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pre[i][j]=pre[i][j-1]+a[i][j];
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pres[i][j]=pres[i-1][j+1]+a[i][j];
		for(ll i=1;i<=m;i++)
			for(ll j=1;j<=min(n,k+1);j++)
				ans[1][i]+=row(j,i+k-j+1)-row(j,i-1);
		for(ll i=1;i<=m;i++)
			for(ll j=2;j<=n;j++)
				ans[j][i]=ans[j-1][i]-(row(j-1,i+k)-row(j-1,i-1))+prs(j+k,i)-prs(j-1,i+k+1);
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				mx=max(mx,ans[i][j]);
	}
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			a[i][j]=v[i][m-j+1];
	{
		pre=v2ct<ll>(n+1,vector<ll>(m+1,0));
		pres=v2ct<ll>(n+1,vector<ll>(m+1,0));
		v2ct<ll> ans(n+1,vector<ll>(m+1,0));
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pre[i][j]=pre[i][j-1]+a[i][j];
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pres[i][j]=pres[i-1][j+1]+a[i][j];
		for(ll i=1;i<=m;i++)
			for(ll j=1;j<=min(n,k+1);j++)
				ans[1][i]+=row(j,i+k-j+1)-row(j,i-1);
		for(ll i=1;i<=m;i++)
			for(ll j=2;j<=n;j++)
				ans[j][i]=ans[j-1][i]-(row(j-1,i+k)-row(j-1,i-1))+prs(j+k,i)-prs(j-1,i+k+1);
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				mx=max(mx,ans[i][j]);
	}
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			a[i][j]=v[n-i+1][j];
	{
		pre=v2ct<ll>(n+1,vector<ll>(m+1,0));
		pres=v2ct<ll>(n+1,vector<ll>(m+1,0));
		v2ct<ll> ans(n+1,vector<ll>(m+1,0));
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pre[i][j]=pre[i][j-1]+a[i][j];
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pres[i][j]=pres[i-1][j+1]+a[i][j];
		for(ll i=1;i<=m;i++)
			for(ll j=1;j<=min(n,k+1);j++)
				ans[1][i]+=row(j,i+k-j+1)-row(j,i-1);
		for(ll i=1;i<=m;i++)
			for(ll j=2;j<=n;j++)
				ans[j][i]=ans[j-1][i]-(row(j-1,i+k)-row(j-1,i-1))+prs(j+k,i)-prs(j-1,i+k+1);
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				mx=max(mx,ans[i][j]);
	}
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			a[i][j]=v[n-i+1][m-j+1];
	{
		pre=v2ct<ll>(n+1,vector<ll>(m+1,0));
		pres=v2ct<ll>(n+1,vector<ll>(m+1,0));
		v2ct<ll> ans(n+1,vector<ll>(m+1,0));
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pre[i][j]=pre[i][j-1]+a[i][j];
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				pres[i][j]=pres[i-1][j+1]+a[i][j];
		for(ll i=1;i<=m;i++)
			for(ll j=1;j<=min(n,k+1);j++)
				ans[1][i]+=row(j,i+k-j+1)-row(j,i-1);
		for(ll i=1;i<=m;i++)
			for(ll j=2;j<=n;j++)
				ans[j][i]=ans[j-1][i]-(row(j-1,i+k)-row(j-1,i-1))+prs(j+k,i)-prs(j-1,i+k+1);
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				mx=max(mx,ans[i][j]);
	}
	
	cout<<mx<<endl;
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
