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

ll tt = 1;

void solve() {
	ll n, m, tot = 0, sub = 0,sccnt=0;
	cin >> n >> m;
	
	//原图的邻接表 DFS序 low[]数组 是否在栈记号 EDCC归属标记
	vector<ll> e[n + 1], dfn(n + 1), low(n + 1),vis(n+1),id(n+1);
	
	vector<pair<ll, ll>> brg;	//每一个桥的两端点
	
	map<ll,ll> cnt;
	
	ll x, y;
	for (ll i = 1; i <= m; i++) {	//建图
		cin >> x >> y;
		e[x].emplace_back(y);
		e[y].emplace_back(x);
	}
	
	stack<ll> stk;
	function<void(ll,ll)> Tarjan=[&](ll x,ll fa){
		vis[x]=true;
		dfn[x]=low[x]=++tot;
		stk.push(x);
		for(auto it:e[x]){
			if(!dfn[it]){
				Tarjan(it,x);
				low[x]=min(low[x],low[it]);
			}else if(it!=fa&&vis[it])
				low[x]=min(low[x],dfn[it]);
		}
		ll cur;
		if(low[x]==dfn[x]){
			if(x!=1) brg.emplace_back(make_pair(x,fa));
			++sccnt;
			do{
				cur=stk.top();
				stk.pop();
				vis[cur]=false;
				id[cur]=sccnt;
				cnt[sccnt]++;
			}while(cur!=x);
		}
	};
	
	Tarjan(1,1);
	
//	for(auto [x,y]:brg) cout<<'['<<x<<','<<y<<']'<<' ';cout<<endl;
	
	vector<ll> eg[sccnt+1],subt(sccnt+1);
	for(auto [x,y]:brg){
		eg[id[x]].emplace_back(id[y]);
		eg[id[y]].emplace_back(id[x]);
	}
	
	vis=vector<ll>(n+1,0);
	function<void(ll)> DFS=[&](ll x){
		vis[x]=true;
		subt[x]=cnt[x];
		for(auto it:eg[x])
			if(!vis[it]) DFS(it),subt[x]+=subt[it];
	};
	
	if(brg.size()) DFS(id[brg[0].first]);
	
//	for(ll i=1;i<=sccnt;i++) cout<<subt[i]<<' ';cout<<endl;
	
	for(ll i=1;i<=sccnt;i++)
		sub=max(sub,subt[i]*(n-subt[i]));
//	OOO
	cout<<n*(n-1)/2-sub<<endl;
}
	
//	↓写假了的缩点↓ 千万不要“我觉得”然后就开始写了，尤其是图论这种 反例比较常见但又不太好找 的模块
//	先理解清楚图的 DFN生成树 的逻辑
	/*function<void(ll, ll)> Tarjan = [&](ll x, ll fa) {	//Tarjan求桥和low[]
	dfn[x] = low[x] = ++tot;
	
	for (auto it : e[x]) {
	if (!dfn[it]) {
	Tarjan(it, x);
	low[x] = min(low[x], low[it]);
	if (low[it] > dfn[x])
	brg.emplace_back(make_pair(x, it));
	} else if (it != fa)
	low[x] = min(low[x], dfn[it]);
	}
	};
	
	Tarjan(1, 1);
	
	map<ll, ll> cnt;	//每个low[]值对应的节点数，也就是每一个边双连通分量的大小
	vector<ll> eg[n + 1], subt(n + 1), vis(n + 1);	//缩点后的邻接表，子树大小，DFS用的vis[]数组
	
	for (auto [u, v] : brg) {	//使用存下的桥的数据构建缩点后的树
	eg[low[u]].emplace_back(low[v]);
	eg[low[v]].emplace_back(low[u]);
	}
	for (ll i = 1; i <= n; i++)	//统计每个low[]值对应的节点数
	cnt[low[i]]++;
	
	function<void(ll)> DFS = [&](ll x) {	//DFS统计子树大小
	vis[x] = 1;
	subt[x] = cnt[x];
	for (auto it : eg[x]) {
	if (vis[it]) continue;
	DFS(it);
	subt[x] += subt[it];
	}
	};
	
	if (brg.size()) DFS(low[brg[0].first]);	//如果没有桥就没可能减少联通点对
	
//	for(ll i=1;i<=n;i++) cout<<low[i]<<" \n"[i==n];
//	cout.flush();
	
	for (auto [x, y] : brg) {	//求最多可能减小的联通点对数量
	sub = max(sub, subt[low[x]] * (n - subt[low[x]]));
	sub = max(sub, subt[low[y]] * (n - subt[low[y]]));
	}
//	OOO
	cout << n*(n - 1) / 2 - sub << endl;*/
	
	
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
