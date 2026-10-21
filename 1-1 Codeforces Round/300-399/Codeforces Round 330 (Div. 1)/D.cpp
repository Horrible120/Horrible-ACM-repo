#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef int ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

const ll nn=1e6;
vector<ll> minp(nn+1,0),prm,iv(nn+1,0);

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

/********************************************************************************************/

template <typename T>
class H_Segment_tree{
public:
	class Tag{	//修改标记类
	public:
		bool status;
		// $$$ 要维护的标记内容，按需添加
		
		
		Tag():status(false){}	// 无效 tag 初始化
		
		Tag(const T &t):status(true){}	  // $$$ 有效 tag 初始化，按需具体实现
		
		void apply(const Tag &t){	// 将 tag 下放应用到 当前tag 上的操作
			if(!t.status) return;
			if(status){		// $$$ 当前 tag 非空时的应用，按需具体实现
				
			}
			else	// 当前 tag 为空
				*this=t;
		}
	};
	
	class Info{		// 节点信息类 
	public:
		ll l,r;	// 左右端点
		// $$$ 要维护的具体信息，按需添加
		ll pdt;
		
		Info():l(0),r(0),pdt(1){} // 无效 Info 初始化，默认将子节点引导向 0 节点，也就是无效节点
		
		Info(const ll &pos,const T &val):l(pos),r(pos),pdt(val){	// 有效 Info 初始化，在 pos 处的数值为 val 的节点
			// $$$ 具体数据初始化实现
		}
		
		friend Info operator+(const Info &lhs,const Info &rhs){	// 重载加法运算符 实现节点信息的合并
			Info res=Info();
			res.l=lhs.l;
			res.r=rhs.r;
			// $$$ 具体合并时的数据维护操作 按需具体实现
			res.pdt=(long long)lhs.pdt*rhs.pdt%Mod;
			return res;
		}
		
		void apply(const Tag &t){	// 将 tag 应用到当前节点上
			if(!t.status) return;
			// $$$ tag 有效时的具体应用操作 按需具体实现
			
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

void init(){	
	for(ll i=2;i<=nn;i++){
		if(!minp[i]){
			minp[i]=i;
			prm.emplace_back(i);
		}
		for(auto j:prm){
			if(j>minp[i]||i*j>nn){
				break;
			}
			minp[i*j]=j;
		}
	}
	iv[1]=1;
	for(ll i=2;i<=nn;i++){
		iv[i]=inv(i);
	}
}

class Info{
public:
	ll pdt,lhs,rhs;
	Info():pdt(1),lhs(0),rhs(0){}
	Info(const ll _a):lhs(0),rhs(0),pdt(_a){}
	
	friend Info operator + (const Info _l,const Info _r){
		Info res;
		res.pdt=(long long)_l.pdt*_r.pdt%Mod;
		return res;
	}
};

void solve(){
	init();
	
	ll n,q,tot=0;
	
	cin>>n;
	
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector<Info> tr(n*100+1,Info());
	
	auto modify=[&](auto &&self,ll &u,ll pre,ll l,ll r,ll pos,ll key)->void{
		u=++tot;
		tr[u]=tr[pre];
		if(l==r){
//			cout<<"!!! "<<l<<' '<<tr[u].pdt<<endl;
			tr[u].pdt=(long long)tr[u].pdt*key%Mod;
			return;
		}
		
		ll mid=l+r>>1;
		if(pos<=mid){
			self(self,tr[u].lhs,tr[pre].lhs,l,mid,pos,key);
		}else{
			self(self,tr[u].rhs,tr[pre].rhs,mid+1,r,pos,key);
		}
		tr[u].pdt=(long long)tr[tr[u].lhs].pdt*tr[tr[u].rhs].pdt%Mod;
	};
	
	auto query=[&](auto &&self,ll u,ll l,ll r,ll s,ll t)->ll{
		if(!u) return 1ll;
		if(l>=s&&r<=t){
			return tr[u].pdt;
		}
		ll mid=l+r>>1;
		long long res=1;
		if(mid>=s){
			res=res*self(self,tr[u].lhs,l,mid,s,t);
		}
		if(mid+1<=t){
			res=res*self(self,tr[u].rhs,mid+1,r,s,t);
		}
		return res%Mod;
	};
	
	vector<ll> lst(nn+1,0),roots(n+1,0);
	for(ll i=1;i<=n;i++){
		roots[i]=roots[i-1];
		ll tmp=v[i];
		long long pdct=1;
		unordered_map<ll,ll> trans;
		while(tmp>1){
			ll tmpf=minp[tmp];
			
//			cout<<">>> "<<i<<' '<<tmpf<<' '<<lst[tmpf]/*<<' '<<iv[tmpf]*/<<endl;
			
			if(lst[tmpf]){
//				modify(modify,roots[i],roots[i],1,n,lst[tmpf],(long long)iv[tmpf-1]*tmpf%Mod);
				if(trans[lst[tmpf]]){
					trans[lst[tmpf]]=(long long)trans[lst[tmpf]]*iv[tmpf-1]%Mod*tmpf%Mod;
				}else{
					trans[lst[tmpf]]=(long long)iv[tmpf-1]*tmpf%Mod;
				}
			}
			
			lst[tmpf]=i;
			pdct=pdct*(tmpf-1)%Mod*iv[tmpf]%Mod;
			
			while(tmp%tmpf==0){
				tmp/=tmpf;
			}
		}
		
		for(auto [pos,val]:trans){
			modify(modify,roots[i],roots[i],1,n,pos,val);
		}
		
		modify(modify,roots[i],roots[i],1,n,i,pdct);
		
//		cout<<">>>>>  [ "<<i<<" ]"<<endl;
//		for(ll j=1;j<=n;j++){
//			cout<<"    "<<j<<' '<<query(query,roots[i],1,n,j,j)<<endl;
//		}
	}
	
	H_Segment_tree<ll> sgm(n,v);
	
	cin>>q;
	
	for(ll i=1;i<=q;i++){
		ll ql,qr;
		cin>>ql>>qr;
//		OOO
		cout<<(long long)query(query,roots[qr],1,n,ql,qr)*sgm.query(ql,qr).pdt%Mod<<endl;
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
