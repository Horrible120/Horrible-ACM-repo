#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

#pragma GCC optimize(3)

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
	ll n,m;
	cin>>n>>m;
	vector<ll> d(n+1,0),dep(n+1,0),vis(n+1,0);
	
	dep[1]=1;
	
	for(ll i=2;i<=n;i++){
		cin>>d[i];
		dep[i]=dep[d[i]]+1;
	}
	
	vector<ll> siz(n+1,1),fa(n+1,0),top(n+1,0);
	
	fa[0]=1,top[0]=1;
	for(ll i=1;i<=n;i++) top[i]=fa[i]=i;
	
	auto gf=[&](ll x)->ll{
		while(fa[x]^x) fa[x]=fa[fa[x]],x=fa[x];
		return x;
	};
	
	auto merge=[&](ll x,ll y){
		ll fx=gf(x),fy=gf(y);
		if(fx==fy) return;
		if(siz[fx]<siz[fy]) swap(fx,fy);
		siz[fx]+=siz[fy];
		if(dep[top[fy]]<dep[top[fx]]) top[fx]=top[fy];
		fa[fy]=fx;
	};
	
	ll u,v,tu,tv;
	cin>>u>>v;
	tu=u,tv=v;
	
	vector<ll> val(n+1,0);
	
	for(ll i=1;i<=m;i++){
//		cin>>u>>v;
			
		tu=top[gf(u)];
		tv=top[gf(v)];
		while(tu^tv){
//			cout<<tu<<' '<<tv<<endl;
			if(dep[tu]<dep[tv]) swap(tu,tv);
			val[tu]=i;
			merge(tu,d[tu]);
			tu=top[gf(tu)];
		}
		
		tu=(114514LL*u+1919810LL*v)%n+1;
		tv=(415411LL*u+8101919LL*v)%n+1;
		u=tu,v=tv;
	}
	
	ll ans=0;
	for(ll i=2;i<=n;i++){
		ans+=val[i];
	}
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
