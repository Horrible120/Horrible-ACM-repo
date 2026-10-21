#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

ll fact[10001],iv[10001];

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
	ll n=10000;
	fact[0]=1;
	for(ll i=1;i<=n;i++){
		fact[i]=fact[i-1]*i%Mod;
	}
	
	iv[n]=inv(fact[n]);
	for(ll i=n-1;i>=0;i--){
		iv[i]=iv[i+1]*(i+1)%Mod;
	}
}

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector<ll> cnt(n+1,0),lstk(n+1,0);
	
	vector<vector<ll>> str(n+1,vector<ll>(1,1));
	
	for(ll i=1;i<=n;i++){
		cnt[v[i]]++;
		str[v[i]].emplace_back(i);
		if(cnt[v[i]]>=k){
			lstk[i]=str[v[i]][cnt[v[i]]-k+1];
		}
	}
	
	vector<ll> f(n+1,0),g(n+1,0);
	ll len=0,ans=0;
	
	for(ll i=1;i<=n;i++){
		ll ct=1;
		for(ll j=i-1;j>=0;j--){
			if(ct>=k) f[i]=max(f[i],f[j]+1);
			if(v[j]==v[i]) ++ct;
		}
		len=max(len,f[i]);
	}
	
//	cout<<"Len : "<<len<<endl;
	
	auto calc=[&](ll a,ll b){
		return fact[a]*iv[a-b]%Mod*iv[b]%Mod;
	};
	
	g[0]=1;
	
	for(ll i=1;i<=n;i++){
		ll ct=1;
		for(ll j=i-1;j>=0;j--){
			if(ct>=k&&f[j]+1==f[i]) g[i]=(g[i]+g[j]*calc(ct-1,k-1)%Mod)%Mod;
			if(v[j]==v[i]) ++ct;
		}
		if(f[i]==len) ans=(ans+g[i])%Mod;
	}
	
	cout<<(len==0LL?1LL:ans)<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
