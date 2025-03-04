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
	ll n,q,cnt=0;
	cin>>n>>q;
	vector<vector<ll>> fa(n+1,vector<ll>(30)),son(n+1);
	vector<ll> p(n+1),bk(n+1),dep(n+1);
	fa[1][0]=1;
	for(ll i=2;i<=n;i++) cin>>fa[i][0],son[fa[i][0]].emplace_back(i);
	dep[1]=1;
	for(ll i=1;i<=n;i++)
		for(auto it:son[i])
			dep[it]=dep[i]+1;
	
	for(ll i=1;i<=20;i++)
		for(ll j=1;j<=n;j++)
			fa[j][i]=fa[fa[j][i-1]][i-1];
	for(ll i=1;i<=n;i++) cin>>p[i];
	
	function<bool(ll,ll)> check=[&](ll u,ll v){
		if(u==fa[v][0]) return 0;
		for(ll i=20;i>=0;i--)
			if(dep[fa[u][i]]>dep[fa[v][0]])
				u=fa[u][i];
//		cout<<"!!!"<<u<<' '<<v<<endl;
		if(fa[u][0]==fa[v][0]) return 0;
		else return 1;
	};
	
//	cout<<"###"<<endl;
//	for(ll i=0;i<=2;i++){
//		for(ll j=1;j<=n;j++)
//			cout<<fa[j][i]<<' ';
//		cout<<endl;
//	}
		
	
	
	for(ll i=1;i<=n-1;i++){
		bk[i]=check(p[i],p[i+1]);
		cnt+=bk[i];
//		cout<<"! ["<<i<<','<<bk[i]<<']'<<endl;
	}
//	OOO
//	for(ll i=1;i<n;i++) cout<<bk[i]<<' ';
//	cout<<"||"<<cnt<<endl;
	ll x,y;
	for(ll i=1;i<=q;i++){
		cin>>x>>y;
		if(x>y) swap(x,y);
		cnt-=bk[x-1]+bk[x]+bk[y-1]+bk[y];
		if(x==y-1) cnt+=bk[x];
		swap(p[x],p[y]);
		if(x!=1) bk[x-1]=check(p[x-1],p[x]);
		bk[x]=check(p[x],p[x+1]);
		bk[y-1]=check(p[y-1],p[y]);
		if(y!=n) bk[y]=check(p[y],p[y+1]);
		cnt+=bk[x-1]+bk[x]+bk[y-1]+bk[y];
		if(x==y-1) cnt-=bk[x];
		
//		OOO
//		for(ll i=1;i<n;i++) cout<<bk[i]<<' ';
//		cout<<"||"<<cnt<<endl;
		if(cnt||p[1]!=1) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
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
