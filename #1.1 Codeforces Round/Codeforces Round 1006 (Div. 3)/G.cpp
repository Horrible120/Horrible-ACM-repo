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
ll pw[601][21];

ll sol1(ll n,ll p){
	ll res=0;
	vector<ll> tmp;
	ll g=0;
	while(n){
		tmp.emplace_back(n%p);
		n/=p;
		g++;
	}
	for(auto it:tmp)
		res=(res+it*pw[p][--g])%Mod;
	return res;
}



void solve(){
	ll n,k,ans=0;
	cin>>n>>k;
	ll q=min(k,(ll)sqrt(n));
	for(ll i=2;i<=q;i++)
		ans=(ans+sol1(n,i))%Mod;
	
	if(k>n)
		ans=(ans+n*((k-n)%Mod))%Mod;
	
	ll yy=min(k,n);
		
	auto qq=[&](ll a1,ll a2,ll b1,ll b2){
		if(a2==a1) return b1*a1;
		ll d=(b2-b1)/(a2-a1),ct=a2-a1+1;
		ll res=0;
		res=(((ct*a1%Mod*b1)%Mod   +(a1*d+b1)%Mod*(ct*(ct-1)/2%Mod)%Mod   +d*(ct*(ct-1)*(2*ct-1)/6%Mod))%Mod+Mod)%Mod;
		return res;
	};
	
	ll l=q+1,r=0;
	while(l<=yy){
		ll p=n/l;
		r=min(yy,n/p);
		ans=(ans+
			p*(r-l+1)+
			qq(l,r,n%l,n%r))
			%Mod;
		l=r+1;
	}
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	for(ll i=1;i<=600;i++) pw[i][0]=1;
	for(ll i=1;i<=600;i++)
		for(ll j=1;j<=20;j++)
			pw[i][j]=pw[i][j-1]*i%Mod;
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
