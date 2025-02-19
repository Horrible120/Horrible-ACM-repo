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

class H_FHQ_Treap{
public:
	class Node{
	public:
		Node *lch,*rch;
		ll siz,wcnt,val,rank;
		Node(){
			lch=rch=nullptr;
		}
		Node(ll _val){
			siz=wcnt=1;
			val=_val;
			rank=rnd();
			lch=rch=nullptr;
		}
		void Calc(){
			siz=wcnt;
			if(lch!=nullptr) siz+=lch->siz;
			if(rch!=nullptr) siz+=rch->siz;
		}
	};
	
	Node *root;
	
	H_FHQ_Treap(){
		root=nullptr;
	}
	
	pair<Node*,Node*> split_by_val(Node *pos,ll key){
		if(pos==nullptr) return {nullptr,nullptr};
		if(pos->val<=key){
			auto [ls,rs]=split_by_val(pos->rch,key);
			pos->rch=ls;
			pos->Calc();
			return {pos,rs};
		}
		else{
			auto [ls,rs]=split_by_val(pos->lch,key);
			pos->lch=rs;
			pos->Calc();
			return {ls,pos};
		}
	}
	
	tuple<Node*,Node*,Node*> split_by_rank(Node* pos,ll rk){
		if(pos==nullptr) return {nullptr,nullptr,nullptr};
		ll lsiz=pos->lch==nullptr?0:pos->lch->siz;
		if(rk<=lsiz){
			auto[l,mid,r]=split_by_rank(pos->lch,rk);
			pos->lch=r;
			pos->Calc();
			return {l,mid,pos};
		}
		else if(rk<=lsiz+pos->wcnt){
			auto ls=pos->lch,rs=pos->rch;
			pos->lch=nullptr;
			pos->rch=nullptr;
			return {ls,pos,rs};
		}
		else{
			auto[l,mid,r]=split_by_rank(pos->rch,rk-lsiz-pos->wcnt);
			pos->rch=l;
			pos->Calc();
			return {pos,mid,r};
		}
	}
	
	Node *merge(Node *u,Node *v){
		if(u==nullptr&&v==nullptr) return nullptr;
		if(u!=nullptr&&v==nullptr) return u;
		if(u==nullptr&&v!=nullptr) return v;
		
		if(u->rank<=v->rank){
			u->rch=merge(u->rch,v);
			u->Calc();
			return u;
		}
		else{
			v->lch=merge(u,v->lch);
			v->Calc();
			return v;
		}
	}
	
	void insert(ll val){
		auto [ls,rs]=split_by_val(root,val);
		auto [lls,lrs]=split_by_val(ls,val-1);
		Node *new_node;
		if(lrs==nullptr){
			new_node=new Node(val);
		}
		else{
			lrs->wcnt++;
			lrs->Calc();
		}
		root=merge(merge(lls,lrs==nullptr?new_node:lrs),rs);
	}
	
	void del(ll val){
		auto [ls,rs]=split_by_val(root,val);
		auto [lls,lrs]=split_by_val(ls,val-1);
		if(lrs->wcnt>1){
			lrs->wcnt--;
			lrs->siz--;
			lls=merge(lls,lrs);
		}else{
			if(ls==lrs)
				ls=nullptr;
			delete lrs;
			lrs=nullptr;
		}
		root=merge(lls,rs);
	}
	
	ll query_rank_by_val(Node *pos,ll val){
		auto [ls,rs]=split_by_val(pos,val-1);
		ll res=(ls==nullptr?0:ls->siz)+1;
		root=merge(ls,rs);
		return res;
	}
	
	ll query_val_by_rank(Node *pos,ll rk){
		auto [l,mid,r]=split_by_rank(pos,rk);
		ll res=mid->val;
		root=merge(merge(l,mid),r);
		return res;
	}
	
	ll query_prev(ll val){
		auto [ls,rs]=split_by_val(root,val-1);
		ll res=query_val_by_rank(ls,ls->siz);
		root=merge(ls,rs);
		return res;
	}
	
	ll query_nxt(ll val){
		auto [ls,rs]=split_by_val(root,val);
		ll res=query_val_by_rank(rs,1);
		root=merge(ls,rs);
		return res;
	}
};

void solve(){
	ll n,m,ans=0,last=0;
		cin>>n>>m;
		H_FHQ_Treap treap=H_FHQ_Treap();
		for(ll i=1;i<=n;i++){
			ll x;
			cin>>x;
			treap.insert(x);
		}
		for(ll i=1;i<=m;i++){
			ll op,x;
			cin>>op>>x;
			if(op==1)
				treap.insert(x^last);
			else if(op==2)
				treap.del(x^last);
			else if(op==3)
				ans^=last=treap.query_rank_by_val(treap.root,x^last);
			else if(op==4)
				ans^=last=treap.query_val_by_rank(treap.root,x^last);
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
