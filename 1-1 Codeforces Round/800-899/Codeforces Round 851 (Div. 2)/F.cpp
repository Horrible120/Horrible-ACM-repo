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
	ll n,q,flag=1;
	cin>>n>>q;
//	vector<vector<ll>> edge(n+1);
	
	ll cnt=n;
	
	vector<vector<ll>> edge(n+1);
	vector<pll> eg(n);
	vector<ll> fa(n+1,0),xr(n+1,0),siz(n+1,0),du(n+1,0);
	
	for(ll i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
	}
	
	for(ll i=1;i<n;i++){
		ll x,y;
		cin>>x>>y;
		edge[x].emplace_back(y);
		edge[y].emplace_back(x);
		du[x]++;
		du[y]++;
		eg[i]=make_pair(x,y);
	}
	
	auto get_fa=[&](auto &&self,ll x)->pair<ll,ll>{
		if(fa[x]==x){
			return make_pair(x,xr[x]);
		}
		auto res=self(self,fa[x]);
		res.second^=xr[x];
		return res;
	};
	
	auto merge=[&](ll x,ll y,ll w)->bool{
		auto [fx,xrx]=get_fa(get_fa,x);
		auto [fy,xry]=get_fa(get_fa,y);
		if(fx==fy){
			return (xrx^xry)==w;
		}else{
			if(siz[fx]<siz[fy]){
				swap(fx,fy);
				swap(xrx,xry);
			}
			fa[fy]=fx;
			xr[fy]=w^xrx^xry;
			du[fx]+=du[fy];
			siz[fx]+=siz[fy];
			cnt--;
		}
		return 1;
	};
	
	auto query=[&](ll x,ll y)->ll{
		auto [fx,xrx]=get_fa(get_fa,x);
		auto [fy,xry]=get_fa(get_fa,y);
		if(fx!=fy){
			return 0;
		}else{
			return xrx^xry;
		}
	};
	
	for(ll i=1;i<=q;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		flag&=merge(u,v,w);
	}
	
	
	
	if(!flag){
		cout<<"No"<<endl;
	}else{
		cout<<"Yes"<<endl;
		vector<ll> ans(n+1,0);
		for(ll i=1;i<=n;i++){
			auto [fx,xrx]=get_fa(get_fa,i);
			ans[i]=xrx;
		}
		
		ll tot=0;
		for(ll i=1;i<n;i++){
			auto [x,y]=eg[i];
			tot^=ans[x]^ans[y];
		}
		
		for(ll i=1;i<=n;i++){
			if(du[get_fa(get_fa,i).first]&1){
//				cout<<"    "<<i<<endl;
				ll tmp=get_fa(get_fa,i).first;
				for(ll j=1;j<=n;j++){
					if(get_fa(get_fa,j).first==tmp){
						ans[j]^=tot;
					}
				}
				break;
			}
		}
		
		for(ll i=1;i<n;i++){
			auto [x,y]=eg[i];
			cout<<(ans[x]^ans[y])<<" \n"[i==n-1];
		}
		cout.flush();
	}
	
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
		cout.flush();
	}
	
	cout.flush();
	return 0;
}
