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
	ll n;
	cin>>n;
	vector<ll> vv((1<<n)+1,0);
	vector<ll> ans;
	for(ll i=1;i<=(1<<n)-1;i++){
		cin>>vv[i];
	}
	
	vv[0]=1;
	
	auto DFS=[&](auto &&self,vector<ll> v,ll k,ll cur)->void{
		if(!k){
			if(v[0]&1ll){
				ans.emplace_back(cur);
			}
			return;
		}
		
		ll m=1<<k-1;
		
		vector<ll> v1(m+1,0);
		for(ll i=0;i<=m-1;i++){
			v1[i]=v[i]&v[i+m];
		}
		self(self,v1,k-1,cur);
		for(ll i=0;i<=m-1;i++){
			v1[i]=v[i]&(v[i+m]>>1);
		}
		self(self,v1,k-1,cur+m);
	};
	
	DFS(DFS,vv,n,0);
	
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<endl;
	for(auto it:ans){
		cout<<it<<endl;
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
