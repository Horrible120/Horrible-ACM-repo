#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,w;
	cin>>n>>w;
	ll rst=n,ans=n*w;
	vector<ll> p(n+1),cnt(n+1),dep(n+1),r(n+1);
	for(ll i=2;i<=n;i++){
		r[i]=i;
		cin>>p[i];
		dep[i]=dep[p[i]]+1;
		cnt[i]=1+labs(dep[p[i]]-dep[i-1]);
		ll cur=i-1;
		while(cur!=p[i]){
			r[p[cur]]=max(r[cur],i-1);
			cur=p[cur];
		}
	}
	ll cur=n;
	cnt[1]=dep[n];
	while(cur!=1){
		r[p[cur]]=max(r[cur],n);
		cur=p[cur];
	}
//	OOO
//	for(ll i=1;i<=n;i++) cout<<cnt[i]<<' ';
//	cout<<endl;
//	
//	OOO
	for(ll i=2;i<=n;i++){
		ll x,y;
		cin>>x>>y;
		ans-=(rst-2)*y;
		w-=y;
		if(--cnt[x]==0) ans-=w,rst--; 
		if(--cnt[(r[x]%n)+1]==0) ans-=w,rst--; 
		
		cout<<ans<<' ';
	}
	
	cout<<endl;
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
