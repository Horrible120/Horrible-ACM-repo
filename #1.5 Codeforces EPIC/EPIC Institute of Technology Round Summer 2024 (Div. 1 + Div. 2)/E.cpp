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
vector<ll> vis,rst,dpt;

void solve(){
	ll n;
	cin>>n;
	vector<ll> w(n+1);
	for(ll i=1;i<=n;i++) cin>>w[i];
	
	
	
	vector<ll> eg[n+1];
	ll x,y;
	for(ll i=2;i<=n;i++){
		cin>>x;
		eg[x].emplace_back(i);
		eg[i].emplace_back(x);
	}
	
	vis=rst=dpt=vector<ll>(n+1);
	
	function<void(ll,ll)> DFS1=[&](ll x,ll f){
		vis[x]=1;
		rst[x]=-w[x];
		dpt[x]=dpt[f]+1;
		for(auto it:eg[x]){
			if(vis[it]) continue;
			DFS1(it,x);
			rst[x]+=w[it];
		}
		if(eg[x].size()==1) rst[x]=INF;
	};
	
	DFS1(1,0);
	
	ll ans=0;
	vis=vector<ll>(n+1,0);
	
	struct cmp{
		bool operator()(ll a, ll b) const {
			return dpt[a] < dpt[b];
		}
	};
	
	multiset<ll,cmp> stk;
	
	function<void(ll)> DFS2=[&](ll x){
		vis[x]=1;
		for(auto it:eg[x]){
			if(vis[it]) continue;
			DFS2(it);
		}
		
		while(rst[x]<0){	//如果当前节点非叶子节点且有待处理的
			ll cur=*stk.begin();
			ll tmp=min(rst[cur],-rst[x]);
			
			rst[x]+=tmp;
			rst[cur]-=tmp;
			ans+=tmp*(dpt[cur]-dpt[x]);
			
			stk.erase(stk.begin());
			stk.insert(cur);
			
			cout<<"!!"<<x<<' '<<cur<<' '<<ans<<endl;
			if(rst[cur]==0) stk.erase(stk.begin());
		}
		if(rst[x]>0) stk.insert(x);
	};
	
	DFS2(1);
	OOO
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
