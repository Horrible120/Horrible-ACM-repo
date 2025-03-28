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
	ll n;
	cin>>n;
	string sa,sb;
	cin>>sa>>sb;
	vector<ll> a(n+1,0),b(n+1,0),aa(n+1,0),bb(n+1,0),pa(n+1,0);
	
	for(ll i=1;i<=n;i++){
		a[i]=sa[i-1]-'0';
		b[i]=sb[i-1]-'0';
	}
	
	for(ll i=1;i<=n;i++){
		bb[i]=b[i];
		if(i>1&&i<n&&a[i-1]==0&&a[i+1]==0)
			bb[i]=1;
	}
	
	for(ll i=1;i<=n;i++){
		aa[i]=a[i];
		if(i>1&&i<n&&bb[i-1]==1&&bb[i+1]==1)
			aa[i]=1;
		pa[i]=pa[i-1]+aa[i];
	}
	
	ll q;
	cin>>q;
	while(q--){
		ll l,r;
		cin>>l>>r;
//		OOO
		if(r-l==0){
			cout<<a[l]<<endl;
			continue;
		}
		else if(r-l==1){
			cout<<a[l]+a[r]<<endl;
			continue;
		}
		else if(r-l==2){
			cout<<a[l]+a[r]+(a[l+1]||(b[l]&&b[r]))<<endl;
			continue;
		}
		
		ll ans=0;
		ans+=pa[r-2]-pa[l+1]+a[l]+a[r];
		ans+=(a[l+1]||(b[l]&&bb[l+2]));
		ans+=(a[r-1]||(b[r]&&bb[r-2]));
		
		
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
