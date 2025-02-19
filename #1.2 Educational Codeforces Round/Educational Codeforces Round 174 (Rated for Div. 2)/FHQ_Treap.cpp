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
	
	Node *rt;
	
	H_FHQ_Treap(){
		rt=nullptr;
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
		else if(rk<=lsiz+pos->siz){
			auto ls=pos->lch,rs=pos->rch;
			pos->lch=nullptr;
			pos->rch=nullptr;
			return {ls,pos,rs};
		}
		else{
			auto[l,mid,r]=split_by_rank(pos->rch,rk);
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
	
	void insert(Node *pos,ll val){
		auto [ls,rs]=split_by_val(rt,val);
		auto [lls,lrs]=split_by_val(ls,val-1);
		Node *new_node;
		if(lrs==nullptr){
			new_node=new Node(val);
		}
		else{
			lrs->wcnt++;
			lrs->Calc();
		}
		rt=merge(merge(lls,lrs==nullptr?new_node:lrs),rs);
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
