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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(2*n,0);
	for(ll i=1;i<=n*2-1;i++) cin>>v[i];
	
	function<bool(ll)> check=[&](ll x)->bool{
		vector<ll> tmp(2*n,0);
//		cout<<x<<"  :  ";
		for(ll i=1;i<=2*n-1;i++) tmp[i]=(v[i]>=x)/*,cout<<tmp[i]*/;
//		cout<<endl;
		for(ll i=1;i<n;i++){
			if(tmp[n+i]==tmp[n+i-1]) return tmp[n+i];
			if(tmp[n-i]==tmp[n-i+1]) return tmp[n-i];
		}
		return (tmp[n]+n-1)%2;
	};
	
	ll l=1,r=2*n-1;
	while(r>l){
		ll mid=(l+r+1)/2;
		ll flag=check(mid);
//		OOO cout<<mid<<' '<<flag<<endl;
		if(flag) l=mid;
		else r=mid-1;
	}
	cout<<l<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
