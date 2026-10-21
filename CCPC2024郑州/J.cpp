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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+1,0),b(m+1,0);
	
	ll tot=1;
	vector<ll> ls(32*m+10,0),rs(32*m+10,0),cnt(32*m+20,0);
	
	auto add_val=[&](ll x){
		ll u=1;
		cnt[1]++;
		for(ll i=0;i<=31;i++){
			if((x>>i)&1){
				if(!rs[u]) rs[u]=++tot;
				u=rs[u];
			}else{
				if(!ls[u]) ls[u]=++tot;
				u=ls[u];
			}
			++cnt[u];
		}
	};
	
//	auto del_val=[&](ll x){
//		ll u=1;
//		cnt[1]--;
//		for(ll i=0;i<=31;i++){
//			if((x>>i)&1){
////				if(!rs[u]) rs[u]=++tot;
//				u=rs[u];
//			}else{
////				if(!ls[u]) ls[u]=++tot;
//				u=ls[u];
//			}
//			--cnt[u];
//		}
//	};
	
	auto calc=[&](ll x,ll len)->ll{
		ll u=1;
		for(ll i=0;i<len;i++){
			if((x>>i)&1){
				if(!rs[u]) return 0;
				u=rs[u];
			}else{
				if(!ls[u]) return 0;
				u=ls[u];
			}
		}
		return cnt[u];
	};
	
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	
	for(ll i=1;i<=m;i++){
		cin>>b[i];
	}
	
	vector<ll> l1(m+1,0),l2(n+1,0);
	
	for(ll i=1;i<m;i++){
		ll tmp=b[i]^b[i+1];
		if(!(tmp&tmp+1)){
			l1[i]=__builtin_popcount(tmp);
		}
	}
	
	for(ll i=1;i<n;i++){
		ll tmp=(a[i]^a[i+1])>>1;
		if((a[i]&1)==(a[i+1]&1)&&!(tmp&tmp+1)){
			l2[i]=__builtin_popcount(tmp);
		}
	}
	
//	for(ll i=1;i<n;i++) cout<<"L2 "<<i<<' '<<l2[i]<<endl;
//	for(ll i=1;i<m;i++) cout<<"L1 "<<i<<' '<<l1[i]<<endl;
	
	vector<vector<ll>> stk(32),stk2(32);
	
	for(ll i=1;i<m;i++){
		stk[l1[i]].emplace_back(b[i]);
	}
	
	for(ll i=1;i<n;i++){
		stk2[l2[i]].emplace_back(a[i]);
	}
	
	ll ans=0;
	
	for(auto it:stk[1]){
		add_val(it);
	}
	
//	OOO
//	cout<<calc(1,0)<<endl;
	
	for(ll i=1;i<n;i++){
		if(l2[i]){
			ans+=calc(a[i]^(((1<<l2[i]-1)-1)<<1),l2[i]+1);
		}
	}
	
//	OOO
//	cout<<"1 "<<ans<<endl;
	
//	for(auto it:stk[1]){
//		del_val(it);
//	}
//	
//	
//	for(ll i=1;i<=30;i++){
//		for(auto it:stk[i+1]){
//			add_val(it);
//		}
//		
//		for(auto it:stk2[i]){
//			ans+=calc(it^((1<<i)-1),i+1);
//		}
//		
//		for(auto it:stk[i+1]){
//			del_val(it);
//		}
//		OOO
//		cout<<i<<' '<<ans<<endl;
//	}
	
//	OOO
	cout<<ans<<endl;
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
