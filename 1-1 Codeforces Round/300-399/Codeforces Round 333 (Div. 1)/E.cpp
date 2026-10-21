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
	ll n,k;
	cin>>n>>k;
	vector<ll> v(n+30001,0),w(n+30001,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i]>>w[i];
	}
	
	ll q;
	cin>>q;
	
	vector<ll> ask(q+1,0);
	
	ll evt=n;
	vector<vector<ll>> node(4*q+1,vector<ll>());
	
	map<ll,ll> lst;
	
	for(ll i=1;i<=n;i++){
		lst[i]=1;
	}
	
	auto modify=[&](auto &&self,ll u,ll l,ll r,ll s,ll t,ll key)->void{
		if(l>=s&&r<=t){
			node[u].emplace_back(key);
			return;
		}
		
		ll mid=l+r>>1;
		
		if(mid>=s){
			self(self,u*2,l,mid,s,t,key);
		}
		if(mid<t){
			self(self,u*2+1,mid+1,r,s,t,key);
		}
	};
	
	for(ll i=1;i<=q;i++){
		ll op;
		cin>>op;
		if(op==3){
			ask[i]=1;
		}else if(op==2){
			ll x;
			cin>>x;
			modify(modify,1,1,q,lst[x],i,x);
			lst[x]=0;
		}else{
			++evt;
			cin>>v[evt]>>w[evt];
			lst[evt]=i;
		}
	}
	
	for(auto [x,ti]:lst){
		if(ti){
			modify(modify,1,1,q,ti,q,x);
		}
	}
	
	vector<vector<ll>> dp(21,vector<ll>(k+1,0));
	
	ll p=1e7+19;
	
	auto DFS=[&](auto &&self,ll u,ll l,ll r,ll dep)->void{
		dp[dep]=dp[dep-1];
		for(auto it:node[u]){
			for(ll i=k;i>=1;i--){
				if(i>=w[it]){
					dp[dep][i]=max(dp[dep][i],dp[dep][i-w[it]]+v[it]);
				}
			}
		}
		
		if(l==r){
			if(ask[l]){
				ll ans=0,pp=1;
				for(ll i=1;i<=k;i++){
					ans=(ans+dp[dep][i]*pp)%Mod;
					pp=pp*p%Mod;
				}
//				OOO
				cout<<ans<<endl;
			}
			return;
		}
		
		ll mid=l+r>>1;
		self(self,u*2,l,mid,dep+1);
		self(self,u*2+1,mid+1,r,dep+1);
	};
	
	DFS(DFS,1,1,q,1);
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
