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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector<ll> pref(n+1,0);
	for(ll i=1;i<=n;i++){
		pref[i]=pref[i-1]+v[i];
	}
	
	vector<ll> tr(n*55+100,-INF),ls(n*55+100,0),rs(n*55+100,0);
	
	ll hi=1e15,lw=-(1e15),tot=0;
	
	
	auto insert=[&](auto &&self,ll &u,ll l,ll r,ll pos,ll key)->void{
		if(!u) u=++tot;
		if(l==r){
			tr[u]=max(tr[u],key);
			return;
		}
		
		ll mid=l+r>>1ll;
		if(pos<=mid){
			self(self,ls[u],l,mid,pos,key);
		}else{
			self(self,rs[u],mid+1,r,pos,key);
		}
		tr[u]=max(tr[ls[u]],tr[rs[u]]);
	};
	
	auto query=[&](auto &&self,ll u,ll l,ll r,ll s,ll t){
		if(!u) return -INF;
		if(l>=s&&r<=t){
			return tr[u];
		}
		
		ll mid=l+r>>1ll;
		ll res=-INF;
		if(mid>=s){
			res=max(res,self(self,ls[u],l,mid,s,t));
		}
		if(mid<t){
			res=max(res,self(self,rs[u],mid+1,r,s,t));
		}
		return res;
	};
	
	ll root=0;
	vector<ll> dp(n+1,0);
	
	insert(insert,root,lw,hi,0,0);
	
	for(ll i=1;i<=n;i++){
		dp[i]=max(dp[i-1],query(query,root,lw,hi,lw,pref[i])+i);
		insert(insert,root,lw,hi,pref[i],dp[i]-i);
	}
	cout<<dp[n]<<endl;
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
