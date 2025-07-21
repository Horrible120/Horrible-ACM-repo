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
	vector<ll> u(n+1),d(n+1);
	ll l=0,r=INF;
	for(ll i=1;i<=n;i++){
		cin>>u[i]>>d[i];
		r=min(r,u[i]+d[i]);
	}
	
	vector<ll> rgr(n+1),rgl(n+1);
	
	auto check=[&](ll tar){
		ll mx=0,mn=INF;
		for(ll i=1;i<=n;i++){
			rgl[i]=max(tar-d[i],0ll);
			rgr[i]=min(tar,u[i]);
			if(i==1) continue;
			if(rgr[i]+x<rgl[i-1]||rgl[i]-x>rgr[i-1])
				return 0;
			rgr[i]=min(rgr[i],rgr[i-1]+x);
			rgl[i]=max(rgl[i],rgl[i-1]-x);
		}
//		if(max(mx-mn,0ll)<=x) return 1;
		return 1;
	};
	
	
	
	while(l<r){
		ll mid=(l+r+1)/2;
		ll flag=check(mid);
		if(flag) l=mid;
		else r=mid-1;
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ans+=u[i]+d[i]-l;
	}
	cout<<ans<<endl;
	
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
