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

ll ask(ll x,ll y,ll val){
	cout<<"? "<<x<<' '<<y<<' '<<val<<endl;
	ll res;
	cin>>res;
	return res;
}

void ans(ll x){
	cout<<"! "<<x<<endl;
}

void solve(){
	ll n,k;
	cin>>n>>k;
	
	ll l=1,r=n*n;
	while(l<r){
		ll mid=l+r>>1;
		
		ll dl=1,cnt=0;
		
		for(ll i=n;i>=1;i--){
			while(dl<=n&&ask(i,dl,mid))
				dl++;
			cnt+=dl-1;
		}
		
		if(cnt>=n*n-k+1)
			r=mid;
		else
			l=mid+1;
	}
	
	ans(l);
	
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
