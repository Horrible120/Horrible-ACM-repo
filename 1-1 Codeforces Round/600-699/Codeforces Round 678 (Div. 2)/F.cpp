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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

vector<ll> minp,prm,mu;
void sieve(ll n){
	minp.assign(n+1,0);
	mu.assign(n+1,0);
	prm.clear();
	if(n>=1)
		mu[1]=1;

	for(ll i=2;i<=n;i++){
		if(!minp[i]){
			minp[i]=i;
			prm.emplace_back(i);
			mu[i]=-1;
		}
		for(ll p:prm){
			if(p>minp[i]||i*p>n)
				break;
			minp[i*p]=p;
			mu[i*p]=(p==minp[i]?0:-mu[i]);
		}
	}
}

void solve(){
	ll m,lim=0;
	cin>>m;
	vector<ll> freq(100001);
	for(ll i=0;i<m;i++){
		ll x,cnt;
		cin>>x>>cnt;
		freq[x]=cnt;
		lim=max(lim,x);
	}
	
	sieve(lim);

	auto qpow=[&](ll x,ll k)->ll{
		ll res=1;
		while(k){
			if(k&1)
				res=res*x%Mod;
			x=x*x%Mod;
			k>>=1;
		}
		return res;
	};
	
	ll inv8=qpow(8,Mod-2),ans=0;
	for(ll d=1;d<=lim;d++){
		if(!mu[d])
			continue;
		
		ll cnt=0,sum=0,sqr=0;
		for(ll j=d;j<=lim;j+=d){
			cnt+=freq[j];
			sum=(sum+freq[j]*j)%Mod;
			sqr=(sqr+freq[j]*j%Mod*j)%Mod;
		}
		
		ll k=cnt%Mod;
		ll val=(k*sum%Mod*sum%Mod+(k-2+Mod)%Mod*sqr)%Mod;
		
		val=val*qpow(2,cnt)%Mod*inv8%Mod;
		ans=(ans+mu[d]*val+Mod)%Mod;
	}
	
	cout<<ans<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

//	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
