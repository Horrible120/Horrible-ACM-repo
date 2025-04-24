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
	ll n,k,ans=0;
	cin>>n>>k;
	vector<ll> v(n+1,0),emp(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		emp[i]=(v[i]==0);
		v[i]+=v[i-1];
		emp[i]+=emp[i-1];
	}
	
	ll s=-v[n];
	
	if(s<emp[n]*-k||s>emp[n]*k){
		cout<<-1<<endl;
		return;
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=i;j<=n;j++){
			ll a1=emp[i-1]+emp[n]-emp[j];
			ll b1=emp[j]-emp[i-1];
			if(k*a1-s<=k*b1)
				ans=max(ans,abs(k*a1+v[i-1]+v[n]-v[j]));
			else
				ans=max(ans,abs(v[j]-v[i-1]-k*b1));
		}
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=i;j<=n;j++){
			ll a1=emp[i-1]+emp[n]-emp[j];
			ll b1=emp[j]-emp[i-1];
			if(-k*a1-s>=-k*b1)
				ans=max(ans,abs(-k*a1+v[i-1]+v[n]-v[j]));
			else
				ans=max(ans,abs(v[j]-v[i-1]+k*b1));
		}
	}
	
//	OOO
	cout<<ans+1<<endl;
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
