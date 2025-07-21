#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll n;
	cin>>n;
	vector<array<ll,2>> v1(n+1),v2(n+1);
	for(ll i=1;i<=n;i++){
		ll x,y;
		cin>>x>>y;
		v1[i][0]=x;
		v2[i][0]=y;
		v1[i][1]=v2[i][1]=i;
	}
	
	sort(v1.begin()+1,v1.end());
	sort(v2.begin()+1,v2.end());
	
	ll lx=1,rx=n,ly=1,ry=n;
	vector<ll> vis(n+1,0);
	
	vector<pair<ll,ll>> ans;
	
	vector<ll> nd[2][2];
	vector<ll> nx(n+1,0),ny(n+1,0);
	
	for(ll i=1;i<=n/2;i++){
		nx[v1[i][1]]=1;
		ny[v2[i][1]]=1;
	}
	
	for(ll i=1;i<=n;i++){
		nd[nx[i]][ny[i]].emplace_back(i);
	}
	
	for(ll i=0;i<nd[0][0].size();i++){
		cout<<nd[0][0][i]<<' '<<nd[1][1][i]<<'\n';
	}
	
	for(ll i=0;i<nd[0][1].size();i++){
		cout<<nd[0][1][i]<<' '<<nd[1][0][i]<<'\n';
	}
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
