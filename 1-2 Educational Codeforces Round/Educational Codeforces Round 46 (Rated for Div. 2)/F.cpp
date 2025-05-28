#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

typedef int ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

/********************************************************************************************/

//template <typename T>
//class H_segment_tree{
//public:
//	
//	class Tag{
//	public:
//		bool status;
//		ll val,lst;
//		
//		Tag():status(0){}
//		
//		Tag(ll _val,ll _lst):status(1){
//			val=_val;
//			lst=_lst;
//		}
//		
//		void apply(const Tag &t){
//			if(!t.status) return;
//			if(status){		// $$$ 当前 tag 非空时的应用，按需具体实现
//				val=t.val;
//				lst=t.lst;
//			}
//			else	// 当前 tag 为空
//				*this=t;
//		}
//	};
//	
//	class Info{
//	public:
//		ll lhs,rhs,l,r;
//		ll min_lst,sng_val;
//		
//		Info():lhs(0),rhs(0),l(0),r(0){
//			min_lst=INF;
//			sng_val=0;
//		}
//		
//		Info(ll pos,ll val,ll lst):lhs(0),rhs(0),l(pos),r(pos){
//			min_lst=lst;
//			sng_val=val;
//		}
//		
//		Info pushup(Info &cur,const Info &lhs,const Info &rhs){
//			cur.l=lhs.l;
//			cur.r=rhs.r;
//			if(lhs.min_lst<=rhs.min_lst)
//				cur.min_lst=lhs.min_lst,
//				cur.sng_val=lhs.sng_val;
//			else
//				cur.min_lst=rhs.min_lst,
//				cur.sng_val=rhs.sng_val;
//		}
//		
//		void apply(const Tag &t){	// 将 tag 应用到当前节点上
//			if(!t.status) return;
//			// $$$ tag 有效时的具体应用操作 按需具体实现
//			min_lst=t.lst;
//			sng_val=t.val;
//		}
//	};
//	
//	
//	
//	H_segment_tree(ll _n){
//		n=_n;
//		tag.assign(n<<6);
//		info.size(n<<6);
//	}
//	
//	
//	
//private:
//	ll n;
//	vector<Tag> tag;
//	vector<Info> info;
//	
//	
//	
//};

/********************************************************************************************/

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),lst(n+1,0),ans(n+1,0);
	map<ll,ll> last;
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(last[v[i]])
			lst[i]=last[v[i]];
		last[v[i]]=i;
	}
	
	class Info{
	public:
		ll lhs,rhs;
		ll min_lst,sng_val;
		
		Info():lhs(0),rhs(0){
			min_lst=INF;
			sng_val=0;
		}
		
		Info(ll pos,ll val,ll lst):lhs(0),rhs(0){
			min_lst=lst;
			sng_val=val;
		}
		
		void pushup(const Info &lhs,const Info &rhs){
			Info &cur=*this;
			if(lhs.min_lst<=rhs.min_lst)
				cur.min_lst=lhs.min_lst,
				cur.sng_val=lhs.sng_val;
			else
				cur.min_lst=rhs.min_lst,
				cur.sng_val=rhs.sng_val;
		}
	};
	
	ll tot=0;
	vector<ll> rt(n+1,0);
	vector<Info> info(n*44+1,Info());
	
	auto modify=[&](auto &&self,ll &u,ll v,ll l,ll r,ll pos,ll lst,ll val)->void{
		u=++tot;
		info[u]=info[v];
		auto &cur=info[u];
		
		if(l==r){
			cur.min_lst=lst;
			cur.sng_val=val;
			return;
		}
		
		ll mid=l+r>>1;
		
		if(pos<=mid)
			self(self,cur.lhs,info[v].lhs,l,mid,pos,lst,val);
		else
			self(self,cur.rhs,info[v].rhs,mid+1,r,pos,lst,val);
		
		cur.pushup(info[cur.lhs],info[cur.rhs]);
//		cout<<u<<' '<<cur.lhs<<' '<<cur.rhs<<' '<<cur.min_lst<<' '<<cur.sng_val<<endl;
	};
	
	auto query=[&](auto &&self,ll u,ll l,ll r,ll s,ll t)->Info{
		if(!u) return Info();
		auto &cur=info[u];
		if(l>=s&&r<=t)
			return cur;
		
		Info res=Info();
		ll mid=l+r>>1;
		
		if(mid>=s&&mid+1<=t)
			res.pushup(self(self,cur.lhs,l,mid,s,t),self(self,cur.rhs,mid+1,r,s,t));
		else if(mid>=t)
			res=self(self,cur.lhs,l,mid,s,t);
		else
			res=self(self,cur.rhs,mid+1,r,s,t);
		return res;
	};
	
//	for(ll i=1;i<=n;i++)
//		cout<<lst[i]<<' ';
//	cout<<endl;
	
	for(ll i=1;i<=n;i++){
		ll tmp=0;
		if(lst[i])
			modify(modify,tmp,rt[i-1],1,n,lst[i],INF,v[i]);
		else
			tmp=rt[i-1];
		modify(modify,rt[i],tmp,1,n,i,lst[i],v[i]);
	}
	
	ll q;
	cin>>q;
	for(ll i=1;i<=q;i++){
		ll l,r;
		cin>>l>>r;
		Info res=query(query,rt[r],1,n,l,r);
		
//		OOO
//		cout<<res.min_lst<<' '<<res.sng_val<<endl;
		
		if(res.min_lst<l)
			cout<<res.sng_val<<endl;
		else
			cout<<0<<endl;
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
