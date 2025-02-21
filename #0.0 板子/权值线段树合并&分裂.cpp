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
