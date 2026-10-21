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
	ll n;
	cin>>n;
	v2ct<ll> v(n+1,vector<ll>(n+1,0));
	vector<ll> ci(n+1,0),ri(n+1,0);
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			cin>>v[i][j];
	
	for(ll i=1;i<=n;i++)
		cin>>ri[i];
	for(ll i=1;i<=n;i++)
		cin>>ci[i];
	
	vector<array<ll,2>> dpc(n+1,{INF,INF}),dpr(n+1,{INF,INF});
	dpr[0][0]=0;
	dpc[0][0]=0;
	for(ll i=1;i<=n;i++){
		ll flag=1;
		for(ll j=1;j<=n&&flag;j++)
			if(v[j][i]==v[j][i-1])
				flag=0;
		if(flag)
			dpc[i][0]=min(dpc[i][0],dpc[i-1][0]),
			dpc[i][1]=min(dpc[i][1],dpc[i-1][1]+ci[i]);
		
		flag=1;
		for(ll j=1;j<=n&&flag;j++)
			if(v[j][i]+1==v[j][i-1])
				flag=0;
		if(flag)
			dpc[i][1]=min(dpc[i][1],dpc[i-1][0]+ci[i]);
		
		flag=1;
		for(ll j=1;j<=n&&flag;j++)
			if(v[j][i]-1==v[j][i-1])
				flag=0;
		if(flag)
			dpc[i][0]=min(dpc[i][0],dpc[i-1][1]);
		
		flag=1;
		for(ll j=1;j<=n&&flag;j++)
			if(v[i][j]==v[i-1][j])
				flag=0;
		if(flag)
			dpr[i][0]=min(dpr[i][0],dpr[i-1][0]),
			dpr[i][1]=min(dpr[i][1],dpr[i-1][1]+ri[i]);
		
		flag=1;
		for(ll j=1;j<=n&&flag;j++)
			if(v[i][j]+1==v[i-1][j])
				flag=0;
		if(flag)
			dpr[i][1]=min(dpr[i][1],dpr[i-1][0]+ri[i]);
		
		flag=1;
		for(ll j=1;j<=n&&flag;j++)
			if(v[i][j]-1==v[i-1][j])
				flag=0;
		if(flag)
			dpr[i][0]=min(dpr[i][0],dpr[i-1][1]);
	}
	
	ll ans=min(dpr[n][0],dpr[n][1])+min(dpc[n][0],dpc[n][1]);
	
//	OOO
	if(ans<INF)
		cout<<ans<<endl;
	else
		cout<<-1<<endl;
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
