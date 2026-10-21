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
	ll n,q;
	cin>>n>>q;
	
	v2ct<ll> v(n+2,vector<ll>(n+2,0)),cpref(n+2,vector<ll>(n+2,0)),pref(n+2,vector<ll>(n+2,0)),wpref(n+2,vector<ll>(n+2,0));
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;i<=n;j++){
			cin>>v[i][j];
			pref[i][j]=pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]+v[i][j];
			wpref[i][j]=wpref[i-1][j]+wpref[i][j-1]-wpref[i-1][j-1]+v[i][j]*(i*n+j-n);
			cpref[i][j]=cpref[i-1][j]+cpref[i][j-1]-cpref[i-1][j-1]+v[i][j]*i;
		}
	}
	
	for(ll i=1;i<=q;i++){
		ll x1,x2,y1,y2;
		cin>>x1>>y1>>x2>>y2;
		
		ll ans=(wpref[x2][y2]-wpref[x2][y1-1]-wpref[x1-1][y2]+wpref[x1-1][y1-1])
				-(x1*n-n+y1-1)*(pref[x2][y2]-pref[x2][y1-1]-pref[x1-1][y2]+pref[x1-1][y1-1])
				-(n-(y2-y1+1))*(cpref[x2][y2]-cpref[x2][y1-1]-cpref[x1-1][y2]+cpref[x1-1][y1-1]
					-x1*(pref[x2][y2]-pref[x2][y1-1]-pref[x1-1][y2]+pref[x1-1][y1-1]));
		
		cout<<ans<<endl;
	}
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
