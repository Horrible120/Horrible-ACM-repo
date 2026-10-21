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
ll x;

template <typename T>
class H_Segment_tree{
public:
	class Tag{	//修改标记类
	public:
		bool status;
		// $$$ 要维护的标记内容，按需添加
		ll set_to;
		
		Tag():status(false){}	// 无效 tag 初始化
		
		Tag(const T &t):status(true),set_to(t){}	  // $$$ 有效 tag 初始化，按需具体实现
		
		void apply(const Tag &t){	// 将 tag 下放应用到 当前tag 上的操作
			if(!t.status) return;
			if(status){		// $$$ 当前 tag 非空时的应用，按需具体实现
				set_to=t.set_to;
			}
			else	// 当前 tag 为空
				*this=t;
		}
	};
	
	class Info{		// 节点信息类 
	public:
		ll xx;
		ll l,r;	// 左右端点
		// $$$ 要维护的具体信息，按需添加
		ll cnt;
		vector<pll> lor,ror;
		
		Info():l(0),r(0),lor(21),ror(21){} // 无效 Info 初始化，默认将子节点引导向 0 节点，也就是无效节点
		
		Info(const ll &pos,const T &val,ll _x):l(pos),r(pos),lor(21),ror(21){	// 有效 Info 初始化，在 pos 处的数值为 val 的节点
			// $$$ 具体数据初始化实现
			lor[0]=make_pair(1,val);
			ror[0]=make_pair(1,val);
			xx=_x;
			if(val>=xx)
				cnt=1;
			else
				cnt=0;
		}
		
		friend Info operator+(const Info &lhs,const Info &rhs){	// 重载加法运算符 实现节点信息的合并
			Info res=Info();
			res.l=lhs.l;
			res.r=rhs.r;
			res.xx=lhs.xx;
			// $$$ 具体合并时的数据维护操作 按需具体实现
			
			res.cnt=lhs.cnt+rhs.cnt;
			
			for(ll l=0,r=20,tmp=0;l<21;l++){
				if(lhs.ror[l].first==0)
					continue;
				
				while(r>=0&&(rhs.lor[r].first==0||(rhs.lor[r].second|lhs.ror[l].second)>=res.xx))
					tmp+=rhs.lor[r].first,r--;
				res.cnt+=lhs.ror[l].first*tmp;
			}
			
			{
				ll vor=0,cnt=0,l=0;
				for(ll i=0;i<21;i++)
					if((vor|lhs.lor[i].second)==vor)
						cnt+=lhs.lor[i].first;
					else if(cnt>0){
						res.lor[l++]=make_pair(cnt,vor);
						vor|=lhs.lor[i].second;
						cnt=lhs.lor[i].first;
					}
					else{
						vor|=lhs.lor[i].second;
						cnt=lhs.lor[i].first;
					}
				
				for(ll i=0;i<21;i++)
					if((vor|rhs.lor[i].second)==vor)
						cnt+=rhs.lor[i].first;
					else if(cnt>0){
						res.lor[l++]=make_pair(cnt,vor);
						vor|=rhs.lor[i].second;
						cnt=rhs.lor[i].first;
					}
					else{
						vor|=rhs.lor[i].second;
						cnt=rhs.lor[i].first;
					}
					if(cnt>0)
						res.lor[l++]=make_pair(cnt,vor);
			}
			
			{
				ll vor=0,cnt=0,r=0;
				for(ll i=0;i<21;i++)
					if((vor|rhs.ror[i].second)==vor)
						cnt+=rhs.ror[i].first;
					else if(cnt>0){
						res.ror[r++]=make_pair(cnt,vor);
						vor|=rhs.ror[i].second;
						cnt=rhs.ror[i].first;
					}
					else{
						vor|=rhs.ror[i].second;
						cnt=rhs.ror[i].first;
					}
				
				for(ll i=0;i<21;i++)
					if((vor|lhs.ror[i].second)==vor)
						cnt+=lhs.ror[i].first;
					else if(cnt>0){
						res.ror[r++]=make_pair(cnt,vor);
						vor|=lhs.ror[i].second;
						cnt=lhs.ror[i].first;
					}
					else{
						vor|=lhs.ror[i].second;
						cnt=lhs.ror[i].first;
					}
				if(cnt>0)
					res.ror[r++]=make_pair(cnt,vor);
			}
			
			return res;
		}
		
		void apply(const Tag &t){	// 将 tag 应用到当前节点上
			if(!t.status) return;
			// $$$ tag 有效时的具体应用操作 按需具体实现
			lor[0]=make_pair(1,t.set_to);
			ror[0]=make_pair(1,t.set_to);
			if(t.set_to>=xx)
				cnt=1;
			else
				cnt=0;
		}
	};
	
	// 用 vals 构造线段树 vals 是支持下标访问的容器对象, 例如 std::vector<T>.
	template<typename V>
	H_Segment_tree(ll _n,const V &vals,ll _x):x(_x),n(_n),info(4*n+1,Info()),tag(4*n+1,Tag()){
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
	ll n,x;
	vector<Tag> tag;
	vector<Info> info;
	
	template<typename V>
	void build_tree(ll o,ll l,ll r,const V &vals){
		if(l==r){
			info[o]=Info(l,vals[l],x);
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
	ll n,m,x;
	cin>>n>>m>>x;
	
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	H_Segment_tree<ll> sgm(n,v,x);
	
	for(ll i=1,op,l,r;i<=m;i++){
		cin>>op>>l>>r;
		if(op==1)
			sgm.modify(l,l,r);
		else
			cout<<sgm.query(l,r).cnt<<endl;
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
