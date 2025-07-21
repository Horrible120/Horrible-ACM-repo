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
	vector<ll> a(n+1,0),b(n+1,0),prea(n+1,0),ans(n+2,0),difans(n+2,0);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
		prea[i]=prea[i-1]+b[i];
	}
	for(ll i=n;i>=1;i--){
		if(a[i]<=b[i]){
			ans[i]+=a[i];
			continue;
		}else{
			ll l=i,r=n;
			while(l<r){
				ll mid=l+r+1>>1;
				if(prea[mid]-prea[i-1]<a[i]){
					l=mid;
				}else{
					r=mid-1;
				}
			}
			difans[i]++;
			difans[l+1]--;
			ans[l+1]+=a[i]-(prea[l]-prea[i-1]);
//			cout<<i<<" "<<l<<endl;
		}
	}
	for(ll i=1;i<=n;i++){
		difans[i]+=difans[i-1];
		
//		cout<<i<<' '<<ans[i]<<' '<<difans[i]<<endl;
		ans[i]+=difans[i]*b[i];
		cout<<ans[i]<<" \n"[i==n];
	}
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
