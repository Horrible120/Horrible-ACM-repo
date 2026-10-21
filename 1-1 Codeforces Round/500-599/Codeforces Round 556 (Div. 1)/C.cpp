#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

class H_PST{
public:
	class Info{
	public:
		ll lhs,rhs;
		ll max_dir;
		ll max_lh,max_rh;
		ll max_val,min_val;
		
		Info():lhs(0),rhs(0),max_dir(0),max_lh(-INF),max_rh(-INF),max_val(0),min_val(INF){}
		
		Info(ll val):lhs(0),rhs(0){
			max_dir=0;
			max_lh=max_rh=-val;
			max_val=min_val=val;
		}
		
		void pushup(const Info &ls,const Info &rs){
			Info &cur=*this;
			cur.max_val=max(ls.max_val,rs.max_val);
			cur.min_val=min(ls.min_val,rs.min_val);
			
			cur.max_lh=max(ls.max_lh,rs.max_lh);
			cur.max_lh=max(cur.max_lh,ls.max_val-2*rs.min_val);
			
			cur.max_rh=max(ls.max_rh,rs.max_rh);
			cur.max_rh=max(cur.max_rh,rs.max_val-2*ls.min_val);
			
			cur.max_dir=max(ls.max_dir,rs.max_dir);
			cur.max_dir=max(cur.max_dir,ls.max_lh+rs.max_val);
			cur.max_dir=max(cur.max_dir,rs.max_rh+ls.max_val);
		}
		
	};
	
	ll n,tot;
	vector<Info> tr;
	
	H_PST(ll _n){
		n=_n;
		tot=0;
		tr.assign(4e6,Info());
	}
	
	template<typename V>
	H_PST(ll _n,const V &vals,ll &rt){
		n=_n;
		tot=0;
		tr.assign(4e6,Info());
		build_tree(rt,1,n,vals);
	}
	
	void modify(ll &u,ll v,ll s,ll t,ll key){
		modify(u,v,1,n,s,t,key);
	}
	
	Info query(ll u,ll s,ll t){
		return query(u,1,n,s,t);
	}
	
	void mmodify(ll &u,ll l,ll r,ll s,ll t,ll key){
		if(l>=s&&r<=t){
			tr[u].max_val+=key;
			tr[u].min_val+=key;
			tr[u].max_rh-=key;
			tr[u].max_lh-=key;
			return;
		}
		ll mid=l+r>>1;
		if(mid>=s)
			mmodify(tr[u].lhs,l,mid,s,t,key);
		if(mid+1<=t)
			mmodify(tr[u].rhs,mid+1,r,s,t,key);
		tr[u].pushup(tr[tr[u].lhs],tr[tr[u].rhs]);
	}
	
	
private:
	
	template<typename V>
	void build_tree(ll &u,ll l,ll r,const V &vals){
		u=++tot;
		if(l==r){
			tr[u]=Info(vals[l]);
			return;
		}
		ll mid=l+r>>1;
		build_tree(tr[u].lhs,l,mid,vals);
		build_tree(tr[u].rhs,mid+1,r,vals);
		tr[u].pushup(tr[tr[u].lhs],tr[tr[u].rhs]);
	}
	
	void modify(ll &u,ll v,ll l,ll r,ll s,ll t,ll key){
		u=++tot;
		tr[u]=tr[v];
		if(l>=s&&r<=t){
			tr[u].max_val+=key;
			tr[u].min_val+=key;
			tr[u].max_rh-=key;
			tr[u].max_lh-=key;
			return;
		}
		ll mid=l+r>>1;
		if(mid>=s)
			modify(tr[u].lhs,tr[v].lhs,l,mid,s,t,key);
		if(mid+1<=t)
			modify(tr[u].rhs,tr[v].rhs,mid+1,r,s,t,key);
		tr[u].pushup(tr[tr[u].lhs],tr[tr[u].rhs]);
	}
	
	Info query(ll u,ll l,ll r,ll s,ll t){
		if(!u) return Info();
		if(l>=s&&r<=t)
			return tr[u];
		ll mid=l+r>>1;
		
		if(mid>=s&&mid+1<=t){
			Info res=Info();
			res.pushup(query(tr[u].lhs,l,mid,s,t),query(tr[u].rhs,mid+1,r,s,t));
			return res;
		}
		else if(mid>=s)
			return query(tr[u].lhs,l,mid,s,t);
		else
			return query(tr[u].rhs,mid+1,r,s,t);
	}
	
};

