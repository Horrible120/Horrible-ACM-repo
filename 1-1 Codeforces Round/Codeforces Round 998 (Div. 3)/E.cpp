#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

ll get_fa(vector<ll> &fa,ll x){
	if(fa[x]==x) return x;
	return fa[x]=get_fa(fa,fa[x]);
}

void solve(){
	ll n,m1,m2,ans=0;
	cin>>n>>m1>>m2;
	
	vector<ll> fa2(n+1),fa1(n+1),u1(m1+1),v1(m1+1),u2(m2+1),v2(m2+1);
	
	for(ll i=1;i<=n;i++) fa1[i]=fa2[i]=i;
	
	for(ll i=1;i<=m1;i++){
		cin>>u1[i]>>v1[i];
	}
	for(ll i=1;i<=m2;i++){
		ll u,v;
		cin>>u>>v;
		u2[i]=u;
		v2[i]=v;
		
		ll fu=get_fa(fa2,u),fv=get_fa(fa2,v);
		if(fu!=fv)
			fa2[fu]=fv;
	}
	for(ll i=1;i<=m1;i++){
		ll u=u1[i],v=v1[i];
		if(get_fa(fa2,u)!=get_fa(fa2,v)){
			ans++;
//			cout<<"1"<<endl;
			continue;
		} 
		ll fu=get_fa(fa1,u),fv=get_fa(fa1,v);
		if(fu!=fv)
			fa1[fu]=fv;
	}
	
//	OOO
//	for(ll i=1;i<=n;i++)
//		cout<<get_fa(fa1,i)<<' ';
//	cout<<endl;
//	OOO
//	for(ll i=1;i<=n;i++)
//		cout<<get_fa(fa2,i)<<' ';
//	cout<<endl;
	
	for(ll i=1;i<=m2;i++){
		ll u=u2[i],v=v2[i];
		if(get_fa(fa1,u)!=get_fa(fa1,v)){
			ans++;
//			cout<<"2"<<endl;
			ll fu=get_fa(fa1,u),fv=get_fa(fa1,v);
			if(fu!=fv)
				fa1[fu]=fv;
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
