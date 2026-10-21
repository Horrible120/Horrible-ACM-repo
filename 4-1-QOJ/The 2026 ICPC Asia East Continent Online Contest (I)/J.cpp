#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

template <typename T>
class H_Segment_tree{
public:
	class Tag{
	public:
		bool status;
		T val;

		Tag():status(false),val(0){}
		Tag(const T &t):status(true),val(t){}

		void apply(const Tag &t){
			if(!t.status) return;
			*this=t;
		}
	};

	class Info{
	public:
		ll l,r,sum;

		Info():l(0),r(0),sum(0){}
		Info(const ll &pos,const T &val):l(pos),r(pos),sum(val){}

		friend Info operator+(const Info &lhs,const Info &rhs){
			Info res;
			res.l=lhs.l;
			res.r=rhs.r;
			res.sum=lhs.sum+rhs.sum;
			return res;
		}

		void apply(const Tag &t){
			if(!t.status) return;
			sum=(r-l+1)*t.val;
		}
	};

	template<typename V>
	H_Segment_tree(ll _n,const V &vals):n(_n),tag(4*n+1,Tag()),info(4*n+1,Info()){
		build_tree(1,1,n,vals);
	}

	void modify(ll op,ll p,ll k){
		modify(1,p,op<=2,!(op&1),k);
	}

	void get_str(string &s){
		get_str(1,s);
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
		if(!tag[o].status) return;
		info[o*2].apply(tag[o]);
		info[o*2+1].apply(tag[o]);
		tag[o*2].apply(tag[o]);
		tag[o*2+1].apply(tag[o]);
		tag[o]=Tag();
	}

	void modify(ll o,ll p,ll d,ll z,ll &k){
		Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(!k||(d?r<p:l>p)) return;
		if(k==1&&(d?l>=p:r<=p)&&cur.sum==(r-l+1)*(1-z)){
			Tag t(z);
			cur.apply(t);
			tag[o].apply(t);
			return;
		}
		if(l==r){
			ll x=k+(cur.sum^z);
			Tag t((x&1)^z);
			cur.apply(t);
			tag[o].apply(t);
			k=x>>1;
			return;
		}
		push_down(o);
		if(d){
			modify(o*2,p,d,z,k);
			modify(o*2+1,p,d,z,k);
		}
		else{
			modify(o*2+1,p,d,z,k);
			modify(o*2,p,d,z,k);
		}
		cur=info[o*2]+info[o*2+1];
	}

	void get_str(ll o,string &s){
		ll l=info[o].l,r=info[o].r;
		if(l==r){
			s[l]=info[o].sum?'H':'N';
			return;
		}
		push_down(o);
		get_str(o*2,s);
		get_str(o*2+1,s);
	}
};

void solve(){
	ll n,q;
	string s;
	cin>>n>>q>>s;
	s=" "+s;
	vector<ll> a(n+1,0);
	for(ll i=1;i<=n;i++) a[i]=(s[i]=='H');
	H_Segment_tree<ll> seg(n,a);
	while(q--){
		ll op,p,k;
		cin>>op>>p>>k;
		seg.modify(op,p,k);
	}
	seg.get_str(s);
	cout<<s.substr(1)<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

//	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
