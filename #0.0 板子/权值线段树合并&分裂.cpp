#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef int ll;
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
	class Node{	//节点信息类
	public:
		ll lch,rch,siz;
		
		Node()=default;	//无意义构造函数
		Node(ll x):lch(),rch(),siz(x){	//有意义的构造函数
			
		}	
	};
	
	ll low,top,tot;
	vector<Node> node;
	
	H_Val_Segment_Tree(ll _sz,ll _low,ll _top){	//初始化
		low=_low;
		top=_top;
		tot=0;
		node.assign(_sz,Node());
	}
	
	void update(ll u){	//由子节点更新父节点信息
		Node &cur=node[u];
		cur.siz=(cur.lch?node[cur.lch].siz:0)+(cur.rch?node[cur.lch].siz:0);
		
	}
	
	void add_vals(ll &rt,ll x,ll key){	//向以 rt 号节点为根的树内一次 x 个值 key
		_add_vals(rt,low,top,x,key);
	}
	
	void tree_merge(ll &new_rt,ll a_rt,ll b_rt){//将编号为 a_rt 和 b_rt 的两棵树合并为一棵树，新树根节点编号为 new_rt
		/*
		有一个可能存在的问题:如果我要把合并之后的树存到原来的某棵树的位置，会不会在合并的过程中出现问题？
		>> 一个显而易见的解决方法是先选一个 tmp 作为新根节点，在合并完成后将原来某一颗树的根节点改为 tmp 无非多一点点空间
		>> 但是能不能解决或者说明这样做不会有问题呢？
		*/
		_tree_merge(new_rt,a_rt,b_rt,top,low);
	}
	
	void tree_split(ll &new_rt,ll &past_rt,ll s,ll t){	//将 past_rt 中 [s,t] 的数值全部分裂出去到 new_rt 中
		_tree_split(new_rt,past_rt,s,t,low,top);
	}
	
	ll query_siz(ll rt,ll s,ll t){
		return _query_siz(rt,s,t,low,top);
	}
	
	ll query_kth(ll rt,ll k){
		return _query_kth(rt,low,top,k);
	}
	
private:
	
	void _add_vals(ll &u,ll l,ll r,ll x,ll key){	//本质上是 u 子树内的 key 位置修改 x	
		if(!u) u=++tot;
		
		Node &cur=node[u];
		
		if(l==r){	//叶子节点的修改操作
			cur.siz+=x;
			return;
		}
		
		ll mid=l+r>>1;
		if(key<=mid)
			_add_vals(cur.lch,l,mid,x,key);
		else
			_add_vals(cur.rch,mid+1,r,x,key);
		update(u);
	}
	
	Node _node_merge(Node &a,Node &b){
		Node res=Node();
		res.siz=a.siz+b.siz;
		return res;
	}
	
	void _tree_merge(ll &u,ll a,ll b,ll l,ll r){	//将 a&b 节点合并，新节点为 u
		if(!a||!b){
			u=a+b;
			return;
		}
		
		if(!u) u=++tot;
		Node &cur=node[u],&na=node[a],&nb=node[b];
		
		if(l==r){	//叶节点的合并
			node[u]=_node_merge(na,nb);
			return;
		}
		
		ll mid=l+r>>1;
		_tree_merge(cur.lch,na.lch,nb.lch,l,mid);
		_tree_merge(cur.rch,na.rch,nb.rch,mid+1,r);
		update(u);
	}
	
	void _tree_split(ll &u,ll &v,ll s,ll t,ll l,ll r){
		if(l>t||r<s) return;
		if(!v) return;
		
		if(s<=l&&t>=r){	//把完整的一的节点分裂出去
			u=v;
			v=0;
			return;
		}
		
		if(!u) u=++tot;
		ll mid=l+r>>1;
		if(s<=mid) _tree_split(node[u].lch,node[v].lch,s,t,l,mid);
		if(t>mid) _tree_split(node[u].rch,node[v].rch,s,t,mid+1,r);
		update(u);
		update(v);
	}
	
	ll _query_siz(ll u,ll s,ll t,ll l,ll r){
		if(l>t||r<s) return 0;
		if(!u) return 0;
		
		Node &cur=node[u];
		
		if(s<=l&&t>=r)
			return cur.siz;
		
		ll mid=l+r>>1;
		
		if(s<=mid&&t>mid) return _query_siz(node[u].lch,s,t,l,mid)+
								_query_siz(node[u].rch,s,t,mid+1,r);
		else if(s<=mid) return _query_siz(node[u].lch,s,t,l,mid);
		else if(t>mid) return _query_siz(node[u].rch,s,t,mid+1,r);
	}
	
	ll _query_kth(ll u,ll l,ll r,ll k){
		if(l==r)
			return l;
		
		Node &cur=node[u];
		ll mid=l+r>>1;
		
		if(k<=node[cur.lch].siz)
			return _query_kth(cur.lch,l,mid,k);
		else
			return _query_kth(cur.rch,mid+1,r,k-node[cur.lch].siz);
	}
	
};

void solve(){
	ll n,m,tot=1;
	cin>>n>>m;
	vector<ll> rt(n+m+1);
	H_Val_Segment_Tree sgm((n+1)*2*18,1,n);
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		sgm.add_vals(rt[1],x,i);
	}
	for(ll i=1;i<=m;i++){
		ll op,p,t,x,q,y,k;
		cin>>op;
		if(op==0){
			cin>>p>>x>>y;
			sgm.tree_split(rt[++tot],rt[p],x,y);
		}
		if(op==1){
			cin>>p>>t;
			sgm.tree_merge(rt[p],rt[p],rt[t]);
		}
		if(op==2){
			cin>>p>>x>>q;
			sgm.add_vals(rt[p],x,q);
		}
		if(op==3){
			cin>>p>>x>>y;
			cout<<sgm.query_siz(rt[p],x,y)<<endl;
		}
		if(op==4){
			cin>>p>>k;
			cout<<sgm.query_kth(rt[p],k)<<endl;
		}
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
