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
const ull mask=rnd();

ull f(ull x){
	x^=mask;
	x^=x<<13;
	x^=x>>7;
	x^=x<<17;
	x^=mask;
	return x;
}


void solve(){
	ll m,cnt=0;
	cin>>m;
	
	map<ull,ll> rnk;
	vector<ll> ans(m+1,0);
	
	for(ll i=1;i<=m;i++){
		ans[i]=i;
	}
	
	while(m--){
		++cnt;
		ll n,rt;
		cin>>n;
		vector<vector<ll>> eg(n+1);
		vector<ull> hs1(n+1,0),fa(n+1,0),hs2(n+1,0);
		for(ll i=1;i<=n;i++){
			ll v;
			cin>>v;
			if(v){
				fa[i]=v;
				eg[v].emplace_back(i);
			}else{
				rt=i;
			}
		}
		
		auto DFS1=[&](auto &&self,ll u)->void{
			hs1[u]=1;
			for(auto v:eg[u]){
				self(self,v);
				hs1[u]+=f(hs1[v]);
			}
		};
		
		auto DFS2=[&](auto &&self,ll u)->void{
			for(auto v:eg[u]){
				hs2[v]=hs1[v]+f(hs2[u]-f(hs1[v]));
				self(self,v);
			}
		};
		
		DFS1(DFS1,rt);
		hs2[rt]=hs1[rt];
		DFS2(DFS2,rt);
		
		for(ll i=1;i<=n;i++){
			if(rnk[hs2[i]]){
				ans[cnt]=min(ans[cnt],rnk[hs2[i]]);
			}else{
				rnk[hs2[i]]=cnt;
			}
		}
	}
	
	for(ll i=1;i<=cnt;i++){
		cout<<ans[i]<<endl;
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