template <typename T>
class H_Segment_tree{
public:
	class Tag{	//修改标记类
	public:
		bool status;
		// $$$ 要维护的标记内容，按需添加
		ll add;
		
		Tag():status(false){}	// 无效 tag 初始化
		
		Tag(const T &t):status(true),add(t){}	  // $$$ 有效 tag 初始化，按需具体实现
		
		void apply(const Tag &t){	// 将 tag 下放应用到 当前tag 上的操作
			if(!t.status) return;
			if(status){		// $$$ 当前 tag 非空时的应用，按需具体实现
				add+=t.add;
			}
			else	// 当前 tag 为空
				*this=t;
		}
	};
	
	class Info{		// 节点信息类 
	public:
		ll l,r;	// 左右端点
		// $$$ 要维护的具体信息，按需添加
		ll max_dir;
		ll max_lh,max_rh;
		ll max_val,min_val;
		
		Info():l(0),r(0),max_val(0),min_val(0),max_dir(0),max_lh(-INF),max_rh(-INF){} // 无效 Info 初始化，默认将子节点引导向 0 节点，也就是无效节点
		
		Info(const ll &pos,const T &val):l(pos),r(pos){	// 有效 Info 初始化，在 pos 处的数值为 val 的节点
			// $$$ 具体数据初始化实现
			max_dir=0;
			max_lh=max_rh=-val;
			max_val=min_val=val;
		}
		
		friend Info operator+(const Info &lhs,const Info &rhs){	// 重载加法运算符 实现节点信息的合并
			Info res=Info();
			res.l=lhs.l;
			res.r=rhs.r;
			// $$$ 具体合并时的数据维护操作 按需具体实现
			
			res.max_val=max(lhs.max_val,rhs.max_val);
			res.min_val=min(lhs.min_val,rhs.min_val);
			
			res.max_lh=max(lhs.max_lh,rhs.max_lh);
			res.max_lh=max(res.max_lh,lhs.max_val-2*rhs.min_val);
			
			res.max_rh=max(lhs.max_rh,rhs.max_rh);
			res.max_rh=max(res.max_rh,rhs.max_val-2*lhs.min_val);
			
			res.max_dir=max(lhs.max_dir,rhs.max_dir);
			res.max_dir=max(res.max_dir,lhs.max_lh+rhs.max_val);
			res.max_dir=max(res.max_dir,rhs.max_rh+lhs.max_val);
			
			return res;
		}
		
		void apply(const Tag &t){	// 将 tag 应用到当前节点上
			if(!t.status) return;
			// $$$ tag 有效时的具体应用操作 按需具体实现
			max_val+=t.add;
			min_val+=t.add;
			max_rh-=t.add;
			max_lh-=t.add;
		}
	};
	
	// 用 vals 构造线段树 vals 是支持下标访问的容器对象, 例如 std::vector<T>.
	template<typename V>
	H_Segment_tree(ll _n,const V &vals):n(_n),info(4*n+1,Info()),tag(4*n+1,Tag()){
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

void solve(){
	ll n,m,len,rt=0;
	cin>>n>>m;
	len=2*n-2;
	string s;
	cin>>s;
	vector<ll> v(len+1,0);
	for(ll i=1;i<=len;i++){
		v[i]=(s[i-1]=='('?1:-1);
		v[i]+=v[i-1];
	}
	
	H_Segment_tree<ll> sgm(len,v);

	cout<<sgm.query(1,len).max_dir<<endl;
	
	for(ll i=1;i<=m;i++){
		ll l,r;
		cin>>l>>r;
		if(l>r)
			swap(l,r);
		if(s[l-1]=='('){
			s[l-1]=')';
			s[r-1]='(';
			sgm.modify(l,r-1,-2);
		}
		else{
			s[l-1]='(';
			s[r-1]=')';
			sgm.modify(l,r-1,2);
		}
//		OOO
		cout<<sgm.query(1,len).max_dir<<endl;
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
