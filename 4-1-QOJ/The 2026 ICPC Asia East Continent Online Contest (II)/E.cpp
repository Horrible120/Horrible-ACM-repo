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

const ll MAXN=100000;
vector<ll> minp,prm;

void sieve(){
	minp.resize(MAXN+1);
	for(ll i=2;i<=MAXN;i++){
		if(!minp[i]){
			minp[i]=i;
			prm.emplace_back(i);
		}
		for(ll j=0;j<(ll)prm.size();j++){
			if(prm[j]>minp[i]||i*prm[j]>MAXN) break;
			minp[i*prm[j]]=prm[j];
		}
	}
}

vector<pair<ll,ll>> factor(ll x){
	vector<pair<ll,ll>> a;
	for(ll i=0;i<(ll)prm.size()&&prm[i]*prm[i]<=x;i++){
		ll p=prm[i],k=0;
		if(x%p) continue;
		while(x%p==0){
			x/=p;
			k++;
		}
		a.emplace_back(p,k);
	}
	if(x>1) a.emplace_back(x,1);
	return a;
}

void solve(){
	ll n;
	cin>>n;
	auto a=factor(n);
	vector<ll> m;
	for(ll i=0;i<(ll)a.size();i++){
		ll p=a[i].first,k=a[i].second;
		if(p==2){
			if(k==2) m.emplace_back(2);
			if(k>=3){
				m.emplace_back(2);
				m.emplace_back(1LL<<(k-2));
			}
		}else{
			ll x=p-1;
			for(ll j=1;j<k;j++) x*=p;
			m.emplace_back(x);
		}
	}
	
	map<ll,vector<ll>> mp;
	for(ll i=0;i<(ll)m.size();i++){
		auto b=factor(m[i]);
		for(ll j=0;j<(ll)b.size();j++){
			mp[b[j].first].emplace_back(b[j].second);
		}
	}
	
	ll ans=1;
	for(auto& [q,v]:mp){
		ll mx=0;
		for(ll i=0;i<(ll)v.size();i++) mx=max(mx,v[i]);
		ll cnt=1,pw=1,sum=1;
		for(ll j=1;j<=mx;j++){
			ll pre=cnt;
			for(ll i=0;i<(ll)v.size();i++){
				if(v[i]>=j) cnt*=q;
			}
			pw*=q;
			sum+=pw*(cnt-pre);
		}
		ans*=sum;
	}
	cout<<ans<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	sieve();
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
