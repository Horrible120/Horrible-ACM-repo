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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;
ll fct[2000010],iv[2000010];

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}
void init(){
	fct[0]=1;
	for(ll i=1;i<=2e6;i++)
		fct[i]=fct[i-1]*i%Mod;
	for(ll i=1;i<=2e6;i++)
		iv[i]=inv(fct[i]);
}

ll Calc(ll n,ll m){
//	cout<<n<<' '<<m<<endl;
	return fct[m+n-1]*(iv[m]*iv[n-1]%Mod)%Mod;
}

void solve(){
	vector<ll> c(5,0);
	for(ll i=1;i<=4;i++)
		cin>>c[i];
	OOO
	cout<<Calc(2,2)<<endl;
	if(abs(c[1]-c[2])>1){
		cout<<0<<endl;
	}
	else if(c[1]!=c[2]){
		cout<<Calc(min(c[1],c[2]),c[3])*Calc(min(c[1],c[2]),c[4])%Mod<<endl;
	}
	else{
		cout<<(Calc(c[1],c[3])*Calc(c[1]-1,c[4])+Calc(c[1]-1,c[3])*Calc(c[1],c[4]))%Mod<<endl;
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();
	cout<<fct[5]<<' '<<iv[3]<<endl;
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
