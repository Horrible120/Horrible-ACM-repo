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
	ll n,m;
	cin>>n>>m;
	v2ct<ll> v(n+1,vector<ll>(n+1)),ans(n+1,vector<ll>(n+1));
	for(ll i=0;i<n;i++)
		for(ll j=0;j<n;j++)
			cin>>v[i][j],v[i][j]--;
	vector cg(4,array<ll,3>());
	cg[1][1]=1;
	cg[2][1]=2;
	cg[3][1]=3;
	
	string op;
	cin>>op;
	for(ll i=0;i<m;i++){
		if(op[i]=='L') cg[2][2]--;
		else if(op[i]=='R') cg[2][2]++;
		else if(op[i]=='U') cg[1][2]--;
		else if(op[i]=='D') cg[1][2]++;
		else if(op[i]=='I') swap(cg[2],cg[3]);
		else if(op[i]=='C') swap(cg[1],cg[3]);
	}
	for(ll i=0;i<n;i++)
		for(ll j=0;j<n;j++){
			array<ll,4> tmp={0,i,j,v[i][j]};
			ll a=(tmp[cg[1][1]]+cg[1][2]%n+n)%n;
			ll b=(tmp[cg[2][1]]+cg[2][2]%n+n)%n;
			ll c=(tmp[cg[3][1]]+cg[3][2]%n+n)%n;
			ans[a][b]=c;
		}
	for(ll i=0;i<n;i++)
		for(ll j=0;j<n;j++)
			cout<<ans[i][j]+1<<" \n"[j==n-1];
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
