#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

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

const ull base1=137;
ull bexp1[500001];

const ull base2=131;
ull bexp2[500001];

void init(){
	ll n=5e5;
	bexp1[0]=1;
	for(ll i=1;i<=n;i++)
		bexp1[i]=bexp1[i-1]*base1;
	
	bexp2[0]=1;
	for(ll i=1;i<=n;i++)
		bexp2[i]=bexp2[i-1]*base2;
}

/********************************************************************************************/

template <typename T>
class H_Segment_tree{
public:
	class Tag{	//修改标记类
	public:
		bool status;
		ll set_to;
		// $$$ 要维护的标记内容，按需添加
		
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
		ll l,r;	// 左右端点
		ull l_hash1,l_hash2,r_hash1,r_hash2;
		// $$$ 要维护的具体信息，按需添加
		
		Info():l(0),r(0){} // 无效 Info 初始化，默认将子节点引导向 0 节点，也就是无效节点
		
		Info(const ll &pos,const T &val):l(pos),r(pos){	// 有效 Info 初始化，在 pos 处的数值为 val 的节点
			l_hash1=r_hash1=val;
			l_hash2=r_hash2=val;
			// $$$ 具体数据初始化实现
		}
		
		friend Info operator+(const Info &lhs,const Info &rhs){	// 重载加法运算符 实现节点信息的合并
			Info res=Info();
			res.l=lhs.l;
			res.r=rhs.r;
			// $$$ 具体合并时的数据维护操作 按需具体实现
			
			ll l_len=lhs.r-lhs.l+1;
			ll r_len=rhs.r-rhs.l+1;
			
			res.l_hash1=(lhs.l_hash1*bexp1[r_len])+rhs.l_hash1;
			res.l_hash2=(lhs.l_hash2*bexp2[r_len])+rhs.l_hash2;
			
			res.r_hash1=(rhs.r_hash1*bexp1[l_len])+lhs.r_hash1;
			res.r_hash2=(rhs.r_hash2*bexp2[l_len])+lhs.r_hash2;
			
			return res;
		}
		
		void apply(const Tag &t){	// 将 tag 应用到当前节点上
			if(!t.status) return;
			// $$$ tag 有效时的具体应用操作 按需具体实现
			l_hash1=r_hash1=t.set_to;
			l_hash2=r_hash2=t.set_to;
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

/********************************************************************************************/

void solve(){
	ll n,ans=0;
	cin>>n;
	H_Segment_tree<ull> sgm(n,vector<ll>(n+1,0));
	
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	for(ll i=1;i<=n&&ans==0;i++){
		ll len=min(v[i]-1,n-v[i]);
		sgm.modify(v[i],v[i],H_Segment_tree<ull>::Tag(1));
		if(len>=1){
			auto ck=sgm.query(v[i]-len,v[i]+len);
			if(ck.l_hash1!=ck.r_hash1&&ck.l_hash2!=ck.r_hash2)
				ans=1;
		}
	}
	if(ans)
		cout<<"Y"<<endl;
	else
		cout<<"N"<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
