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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

struct Sgm_tree{
	
	struct Tag{
		bool status;
		ll val;
		
		Tag():status(0){}
		Tag(ll x):status(1),val(x){}
		
		void apply(const Tag &t){
			if(status){
				*this=Tag(t.val);
			}
			else
				*this=t;
		}
	};
	
	struct Info{
		ll l,r,sum;
		Info(){
			l=r=sum=-1;
		}
		Info(const ll &pos,const ll &x){
			l=r=pos;
			sum=x;
		}
		friend Info operator+(const Info &lhs,const Info &rhs){
			Info res=Info();
			
			res.l=lhs.l;
			res.r=rhs.r;
			res.sum=lhs.sum+rhs.sum;
			
			return res;
		}
		void apply(const Tag &t){
			sum=(r-l+1)*t.val;
		}
	};
	
	ll n;
	vector<Info> info;
	vector<Tag> tag;
	
	template <typename V>
	Sgm_tree(const V &values):n(values.size()-1),info(4*n,Info()),tag(4*n,Tag()){
		build_tree(1,1,n,values);
	}
	
	template<typename V>
	void build_tree(ll o,ll l,ll r,const V &values){
		if(l==r){
			info[o]=Info(l,values[l]);
			return;
		}
		ll mid=(l+r)/2;
		build_tree(o*2,l,mid,values);
		build_tree(o*2+1,mid+1,r,values);
		info[o]=info[o*2]+info[o*2+1];
	}
	
	void push_down(ll o){
		if(tag[o].status){
			info[o*2].apply(tag[o]);
			info[o*2+1].apply(tag[o]);
			tag[o*2].apply(tag[o]);
			tag[o*2+1].apply(tag[o]);
			
			tag[o]=Tag();
		}
	}
	
	void modify(ll ql,ll qr,ll val){
		modify(1,ql,qr,Tag(val));
	}
	
	void modify(ll o,ll ql,ll qr,const Tag &t){
		if(ql>qr) return;
		Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(l>=ql&&r<=qr){
			info[o].apply(t);
			tag[o].apply(t);
			return;
		}
		push_down(o);
		ll mid=(l+r)/2;
		if(ql<=mid) modify(o*2,ql,qr,t);
		if(qr>=mid+1) modify(o*2+1,ql,qr,t);
		info[o]=info[o*2]+info[o*2+1];
	}
	
	ll query(ll ql,ll qr){
		return query(1,ql,qr).sum;
	}
	
	Info query(ll o,ll ql,ll qr){
		Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(l>=ql&&r<=qr){
//			OOO cout<<"!!!"<<endl;
			return info[o];
		}
		push_down(o);
		ll mid=(l+r)/2;
		if(ql<=mid&&qr>=mid+1) return query(o*2,ql,qr)+query(o*2+1,ql,qr);
		if(ql<=mid) return query(o*2,ql,qr);
		if(qr>=mid+1) return query(o*2+1,ql,qr);
	}
};

void solve(){
	ll n,m,q;
	cin>>n>>m;
	vector<ll> v(n+1),op(m+1),l(m+1),r(m+1);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}	
	for(ll i=1;i<=m;i++){
		cin>>op[i]>>l[i]>>r[i];
		if(l[i]>r[i]) swap(l[i],r[i]);
//		cout<<"!!!"<<endl;
	}
		
	cin>>q;
	
	auto check=[&](ll x)->bool{
		vector<ll> tmp(n+1);
		for(ll i=1;i<=n;i++){
			if(v[i]>=x)
				tmp[i]=1;
		}
		Sgm_tree sgt(tmp);
		for(ll i=1;i<=m;i++){
//			OOO OOO cout<<i<<endl;
//			for(ll i=1;i<=n;i++) cout<<sgt.query(i,i)<<' ';
//			cout<<endl;
			if(op[i]==0){
				ll sum1=sgt.query(l[i],r[i]);
				sgt.modify(r[i]-sum1+1,r[i],1);
				sgt.modify(l[i],r[i]-sum1,0);
			}
			else{
				ll sum1=sgt.query(l[i],r[i]);
				sgt.modify(l[i],l[i]+sum1-1,1);
				sgt.modify(l[i]+sum1,r[i],0);
			}
			
		}
		return sgt.query(q,q);
	};
	
	ll L=1,R=n;
	while(L<R){
		ll mid=(L+R+1)/2;
//		cout<<mid<<' '<<check(mid)<<endl;
		if(check(mid)){
			L=mid;
		}
		else{
			R=mid-1;
		}
	}
//	OOO
	cout<<L<<endl;
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
