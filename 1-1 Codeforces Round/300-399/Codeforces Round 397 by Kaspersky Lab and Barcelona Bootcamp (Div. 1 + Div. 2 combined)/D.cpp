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

template <typename T>
class H_Segment_tree{
public:
	class Tag{	//修改标记类
	public:
		bool status;
		// $$$ 要维护的标记内容，按需添加
		ll add;
		
		Tag():status(false){}	// 无效 tag 初始化
		
		Tag(const T &t):status(true){add=t;}	  // $$$ 有效 tag 初始化，按需具体实现
		
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
		ll max_val;
		
		Info():l(0),r(0){} // 无效 Info 初始化，默认将子节点引导向 0 节点，也就是无效节点
		
		Info(const ll &pos,const T &val):l(pos),r(pos){	// 有效 Info 初始化，在 pos 处的数值为 val 的节点
			// $$$ 具体数据初始化实现
			max_val=val;
		}
		
		friend Info operator+(const Info &lhs,const Info &rhs){	// 重载加法运算符 实现节点信息的合并
			Info res=Info();
			res.l=lhs.l;
			res.r=rhs.r;
			// $$$ 具体合并时的数据维护操作 按需具体实现
			res.max_val=max(lhs.max_val,rhs.max_val);
			
			return res;
		}
		
		void apply(const Tag &t){	// 将 tag 应用到当前节点上
			if(!t.status) return;
			// $$$ tag 有效时的具体应用操作 按需具体实现
			max_val+=t.add;
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
	ll n,flag=0;
	cin>>n;
	vector<ll> v(n+1,0);
	vector<ll> pl(n+1,0),pr(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(i>1&&v[i]>v[i-1])
			flag=1;
		while(pr[0]>0&&v[pr[pr[0]]]<=v[i]) pr[0]--;
		pr[++pr[0]]=i;
	}
	for(ll i=n;i>=1;i--){
		while(pl[0]>0&&v[pl[pl[0]]]>=v[i]) pl[0]--;
		pl[++pl[0]]=i;
	}
	
	if(!flag){
//		OOO
		cout<<1<<endl;
		return;
	}
	
//	for(ll i=1;i<=pl[0];i++)
//		cout<<"!!! "<<i<<' '<<pl[i]<<endl;
//	OOO cout<<endl;
//	for(ll i=1;i<=pr[0];i++)
//		cout<<"!!! "<<i<<' '<<pr[i]<<endl;
	
	vector<tuple<ll,ll,ll,ll>> p;
	
	for(ll i=1;i<=n;i++){
		ll val=v[i];
		ll ld,rd,lu,ru,l,r;
		
		l=1,r=pl[0];
		while(l<r){
			ll mid=(l+r)/2;
			if(v[pl[mid]]<v[i]) r=mid;
			else l=mid+1;
		}
		ld=l;
		
		l=1,r=pl[0];
		while(l<r){
			ll mid=(l+r+1)/2;
			if(pl[mid]<i) l=mid;
			else r=mid-1;
		}
		rd=l;
		
		l=1,r=pr[0];
		while(l<r){
			ll mid=(l+r+1)/2;
			if(v[pr[mid]]>v[i]) l=mid;
			else r=mid-1;
		}
		ru=l;
		
		l=1,r=pr[0];
		while(l<r){
			ll mid=(l+r)/2;
			if(pr[mid]>i) r=mid;
			else l=mid+1;
		}
		lu=l;
		
//		cout<<i<<' '<<pl[ld]<<' '<<pl[rd]<<' '<<pr[lu]<<' '<<pr[ru]<<endl;
		
		if(pr[lu]>i&&pl[rd]<i&&v[pr[ru]]>v[i]&&v[pl[rd]]<v[i]&&ld<=rd&&lu<=ru){
			
//			cout<<i<<' '<<pl[ld]<<' '<<pl[rd]<<' '<<pr[lu]<<' '<<pr[ru]<<endl;
			
			p.emplace_back(ld,1,lu,ru);
			p.emplace_back(rd+1,-1,lu,ru);
		}
	}
	
	ll sz=max(pl[0],pr[0])+1;
	
	H_Segment_tree<ll> sgm(sz,vector<ll>(sz+1,0));
	
	sort(p.begin(),p.end());
	
	ll ans=0;
	
	for(auto [q,k,l,r]:p){
		sgm.modify(l,r,k);
//		cout<<l<<' '<<r<<' '<<k<<' '<<sgm.query(1,sz).max_val<<endl;
		ans=max(ans,sgm.query(1,sz).max_val);
	}
//	OOO
	cout<<ans+2<<endl;
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
