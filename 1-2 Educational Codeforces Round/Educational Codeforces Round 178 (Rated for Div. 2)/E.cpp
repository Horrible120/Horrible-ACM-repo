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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	string s;
	cin>>n>>k;
	cin>>s;
	
	vector<ll> nxt(k+2,0);
	v2ct<ll> snxt(n+1,vector<ll>(k+1,0));
	
	vector<ll> dp(n+2,INF);
	
	for(ll i=n-1;i>=0;i--){
		for(ll j=0;j<k;j++){
			
			snxt[i+1][j]=nxt[j];
			
			if(nxt[j]==0)
				dp[i+1]=1;
			else
				dp[i+1]=min(dp[i+1],dp[nxt[j]]+1);
		}
		
		nxt[s[i]-'a']=i+1;
	}
	
	ll q;
	cin>>q;
	while(q--){
		string t;
		cin>>t;
		ll cur=nxt[t[0]-'a'];
		
		for(ll i=1;i<t.size()&&cur>0;i++)
			cur=snxt[cur][t[i]-'a'];
		
//		OOO
		if(cur==0)
			cout<<0<<endl;
		else
			cout<<dp[cur]<<endl;
	}
	
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
