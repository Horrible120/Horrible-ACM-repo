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
	vector<ll> k(n+1,0),dp(n+1,0),last(n+1,0);
	
	vector<vector<ll>> s(n+1);
	
	map<ll,ll> lst;
	
	for(ll i=1;i<=n;i++){
		cin>>k[i];
		for(ll j=1;j<=k[i];j++){
			ll x;
			cin>>x;
			s[i].emplace_back(x);
			last[i]=max(last[i],lst[x]);
			lst[x]=i;
		}
//		if(last[i]==0) last[i]=n+1; 
		
	}
	
	vector<ll> pre(n+1,0);
	for(ll i=1;i<=n;i++){
		pre[i]=pre[i-1]+(k[i]==0);
//		cout<<pre[i]<<' ';
	}
	
//	cout<<endl;
	
	ll ld=0;
	dp[0]=1;
	
	for(ll i=1;i<=n;i++){
		if(k[i]==0){
			dp[i]=1;
		}else{
			if(ld<last[i]){
				dp[i]=1;
				ld=last[i];
				while(!dp[ld]) ++ld;
			}else if(pre[i]-pre[ld]>0){
				dp[i]=1;
				while(!dp[ld]) ++ld;
			}
		}
		
//		cout<<">>> "<<i<<' '<<dp[i]<<' '<<ld<<endl;
	}
	
	ll ans=0,cnt=0;
	set<ll> st;
	for(ll i=n;i>=1;i--){
		cnt+=k[i];
		for(auto it:s[i]){
			st.insert(it);
		}
		if(st.size()==cnt){
//			cout<<"!! "<<i<<endl;
			if(dp[i-1]==1){
				if(pre[n]-pre[i-1]>0){
					ans=m;
				}else{
					ans=max(ans,cnt);
				}
			}
		}else{
			break;
		}
	}
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
