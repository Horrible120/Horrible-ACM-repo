#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

class H_Val_Segment_Tree{
public:
	class Node{	//节点数据类
	public:
		ll lch,rch,siz;	
		ll mnum,mcnt;	//区间众数 & 其出现的次数
		
		Node():lch(0),rch(0),mcnt(0),mnum(0),siz(0){};
		Node(ll x,ll _val){	//初始化节点 (x个值val)
			lch=rch=0;
			siz=x;
			mnum=_val;
			mcnt=x;
		}
	};
	
	ll low,top,tot;
	vector<Node> node;
	
	H_Val_Segment_Tree(ll _sz,ll _low,ll _top){	//值域为 [_low,_top] 的权值线段树
		tot=0;
		low=_low;
		top=_top;
		node.assign(_sz+1,Node());
	}
	
	void update(ll u){	//由儿子节点更新节点信息
		Node &cur=node[u];
		cur.siz=node[cur.lch].siz+node[cur.rch].siz;
		if(node[cur.lch].mcnt>=node[cur.rch].mcnt){
			cur.mcnt=node[cur.lch].mcnt;
			cur.mnum=node[cur.lch].mnum;
		}else{
			cur.mcnt=node[cur.rch].mcnt;
			cur.mnum=node[cur.rch].mnum;
		}
	}
	
	void add_vals(ll &rt,ll x,ll key){	//向以 rt 号节点为根的树内一次插入 x 个值 key
		_add_vals(rt,low,top,x,key);
	}
	
	void merge(ll &rt,ll a,ll b){	//将编号为 a 和 b 的两棵树合并为一棵树，新树根节点编号为 rt
		_merge(rt,a,b,low,top);
	}
	
private:
	
	void _add_vals(ll &u,ll l,ll r,ll x,ll key){	//当前节点 u 范围 [l,r] 插入 x 个值 key
		if(!u) u=++tot;
//		cout<<"!!! "<<u<<' '<<l<<' '<<r<<endl;
		if(l==r){
			node[u].siz+=x;
			node[u].mnum=l;
			node[u].mcnt+=x;
			return;
		}
		ll mid=l+r>>1;
		if(key<=mid)
			_add_vals(node[u].lch,l,mid,x,key);
		else
			_add_vals(node[u].rch,mid+1,r,x,key);
		update(u);
	}
	
	void _merge(ll &u,ll a,ll b,ll l,ll r){	//将 a&b 节点合并，新节点为 u
		if(!a||!b){
			u=a+b;
			return;
		}
		
		if(!u) u=++tot;
		Node &cur=node[u],&na=node[a],&nb=node[b];
		if(l==r){
			node[u]=Node(na.mcnt+nb.mcnt,l);
//			cout<<"NEW "<<l<<' '<<node[u].siz<<endl;
			return;
		}
		
		ll mid=l+r>>1;
		_merge(cur.lch,na.lch,nb.lch,l,mid);
		_merge(cur.rch,na.rch,nb.rch,mid+1,r);
		update(u);
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	H_Val_Segment_Tree sgm((n+m+1)*40,1,1e5);
	vector<ll> ans(n+1),eg[n+1],rt(n+1),dep(n+1);	//答案 邻接表 每个房屋对应的根节点 深度
	v2ct<ll> fa(21,vector<ll>(n+1));
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	function<void(ll,ll)> DFS1=[&](ll u,ll _fa){	//预处理dep与fa数组
		fa[0][u]=_fa;
		dep[u]=dep[_fa]+1;
		for(ll i=1;i<=20;i++)
			fa[i][u]=fa[i-1][fa[i-1][u]];
		for(auto it:eg[u]){
			if(it==fa[0][u]) continue;
			DFS1(it,u);
		}
	};
	DFS1(1,0);
	
	auto get_lca=[&](ll a,ll b){	//倍增LCA
		if(dep[a]<dep[b]) swap(a,b);
		while(dep[a]-dep[b])
			a=fa[__lg(dep[a]-dep[b])][a];
		if(a==b) return a;
		else for(ll i=20;i>=0;i--)
				if(fa[i][a]!=fa[i][b]){
					a=fa[i][a];
					b=fa[i][b];
				}
		return fa[0][a];
	};
	
	for(ll i=1;i<=m;i++){	//初始化每个节点处的线段树
		ll u,v,w;
		cin>>u>>v>>w;
		sgm.add_vals(rt[u],1,w);
		sgm.add_vals(rt[v],1,w);
		ll tmp=get_lca(u,v);
		sgm.add_vals(rt[tmp],-1,w);
//		cout<<"&&&"<<rt[u]<<' '<<rt[v]<<' '<<tmp<<' '<<rt[tmp]<<endl;
		
		if(tmp!=1) sgm.add_vals(rt[fa[0][tmp]],-1,w);
	}
	function<void(ll)> DFS2=[&](ll u){	//自底向上统计答案
		for(auto it:eg[u]){
			if(it==fa[0][u]) continue;
			DFS2(it);
			sgm.merge(rt[u],rt[u],rt[it]);
		}
//		cout<<">>>>"<<u<<' '<<sgm.node[rt[u]].siz<<' '<<sgm.node[rt[u]].mnum<<' '<<sgm.node[rt[u]].mnum<<endl;
		ans[u]=sgm.node[rt[u]].mnum;
		if(sgm.node[rt[u]].siz==0) ans[u]=0;
	};
	DFS2(1);
	for(ll i=1;i<=n;i++) cout<<ans[i]<<endl;
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
