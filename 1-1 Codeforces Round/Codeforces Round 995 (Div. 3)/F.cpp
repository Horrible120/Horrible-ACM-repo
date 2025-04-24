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
	ll l=0,r=0,ml,mr,q,n;
	cin>>n>>ml>>q;
	
	mr=ml;
	r=n+1;
	
	while(q--){
		ll x;
		cin>>x;
		
		if(ml==mr&&x==ml)
			mr=ml-1;
		
		if(mr>=ml){
			if(ml>0&&x>ml) ml--;
			if(mr<n&&x<mr) mr++;
		}
		
		
		if(l>0){
			if(x>l) l++;
			if(x<r) r--;
		}
		else if(x>=ml&&x<=mr){
			l=1;
			r=n;
		}
		
		ll ans=0;
		if(l>0) ans+=min(l,ml-1);
		if(r<=n) ans+=min(n-r+1,n-mr);
		ans+=mr-ml+1;
		
			
		
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
