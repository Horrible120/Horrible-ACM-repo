#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

struct Cow{
	ll mx,mn=INF,num;
	bool operator<(const Cow &aa){
		return mn<aa.mn;
	}
};

void solve(){
	ll n,m,flag=1;
	cin>>n>>m;
	v2ct<ll> v(n+1,vector<ll>(m+1));
	vector<ll> cd(n*m+10);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++){
			cin>>v[i][j];
			cd[v[i][j]]=i;
			if(j>1&&v[i][j]%n!=v[i][j-1]%n) flag=0;
		}
	if(flag)
		for(ll i=0;i<n;i++) cout<<cd[i]<<" \n"[i==n-1];
	else cout<<-1<<endl;
	cout.flush();
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
