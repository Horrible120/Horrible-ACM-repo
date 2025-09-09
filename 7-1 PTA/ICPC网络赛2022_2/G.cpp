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

ll fact[1000001];

void init(){
	ll n=1000000;
	fact[0]=1;
	for(ll i=1;i<=n;i++){
		fact[i]=fact[i-1]*i%Mod;
	}
}

bool cmp(const pll &a,const pll &b){
	if(a.first^b.first){
		return a.first<b.first;
	}else{
		return a.second>b.second;
	}
}

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<pll> p(1);
	for(ll i=1;i<=m;i++){
		ll l,r;
		cin>>l>>r;
		p.emplace_back(make_pair(l,r));
	}
	
	p.emplace_back(make_pair(1,n));
	sort(p.begin()+1,p.end(),cmp);
	p.erase(unique(p.begin()+1,p.end()),p.end());
	
	vector<vector<ll>> son(n+1,vector<ll>());
	
	
	
	vector<ll> stk(m+1);
	ll top=0;
	
	stk[++top]=1;
	
	for(ll i=2;i<p.size();i++){
		while(top>0&&p[stk[top]].second<p[i].second){
			top--;
		}
		son[stk[top]].emplace_back(i);
		stk[++top]=i;
	}
	
//	for(ll i=1;i<=n;i++){
//		cout<<i<<endl;
//		for(auto u:son[i]){
//			cout<<"    "<<p[u].first<<' '<<p[u].second<<endl;
//		}
//	}
	
	auto dfs=[&](auto &&self,ll it)->ll{
		ll tmp=p[it].second-p[it].first+1;
		ll res=1;
		for(auto u:son[it]){
			tmp-=p[u].second-p[u].first;
			res=res*self(self,u)%Mod;
		}
		res=res*fact[tmp]%Mod;
		return res;
	};
	
	cout<<dfs(dfs,1)<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
