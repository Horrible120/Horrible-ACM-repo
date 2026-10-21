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

struct Seg{
	ll v=0,l=0,r=0;

	bool operator<(const Seg &a) const{
		return v<a.v;
	}
};

template <typename T>
class H_Segment_tree{
public:
	class Info{
	public:
		ll l=0,r=0,sum=0;
		Seg lmx,rmx,mx,lmn,rmn,mn;

		Info()=default;

		Info(const ll &pos,const T &val):l(pos),r(pos),sum(val){
			lmx=rmx=mx=lmn=rmn=mn={val,pos,pos};
		}

		friend Info operator+(const Info &lhs,const Info &rhs){
			Info res;
			res.l=lhs.l;
			res.r=rhs.r;
			res.sum=lhs.sum+rhs.sum;

			res.lmx=max(lhs.lmx,Seg{lhs.sum+rhs.lmx.v,lhs.l,rhs.lmx.r});
			res.rmx=max(rhs.rmx,Seg{rhs.sum+lhs.rmx.v,lhs.rmx.l,rhs.r});
			res.mx=max({lhs.mx,rhs.mx,Seg{lhs.rmx.v+rhs.lmx.v,lhs.rmx.l,rhs.lmx.r}});

			res.lmn=min(lhs.lmn,Seg{lhs.sum+rhs.lmn.v,lhs.l,rhs.lmn.r});
			res.rmn=min(rhs.rmn,Seg{rhs.sum+lhs.rmn.v,lhs.rmn.l,rhs.r});
			res.mn=min({lhs.mn,rhs.mn,Seg{lhs.rmn.v+rhs.lmn.v,lhs.rmn.l,rhs.lmn.r}});
			return res;
		}
	};

	template<typename V>
	H_Segment_tree(ll _n,const V &vals):n(_n),info(4*n+1){
		build_tree(1,1,n,vals);
	}

	void modify(ll pos,const T &val){
		modify(1,pos,val);
	}

	Info query(ll ql,ll qr){
		return query(1,ql,qr);
	}

private:
	ll n;
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

	void modify(ll o,ll pos,const T &val){
		Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(l==r){
			cur=Info(l,val);
			return;
		}

		ll mid=(l+r)/2;
		if(pos<=mid)
			modify(o*2,pos,val);
		else
			modify(o*2+1,pos,val);

		cur=info[o*2]+info[o*2+1];
	}

	Info query(ll o,ll ql,ll qr){
		const Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(ql<=l&&r<=qr)
			return cur;

		ll mid=(l+r)/2;
		if(qr<=mid)
			return query(o*2,ql,qr);
		if(ql>mid)
			return query(o*2+1,ql,qr);
		return query(o*2,ql,qr)+query(o*2+1,ql,qr);
	}
};

struct Node{
	ll v,l,r,x,y,t;

	bool operator<(const Node &a) const{
		return v<a.v;
	}
};

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++)
		cin>>a[i];

	H_Segment_tree<ll> tr(n,a);
	ll m;
	cin>>m;
	while(m--){
		ll op,l,r;
		cin>>op>>l>>r;
		if(op==0){
			tr.modify(l,r);
			continue;
		}

		ll k,ans=0;
		cin>>k;
		std::priority_queue<Node> q;
		auto add=[&](ll l,ll r,ll t){
			if(l>r)
				return;

			auto res=tr.query(l,r);
			Seg cur=t?res.mn:res.mx;
			ll v=t?-cur.v:cur.v;
			if(v>0)
				q.push({v,l,r,cur.l,cur.r,t});
		};

		add(l,r,0);
		for(ll i=1;i<=k&&!q.empty();i++){
			Node cur=q.top();
			q.pop();
			ans+=cur.v;

			add(cur.l,cur.x-1,cur.t);
			add(cur.x,cur.y,cur.t^1);
			add(cur.y+1,cur.r,cur.t);
		}
		cout<<ans<<'\n';
	}
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
