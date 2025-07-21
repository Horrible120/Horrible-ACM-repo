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

template <typename T>
class Segment_tree{
public:
	class Tag{	//修改标记类
	public:
		bool status;
		// $$$ 要维护的标记内容，按需添加
		
		
		Tag():status(false){}	// 无效 tag 初始化
		
		Tag(const T &t):status(true){}	  // $$$ 有效 tag 初始化，按需具体实现
		
		void apply(const Tag &t){	// 将 tag 下放应用到 当前tag 上的操作
			if(!t.status) return;
			if(status){		// $$$ 当前 tag 非空时的应用，按需具体实现
				
			}
			else	// 当前 tag 为空
				*this=t;
		}
	};
	
	class Info{		// 节点信息类 
	public:
		ll l,r;	// 左右端点
		// $$$ 要维护的具体信息，按需添加
		
		
		Info():l(0),r(0){} // 无效 Info 初始化，默认将子节点引导向 0 节点，也就是无效节点
		
		Info(const ll &pos,const T &val):l(pos),r(pos){	// 有效 Info 初始化，在 pos 处的数值为 val 的节点
			// $$$ 具体数据初始化实现
		}
		
		friend Info operator+(const Info &lhs,const Info &rhs){	// 重载加法运算符 实现节点信息的合并
			Info res=Info();
			res.l=lhs.l;
			res.r=rhs.r;
			// $$$ 具体合并时的数据维护操作 按需具体实现
			
			return res;
		}
		
		void apply(const Tag &t){	// 将 tag 应用到当前节点上
			if(!t.status) return;
			// $$$ tag 有效时的具体应用操作 按需具体实现
			
		}
	};
	
	// 用 vals 构造线段树 vals 是支持下标访问的容器对象, 例如 std::vector<T>.
	template<typename V>
	Segment_tree(ll _n,const V &vals):n(_n),info(4*n+1,Info()),tag(4*n+1,Tag()){
		build_tree(1,1,n,vals);
	}
	
	void modify(ll ql,ll qr,const Tag &_key){
		if(ql<1||qr>n||ql>qr){
			cout<<"Error form Segment_tree :: modify() -> Range_Error "<<endl;
		}
		if(!_key.status) return;
		modify(1,ql,qr,_key);
	}
	
	Info query(ll ql,ll qr){
		if(ql<1||qr>n||ql>qr){
			cout<<"Error form Segment_tree :: query() -> Range_Error "<<endl;
		}
		return query(1,ql,qr);
	}
	
private:
	ll n;
	vector<Tag> tag;
	vector<Info> info;
	
	template<typename V>
	void build_tree(ll o,ll l,ll r,const V &vals){
		if(l==r){
			info[o]=Info(l,vals[l]);
			return;
		}
		ll mid=(l+r)/2;
		build_tree(o*2,l,mid,vals);
		build_tree(o*2+1,mid+1,r,vals);
		info[o]=info[o*2]+info[o*2+1];
	}
	
	void push_down(ll o){
		info[o*2].apply(tag[o]);
		info[o*2+1].apply(tag[o]);
		tag[o*2].apply(tag[o]);
		tag[o*2+1].apply(tag[o]);
		tag[o]=Tag();
	}
	
	void modify(ll o,ll ql,ll qr,const Tag &_key){
		Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(l>=ql&&r<=qr){
			cur.apply(_key);
			tag[o].apply(_key);
			return;
		}
		
		push_down(o);
		ll mid=(l+r)/2;
		if(ql<=mid) modify(o*2,ql,qr,_key);
		if(qr>=mid+1) modify(o*2+1,ql,qr,_key);
		
		cur=info[o*2]+info[o*2+1];
	}
	
	Info query(ll o,ll ql,ll qr){
		Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(l>=ql&&r<=qr){
			return cur;
		}
		
		push_down(o);
		ll mid=(l+r)/2;
		if(ql<=mid&&qr>=mid+1) return query(o*2,ql,qr)+query(o*2+1,ql,qr);
		else if(ql<=mid) return query(o*2,ql,qr);
		else if(qr>=mid+1) return query(o*2+1,ql,qr);
	}
};

class H_Heavy_Light_decomposition{
public:
	class Node{
	public:
		ll hson,fa,dep,siz;
		ll top,dfn,btm;
		ll val;
		Node():dep(0),fa(0),hson(0),siz(0),top(0),dfn(0),btm(0),val(0){};
	};
	
	ll n,dfn_tot;
	vector<Node> node;
	vector<vector<ll>> eg;
	vector<ll> rnk;
	
	H_Heavy_Light_decomposition(ll _n):n(_n),dfn_tot(0){
		node.assign(n+1,Node());
		eg.assign(n+1,vector<ll>());
		rnk.assign(n+1,0);
	}
	
	void add_edge(ll u,ll v){
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	void HLD_dfs_1(ll cur){
		Node &u=node[cur];
		u.hson=-1;
		u.siz=1;
		for(auto v:eg[cur]){
			if(!node[v].dep){
				node[v].dep=u.dep+1;
				node[v].fa=cur;
				HLD_dfs_1(v);
				u.siz+=node[v].siz;
				if(u.hson==-1||node[v].siz>node[u.hson].siz)
					u.hson=v;
			}
		}
	}
	
	void HLD_dfs_2(ll cur,ll top){
		Node &u=node[cur];
		u.top=top;
		u.btm=u.dfn=++dfn_tot;
		rnk[dfn_tot]=cur;
		if(u.hson==-1)
			return;
		else
			HLD_dfs_2(u.hson,top);
		for(auto v:eg[cur]){
			if(v!=u.hson&&v!=u.fa)
				HLD_dfs_2(v,v);
		}
		u.btm=dfn_tot;
	}
	
	void HLD_init(ll rt){
		node[rt].dep=1;
		HLD_dfs_1(rt);
		HLD_dfs_2(rt,rt);
	}
	
	template<typename T>
	void tree_path_modify(ll x,ll y,Segment_tree<T> &sgm,Segment_tree<T>::Tag tag){
		ll x_top=node[x].top,y_top=node[y].top;
		while(x_top!=y_top){
			if(node[x_top].dep<node[y_top].dep)
				swap(x,y),swap(x_top,y_top);
			sgm.modify(node[x_top].dfn,node[x].dfn,tag);
			x=node[x_top].fa;
			x_top=node[x].top;
		}
		if(node[x].dfn>node[y].dfn)
			swap(x,y);
		sgm.modify(node[x].dfn,node[y].dfn,tag);
	}
	
	template<typename T>
	ll tree_path_query(ll x,ll y,Segment_tree<T> &sgm){
		ll x_top=node[x].top,y_top=node[y].top;
		ll res=0;
		while(x_top!=y_top){
			if(node[x_top].dep<node[y_top].dep)
				swap(x,y),swap(x_top,y_top);
//			res+=sgm.query(node[x_top].dfn,node[x].dfn).val_sum;
			x=node[x_top].fa;
			x_top=node[x].top;
		}
		if(node[x].dfn>node[y].dfn)
			swap(x,y);
//		res+=sgm.query(node[x].dfn,node[y].dfn).val_sum;
		return res%Mod;
	}
};

void solve(){
	
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
