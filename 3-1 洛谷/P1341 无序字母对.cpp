#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll m,n=256;
	cin>>m;
	
	vector<ll> fa(n+1,0),siz(n+1,0);
	vector<multiset<ll>> eg(n+1);
	
	auto gf=[&](auto &&self,ll u)->ll{
		if(fa[u]==u)
			return u;
		return fa[u]=self(self,fa[u]);
	};
	
	auto merge=[&](ll u,ll v){
		ll fau=gf(gf,u);
		ll fav=gf(gf,u);
		if(fav==fau)
			return;
		siz[fau]+=siz[fav];
		fa[fav]=fau;
	};
	
	for(ll i=1;i<=m;i++){
		ll u,v;
		string s;
		cin>>s;
		u=s[0]-'A'+1;
		v=s[1]-'A'+1;
		merge(u,v);
		eg[u].insert(v);
		eg[v].insert(u);
	}	
	
	vector<ll> ans;
	auto dfs=[&](auto &&self,ll u)->void{
		while(eg[u].size()){
			ll v=*eg[u].begin();
			eg[u].erase(eg[u].find(v));
			eg[v].erase(eg[v].find(u));
			self(self,v);
		}
		ans.emplace_back(u);
	};
	
	
	
	ll k=0;
	set<ll> fff;
	for(ll i=1;i<=n;i++){
		if(eg[i].size()&1){
			k++;	
		}
		fff.insert(gf(gf,i));
	}
	
	if(fff.size()>1){
		cout<<"No Solution"<<endl;
		return;
	}
	
	if(!k){
		for(ll i=1;i<=n;i++){
			if(eg[i].size()){
				dfs(dfs,i);
				break;
			}
		}
		reverse(ans.begin(),ans.end());
		for(auto it:ans){
			cout<<(char)(it-1+'A');
		}
		cout<<endl;
	}
	else if(k==2){
		for(ll i=1;i<=n;i++){
			if(eg[i].size()&1){
				dfs(dfs,i);
				break;
			}
		}
		reverse(ans.begin(),ans.end());
		for(auto it:ans){
			cout<<(char)(it-1+'A');
		}
		cout<<endl;
	}
	else{
		cout<<"No Solution"<<endl;
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
