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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

ll cnt[10000001];

void solve(){
	ll n,ans=0;
	cin>>n;
	vector<ll> s(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>s[i];
		cnt[s[i]]++;
	}
	
	ll m=s[n];
	
	for(ll i=1;i<=m;i++){
		cnt[i]+=cnt[i-1];
//		cout<<cnt[i]<<" \n"[i==m];
	}
	
	ll l=1,r1=0,r2=0;
	while(l<m){
		r1=m/(m/l);
		r2=(m-1)/((m-1)/l);
		
//		cout<<l<<' '<<r1<<' '<<r2<<' '<<m/l<<' '<<ans<<endl;
		
		ll k=m/l;
		
		if(m/l==(m-1)/l+1){
//			OOO
			for(ll j=k;j<=m;j+=k){
				ans=(ans+(cnt[j]-cnt[j-1])*l)%Mod;
			}
			l++;
		}else if(r1<=r2){
			for(ll j=1;j*k<=m&&j<k;j++){
				ans=(ans+(l+r1)*(r1-l+1)/2%Mod*(cnt[min(j*k+j,m)]-cnt[j*k-1]))%Mod;
//				cout<<"    "<<j<<' '<<ans<<endl;
			}
			if(m>=k*k){
				ans=(ans+(l+r1)*(r1-l+1)/2%Mod*(cnt[m]-cnt[k*k-1]))%Mod;
			}
			l=r1+1;
		}else{
			for(ll j=1;j*k<=m&&j<k;j++){
				ans=(ans+(l+r2)*(r2-l+1)/2%Mod*(cnt[min(j*k+j,m)]-cnt[j*k-1]))%Mod;
			}
			if(m>=k*k){
				ans=(ans+(l+r2)*(r2-l+1)/2%Mod*(cnt[m]-cnt[k*k-1]))%Mod;
			}
			l=r2+1;
		}
	}
	
	cout<<(ans+n*m)%Mod<<endl;
	
	for(ll i=1;i<=m;i++){
		cnt[i]=0;
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
