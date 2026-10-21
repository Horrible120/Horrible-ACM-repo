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

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector<vector<ll>> st(n+1,vector<ll>(21,0));
	
	for(ll i=1;i<=n;i++) st[i][0]=v[i];
	
	for(ll i=1;i<=20;i++){
		for(ll j=1;j<=n;j++){
			st[j][i]=max(st[j][i-1],st[min(j+(1<<i-1),n)][i-1]);
		}
	}
	
	auto qmax=[&](ll l,ll r){
		ll g=__lg(r-l+1);
		return max(st[l][g],st[r-(1<<g)+1][g]);
	};
	
	auto nxt=[&](ll l,ll k){
		ll res=0;
		for(ll i=20;i>=0;i--){
			if(qmax(l,min(n,l+res-1+(1<<i)))<k){
				res=min(n-l+1,res+(1<<i));
			}
		}
		return res;
	};
	
	vector<ll> tmp(32,0);
	tmp[31]=n+1;
	
	ll ans=0;
	
	for(ll i=n;i>=1;i--){
		for(ll g=0;g<=30;g++){
			if((v[i]>>g)&1) tmp[g]=i;
		}
		auto ttmp=tmp;
		sort(ttmp.begin(),ttmp.end());
		ttmp.erase(unique(ttmp.begin(),ttmp.end()),ttmp.end());
		
//		for(auto it:ttmp) cout<<it<<' ';
//		cout<<endl;
		
		ll cur=0;
		
		for(ll it=1;it<(ll)ttmp.size();it++){
			if(it>1) ans+=min(ttmp[it]-ttmp[it-1],nxt(ttmp[it-1],cur));
			
//			cout<<cur<<' '<<nxt(ttmp[it-1],cur)<<endl;
			
			if(ttmp[it]<=n) cur|=v[ttmp[it]];
			
		}
	}
//	OOO
	cout<<ans<<endl;
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
