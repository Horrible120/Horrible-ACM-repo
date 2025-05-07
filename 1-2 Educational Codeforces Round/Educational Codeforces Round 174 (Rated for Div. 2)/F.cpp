#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef int ll;
typedef uint64_t ull;
using pll = pair<ll, ll>;
template <typename T> using v2ct = vector<vector<T >>;
template <typename T> using v3ct = vector<vector<vector<T >>>;

template <typename T, typename Compare = std::less<T >>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF) + time(0) );

ll tt = 1;

void solve() {
	ll n, q;
	cin >> n >> q;
	
	//注意!! 除了 cntb / bk_b / tr_b   标为 _b 的变量其实存的是 a,b 的并!!!

	ll cnta = n, cntb = n;	//记录连通分量数
	
	vector<ll> fa_a(n + 1, 0), fa_b(n + 1, 0);	//dsu父亲数组
	vector<ll> siz_a(n + 1, 0), siz_b(n + 1, 0);	//dsu节点大小数组 (用于按秩合并)
	vector<pair<ll&, ll >> bac_a, bac_b;	//原数据记录数组 用于撤销

	v2ct<pair<ll, ll >> tr_a(4 * q + 5),tr_b(4*q+5);	//线段树 记录区间上的加边操作

	map<pair<ll, ll>, ll> bk_a,bk_b;	//记录加边的过程

	auto add_edge_a = [&](auto &&self, ll u, ll l, ll r, ll s, ll t, ll x, ll y)->void{	
		//在线段树上“分治”生命周期为 [s,t] 的A边 (x,y)
		if (l >= s && r <= t) {
			//同时加两个图
			tr_a[u].emplace_back(x, y);
			tr_b[u].emplace_back(x, y);
			return;
		}

		ll mid = l + r>>1;
		if (mid >= s)
			self(self, u * 2, l, mid, s, t, x, y);
		if (mid + 1 <= t)
			self(self, u * 2 + 1, mid + 1, r, s, t, x, y);
	};
	
	auto add_edge_b = [&](auto &&self, ll u, ll l, ll r, ll s, ll t, ll x, ll y)->void{	
		//在线段树上“分治”生命周期为 [s,t] 的B边 (x,y)
		if (l >= s && r <= t) {
			//只加在 _b 上
			tr_b[u].emplace_back(x, y);
			return;
		}
		
		ll mid = l + r>>1;
		if (mid >= s)
			self(self, u * 2, l, mid, s, t, x, y);
		if (mid + 1 <= t)
			self(self, u * 2 + 1, mid + 1, r, s, t, x, y);
	};
	
	auto get_fa=[&](vector<ll> &fa,ll x)->ll{	//获取某个节点所在树的根
		while(fa[x]!=x)
			x=fa[x];
		return x;
	};
	
	auto dsu_merge=[&](vector<ll> &fa,vector<ll> &siz,vector<pair<ll&, ll >> &bac,ll &cnt,ll x,ll y)->void{
		//合并两个节点所在的树
		ll fx=get_fa(fa,x),fy=get_fa(fa,y);
		
		if(fx==fy)
			return;
		
		if(siz[fx]<siz[fy])	//保证按秩合并
			swap(fx,fy);
		
		bac.emplace_back(siz[fx],siz[fx]);	//记录修改之前的数据 用于撤销回滚
		siz[fx]+=fy;	//更新 siz
		
		bac.emplace_back(fa[fy],fa[fy]);	//同
		fa[fy]=fx;	//更新 fa
		
		bac.emplace_back(cnt,cnt);	//同
		cnt--;	//属于不同的连通块 所以连通块数量--
	};
	
	auto DFS=[&](auto &&self,ll u,ll l,ll r)->void{	//遍历线段树 离线获取答案
		ll m_a=bac_a.size(),m_b=bac_b.size();	//记录未操作前的 回滚数组 的大小 (用于记录应该回滚到什么地方)
		
		for(auto [x,y]:tr_a[u]){	//加A边操作
			dsu_merge(fa_a,siz_a,bac_a,cnta,x,y);
			dsu_merge(fa_b,siz_b,bac_b,cntb,x,y);
		}
		
		for(auto [x,y]:tr_b[u]){	//加B边操作
			dsu_merge(fa_b,siz_b,bac_b,cntb,x,y);
		}
		
		ll mid=l+r>>1;
		if(l==r){	//到某个单位时间了 就输出对应的答案
//			OOO
			cout<<cnta-cntb<<endl;
//			cout<<cnta<<' '<<cntb<<endl;
		}
		else{	//还有就继续 DFS
			self(self,u*2,l,mid);
			self(self,u*2+1,mid+1,r);
		}
		
		while(bac_a.size()>m_a){	//回滚 A
			auto [it,val]=bac_a.back();
			it=val;
			bac_a.pop_back();
		}
		
		while(bac_b.size()>m_b){	//回滚 B
			auto [it,val]=bac_b.back();
			it=val;
			bac_b.pop_back();
		}
	};

	for (ll i = 1; i <= n; i++) {//初始化并查集
		fa_a[i] = fa_b[i] = i;
		siz_a[i] = siz_b[i] = 1;
	}

	for (ll i = 1; i <= q; i++) {
		string s;
		ll x, y;
		cin >>s>> x >> y;

		if (x > y)	//统一边的表示法
			swap(x, y);
		
		if(s[0]=='A'){	//加A边
			if (!bk_a[make_pair(x, y)])	//未被加入 记录左端点
				bk_a[make_pair(x, y)] = i;
			else {	//已被加入 生命周期右端点已知 直接分治加边
				add_edge_a(add_edge_a, 1ll, 1ll, q, bk_a[make_pair(x, y)], i - 1, x, y);
				bk_a[make_pair(x, y)] = 0;
				}
		}
		else{	//同理 加B边
			if (!bk_b[make_pair(x, y)])
				bk_b[make_pair(x, y)] = i;
			else {
				add_edge_b(add_edge_b, 1ll, 1ll, q, bk_b[make_pair(x, y)], i - 1, x, y);
				bk_b[make_pair(x, y)] = 0;
			}
		}
	}

	//处理右端点未出现 (也就是右端点为 q ) 的边
	for (auto [p, l] : bk_a)	
		if(l!=0)
			add_edge_a(add_edge_a, 1, 1, q, l, q, p.first, p.second),
			add_edge_b(add_edge_b, 1, 1, q, l, q, p.first, p.second);
	for (auto [p, l] : bk_b)
		if(l!=0)
			add_edge_b(add_edge_b, 1, 1, q, l, q, p.first, p.second);
	
	//离线计算
	DFS(DFS,1,1,q);
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
