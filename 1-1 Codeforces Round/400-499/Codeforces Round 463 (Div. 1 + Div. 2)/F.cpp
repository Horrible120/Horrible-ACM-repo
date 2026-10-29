#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

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
	ll n;
	cin>>n;
	vector<ll> a(n+1),b(n+1),dp(n+1);
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=n;i++)
		cin>>b[i];
	vector<vector<ll>> eg(n+1);
	for(ll i=1,u,v;i<n;i++){
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}

	vector<ll> fa(n+1),ord{1};
	for(ll i=0;i<n;i++){
		ll u=ord[i];
		for(ll v:eg[u]){
			if(v==fa[u])
				continue;
			fa[v]=u;
			ord.emplace_back(v);
		}
	}

	ll tot=0;
	vector<array<ll,3>> tr(20*n+1);
	vector<ll> rt(n+1);
	vector<vector<ll>> bag(n+1);
	auto calc=[&](ll id,ll x)->ll{
		return b[id]*x+dp[id];
	};
	auto add=[&](this auto &&self,ll &p,ll l,ll r,ll id)->void{
		if(!p){
			p=++tot;
			tr[p]={0,0,id};
			return;
		}
		ll mid=l+(r-l)/2;
		if(calc(id,mid)<calc(tr[p][2],mid))
			swap(id,tr[p][2]);
		if(l==r)
			return;
		if(calc(id,l)<calc(tr[p][2],l))
			self(tr[p][0],l,mid,id);
		else if(calc(id,r)<calc(tr[p][2],r))
			self(tr[p][1],mid+1,r,id);
	};
	auto qry=[&](this auto &&self,ll p,ll l,ll r,ll x)->ll{
		if(!p)
			return INF;
		ll ans=calc(tr[p][2],x);
		if(l==r)
			return ans;
		ll mid=l+(r-l)/2;
		if(x<=mid)
			return min(ans,self(tr[p][0],l,mid,x));
		return min(ans,self(tr[p][1],mid+1,r,x));
	};

	for(ll i=n-1;i>=0;i--){
		ll u=ord[i],son=0;
		for(ll v:eg[u]){
			if(v!=fa[u]&&bag[v].size()>bag[son].size())
				son=v;
		}
		if(son){
			rt[u]=rt[son];
			bag[u].swap(bag[son]);
			for(ll v:eg[u]){
				if(v==fa[u]||v==son)
					continue;
				for(ll id:bag[v]){
					add(rt[u],-100000,100000,id);
					bag[u].emplace_back(id);
				}
				vector<ll>().swap(bag[v]);
			}
			dp[u]=qry(rt[u],-100000,100000,a[u]);
		}
		add(rt[u],-100000,100000,u);
		bag[u].emplace_back(u);
	}

	for(ll i=1;i<=n;i++)
		cout<<dp[i]<<" \n"[i==n];
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
