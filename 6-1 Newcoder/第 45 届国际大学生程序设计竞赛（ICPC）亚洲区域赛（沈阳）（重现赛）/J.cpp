#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll, ll>;
template <typename T> using v2ct = vector<vector<T >>;
template <typename T> using v3ct = vector<vector<vector<T >>>;

template <typename T, typename Compare = std::less<T >>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF) + time(0) );

ll tt = 1;

class H_Segment_Tree{
public:

	class Node{
	public:
		ll lhs, rhs;
		ll val;
		Node(): lhs(0), rhs(0), val(0) {}
	};

	ll n, tot;
	vector<Node> tr;

	H_Segment_Tree(ll _n) {
		n = _n;
		tot = 0;
		tr.assign(20000001, Node());
	}

	void build_tree(ll &u, ll l, ll r) {
		if (!u)
			u = ++tot;

		if (l == r) {
			tr[u].val = 1;
			return;
		}

		ll mid = (l + r) >> 1;
		build_tree(tr[u].lhs, l, mid);
		build_tree(tr[u].rhs, mid + 1, r);
		
		tr[u].val = tr[tr[u].lhs].val + tr[tr[u].rhs].val;
	}

	void modify(ll u,ll &v,ll l,ll r,ll s,ll t){	//把 u 结点子树中的 [s,t] 部分完全传给 v 节点
		if(!u)
			return;
		
		if(l>=s&&r<=t){
			v=u;
			return;
		}
		
		++tot;
		tr[tot]=tr[v];
		v=tot;
		
		ll mid=l+r>>1;
		if(mid>=s)
			modify(tr[u].lhs,tr[v].lhs,l,mid,s,t);
		if(mid+1<=t)
			modify(tr[u].rhs,tr[v].rhs,mid+1,r,s,t);
		
		tr[v].val=tr[tr[v].lhs].val+tr[tr[v].rhs].val;
	}
	
	ll query(ll u,ll l,ll r,ll s,ll t){
		if(!u)
			return 0ll;
		if(l>=s&&r<=t)
			return tr[u].val;
		ll mid=l+r>>1,res=0;
		if(mid>=s)
			res+=query(tr[u].lhs,l,mid,s,t);
		if(mid+1<=t)
			res+=query(tr[u].rhs,mid+1,r,s,t);
		return res;
	}
};

void solve() {
	ll n, q;
	cin >> n >> q;

	vector<ll> rt(500005,0);

	H_Segment_Tree sgm(n);
	
	sgm.build_tree(rt[0],1,n);

	for (ll i = 1; i <= q; i++) {
		ll op,ql,qr,k;
		cin>>op;
		if(op==1){
			cin>>ql>>qr>>k;
			sgm.modify(rt[k],rt[k+1],1,n,ql,qr);
		}
		else{
			cin>>ql>>qr;
			ll l=0,r=i;
			while(l<r){
				ll mid=(l+r+1)/2;
				if(sgm.query(rt[mid],1,n,ql,qr))
					l=mid;
				else
					r=mid-1;
			}
//			OOO
			cout<<l<<endl;
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
