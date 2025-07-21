#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll s,p;
	cin>>p>>s;
	
	for(ll i=1;i<=50;i++){
		ll tmp=(i+1)*2;
		if(tmp*s==i*p){
			cout<<i<<endl;
			for(ll j=1;j<=i;j++)
				cout<<1<<' '<<j<<endl;
			return;
		}
	}
	
	ll g=__gcd(s,p);
	s/=g;
	p/=g;
	
	if(s>=(p+1)/2-1){
		p*=16*s;
		s*=16*s;
		cout<<s<<endl;
		
		ll n=p/4;
		
		for(ll i=1;i<=n;i++)
			cout<<1<<' '<<i<<endl;
		for(ll i=2;i<=n;i++)
			cout<<i<<' '<<1<<endl;
		
		s-=n*2-1;
		
		for(ll i=2;i<=n&&s>0;i++){
			for(ll j=2;j<=n&&s>0;j++){
				cout<<j<<' '<<i<<endl;
				s--;
			}
		}
	}
	else{
		cout<<-1<<endl;
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
