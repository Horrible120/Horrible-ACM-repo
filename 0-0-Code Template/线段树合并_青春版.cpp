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

		Node(){};
		Node(ll x,ll _val){	//初始化节点 (x个值val)
			lch=rch=0;
			siz=x;
		}
	};
	
	ll low,top,tot;
	vector<Node> node;
	
	H_Val_Segment_Tree(ll _sz,ll _low,ll _top){
		tot=0;
		low=_low;
		top=_top;
		node.assign(_sz+1,Node());
	}
	
	void update(ll u){	//由儿子节点更新节点信息
		Node &cur=node[u];
		cur.siz=node[cur.lch].siz+node[cur.rch].siz;
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
		if(l==r){
			node[u].siz+=x;
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
			node[u]=Node(na.siz+nb.siz,l);	// !!! 未定
			return;
		}
		
		ll mid=l+r>>1;
		_merge(cur.lch,na.lch,nb.lch,l,mid);
		_merge(cur.rch,na.rch,nb.rch,mid+1,r);
		update(u);
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
