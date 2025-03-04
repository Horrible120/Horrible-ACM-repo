#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd(time(0));
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

class H_Treap{
public:
	class Node{	public:
		ll lch,rch;
		ll val,rank;
		ll wcnt,siz;
		
		Node(){
			lch=rch=val=wcnt=siz=rank=0;
		}
		
		Node(ll _val):val(_val),wcnt(1),siz(1){
			lch=rch=0;
			rank=rnd();
		}
	};
	
	
	ll n,rt;
	ll q_prev_tmp,q_nxt_tmp;
	vector<Node> node;
	
	
	H_Treap(ll _sz){
		n=0;
		rt=0;
		node.assign(_sz,Node());
	}
	
	
	void calc(Node &pos){
		pos.siz=pos.wcnt;
		if(pos.lch) pos.siz+=node[pos.lch].siz;
		if(pos.rch) pos.siz+=node[pos.rch].siz;
	}
	
	void L_rotate(ll &pos){
//		cout<<"L_rotate "<<pos<<endl;
		Node &cur=node[pos];
		ll tmp=cur.rch;
		cur.rch=node[tmp].lch;
		node[tmp].lch=pos;
		node[tmp].siz=node[pos].siz;
		calc(node[pos]);
		pos=tmp;
	}
	
	void R_rotate(ll &pos){
//		cout<<"R_rotate "<<pos<<endl;
		Node &cur=node[pos];
		ll tmp=cur.lch;
		cur.lch=node[tmp].rch;
		node[tmp].rch=pos;
		node[tmp].siz=node[pos].siz;
		calc(node[pos]);
		pos=tmp;
	}
	
	void insert(ll &pos,ll val){
		Node &cur=node[pos];
		if(!pos) {
			pos=++n;
			node[pos]=Node(val);
			return;
		}
		cur.siz++;
		if(val==cur.val){
			cur.wcnt++;
		}
		else if(val<cur.val){
			insert(cur.lch,val);
			if(node[node[pos].lch].rank<node[pos].rank)
				R_rotate(pos);
		}
		else{
			insert(cur.rch,val);
			if(node[node[pos].rch].rank<node[pos].rank)
				L_rotate(pos);
		}
	}
	
	bool del(ll &pos,ll val){
		if (!pos) return false;
		if(node[pos].val==val){
			if(node[pos].wcnt>1){
				node[pos].wcnt--;
				node[pos].siz--;
				return true;
			}
			if(node[pos].lch==0||node[pos].rch==0){
				node[pos].siz=node[pos].wcnt=0;
				pos=node[pos].lch+node[pos].rch;
				return true;
			}else if(node[node[pos].lch].rank>=node[node[pos].rch].rank){
				L_rotate(pos);
				return del(pos,val);
			}else{
				R_rotate(pos);
				return del(pos,val);
			}
		}else if(val>node[pos].val){
			bool flag=del(node[pos].rch,val);
			if(flag) node[pos].siz--;
			return flag;
		} else{
			bool flag=del(node[pos].lch,val);
			if(flag) node[pos].siz--;
			return flag;
		}
	}
	
	ll query_rank_by_val(ll pos,ll val){
		Node cur=node[pos];
		ll lsiz=node[cur.lch].siz;
		if(cur.val==val){
			return lsiz+1;
		}else if(val<cur.val){
			if(cur.lch)
				return query_rank_by_val(cur.lch,val);
			else
				return 1;
		}else{
			if(cur.rch)
				return cur.wcnt+lsiz+query_rank_by_val(cur.rch,val);
			else
				return cur.siz+1;
		}
	}
	
	ll query_val_by_rank(ll pos,ll rk){
		if(node[rt].wcnt==0) return 1;
		if(!pos) return 0; 
		Node &cur=node[pos];
		ll lsiz=node[cur.lch].siz;
		if(rk<=lsiz)
			return query_val_by_rank(cur.lch,rk);
		else if(rk<=lsiz+cur.wcnt)
			return cur.val;
		else
			return query_val_by_rank(cur.rch,rk-lsiz-cur.wcnt);
	}
	
	void S_query_prev(ll pos,ll val){
		if(!pos) return;
		Node &cur=node[pos];
		if(val<=cur.val)
			S_query_prev(cur.lch,val);
		else{
			q_prev_tmp=cur.val;
			S_query_prev(cur.rch,val);
		}
	}
	
	ll query_prev(ll val){
		S_query_prev(rt,val);
		return q_prev_tmp;
	}
	
	void S_query_nxt(ll pos,ll val){
		if(!pos) return;
		Node &cur=node[pos];
		if(val>=cur.val)
			S_query_nxt(cur.rch,val);
		else{
			q_nxt_tmp=cur.val;
			S_query_nxt(cur.lch,val);
		}
	}
	
	ll query_nxt(ll val){
		S_query_nxt(rt,val);
		return q_nxt_tmp;
	}
};

void solve(){
	ll n,m,ans=0,last=0;
	cin>>n>>m;
	H_Treap treap=H_Treap(n+m+1);
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		treap.insert(treap.rt,x);
	}
	for(ll i=1;i<=m;i++){
		ll op,x;
		cin>>op>>x;
//		OOO
		
		if(op==1)
			treap.insert(treap.rt,x^last);
		else if(op==2)
			treap.del(treap.rt,x^last);
		else if(op==3)
			ans^=last=treap.query_rank_by_val(treap.rt,x^last);
		else if(op==4)
			ans^=last=treap.query_val_by_rank(treap.rt,x^last);
		else if(op==5)
			ans^=last=treap.query_prev(x^last);
		else
			ans^=last=treap.query_nxt(x^last);
		
//		cout<<"!!! 1 "<<treap.node[1].lch<<' '<<treap.node[1].rch<<endl;
//		cout<<"!!! 2 "<<treap.node[2].lch<<' '<<treap.node[2].rch<<endl;
//		cout<<"!!! 3 "<<treap.node[3].lch<<' '<<treap.node[3].rch<<endl;
	}
//	OOO
	cout<<ans<<endl;
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
