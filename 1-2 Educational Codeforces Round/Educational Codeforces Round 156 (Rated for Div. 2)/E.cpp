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
	vector<ll> v(n+1,0),rnk(n+1,0),g(m+1,0);
	for(ll i=1;i<=n;i++){
		rnk[i]=i;
		cin>>v[i];
	}
	
	for(ll i=0;i<m;i++){
		cin>>g[i];
	}
	
	auto cmd=[&](const ll &aa,const ll &bb)->bool{
		return v[aa]<v[bb];
	};
	
	sort(rnk.begin()+1,rnk.end(),cmd);
	sort(v.begin()+1,v.end());
	
	vector<vector<ll>> nxt(m+1,vector<ll>(n+1,0));
	
	for(ll i=0;i<m;i++){
		for(ll j=n;j>=1;j--){
			if((g[i]+v[j]-1)/v[j]+j-1>n){
				nxt[i][j]=INF;
			}else{
				nxt[i][j]=(g[i]+v[j]-1)/v[j]+j-1;
			}
			if(j<n) nxt[i][j]=min(nxt[i][j],nxt[i][j+1]);
			
		}
		
//		for(ll j=1;j<=n;j++) cout<<nxt[i][j]<<' ';
//		cout<<endl;
	}
	
	vector<ll> dp((1<<m)+1,INF),lst((1<<m)+1,0);
	
	dp[0]=0;
	
	for(ll i=1;i<(1<<m);i++){
		for(ll j=0;j<m;j++) if((i>>j)&1){
			if(dp[i^(1<<j)]<n&&nxt[j][dp[i^(1<<j)]+1]<dp[i]){
				dp[i]=nxt[j][dp[i^(1<<j)]+1];
				lst[i]=j;
			}
		}
	}
	
	if(dp[(1<<m)-1]>n){
		cout<<"NO"<<endl;
	}else{
		cout<<"YES"<<endl;
		vector<ll> ans(m+1);
		ll cur=(1<<m)-1,rd=n,tmp=n+1;
		for(ll i=1;i<=m;i++){
			while((g[lst[cur]]+v[rd]-1)/v[rd]+rd-1>min(dp[cur],tmp-1)) rd--;
			ans[lst[cur]]=rd;
			cur^=(1<<lst[cur]);
			tmp=rd;
		}
		
		for(ll i=0;i<m;i++){
			cout<<nxt[i][ans[i]]-ans[i]+1<<' ';
			for(ll j=ans[i];j<=nxt[i][ans[i]];j++){
				cout<<rnk[j]<<' ';
			}
			cout<<endl;
		}
		
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
