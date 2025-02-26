#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,x;
	cin>>n>>x;
	
	if(x==0){
		for(ll i=1;i<=n;i++)
			cout<<0<<' ';
		cout<<endl;
		return;
	}
		
	vector<ll> ans(n+1);
	ll g=0,tmp=x;
	while(tmp){
		if(tmp%2) g++;
		else break;
		tmp/=2;
	}
	
	ll p=min(n-1,1ll<<g);
	for(ll i=1;i<=p;i++)
		ans[i]=i-1;
	if(x<=2*ans[p]+1)
		for(ll i=p+1;i<=n;i++)
			ans[i]=min(x,ans[p]+1);
	else
		for(ll i=p+1;i<=n;i++)
			ans[i]=x;
	
//	OOO
	for(ll i=1;i<=n;i++)
		cout<<ans[i]<<' ';
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
