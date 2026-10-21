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

class H_Dsu{
public:
	ll n;

	class Info{
	public:
		ll fa,siz;

		Info():fa(0),siz(0){}
		Info(ll _fa):fa(_fa),siz(1){}

		friend Info operator+(const Info &a,const Info &b){
			Info res;
			res.fa=a.fa;
			res.siz=a.siz+b.siz;
			return res;
		}
	};

	vector<Info> v;

	H_Dsu(ll _n):n(_n){
		v.assign(n+1,Info());
		for(ll i=1;i<=n;i++)
			v[i]=Info(i);
	}

	ll Fa(ll x){
		if(v[x].fa==x)
			return x;
		return v[x].fa=Fa(v[x].fa);
	}

	void merge(ll x,ll y){
		ll fx=Fa(x),fy=Fa(y);
		if(fx==fy)
			return;
		if(v[fx].siz<v[fy].siz)
			swap(fx,fy);
		v[fy].fa=fx;
		v[fx]=v[fx]+v[fy];
	}
};

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
			if(!t.status)
				return;
			*this=t;
		}
	};

	class Info{
	public:
		ll l,r,pos;
		T mx;

		Info():l(0),r(0),pos(0),mx(0){}
		Info(const ll &_pos,const T &val):l(_pos),r(_pos),pos(_pos),mx(val){}

		friend Info operator+(const Info &lhs,const Info &rhs){
			Info res;
			res.l=lhs.l;
			res.r=rhs.r;
			if(lhs.mx>=rhs.mx){
				res.mx=lhs.mx;
				res.pos=lhs.pos;
			}
			else{
				res.mx=rhs.mx;
				res.pos=rhs.pos;
			}
			return res;
		}

		void apply(const Tag &t){
			if(!t.status)
				return;
			mx=t.val;
			pos=l;
		}
	};

	template<typename V>
	H_Segment_tree(ll _n,const V &vals):n(_n),tag(4*n+1,Tag()),info(4*n+1,Info()){
		build_tree(1,1,n,vals);
	}

	void modify(ll ql,ll qr,const Tag &_key){
		if(ql<1||qr>n||ql>qr){
			cout<<"Error form Segment_tree :: modify() -> Range_Error "<<endl;
		}
		if(!_key.status)
			return;
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
		if(ql<=mid)
			modify(o*2,ql,qr,_key);
		if(qr>=mid+1)
			modify(o*2+1,ql,qr,_key);
		cur=info[o*2]+info[o*2+1];
	}

	Info query(ll o,ll ql,ll qr){
		Info &cur=info[o];
		ll l=cur.l,r=cur.r;
		if(l>=ql&&r<=qr)
			return cur;

		push_down(o);
		ll mid=(l+r)/2;
		if(ql<=mid&&qr>=mid+1)
			return query(o*2,ql,qr)+query(o*2+1,ql,qr);
		else if(ql<=mid)
			return query(o*2,ql,qr);
		else
			return query(o*2+1,ql,qr);
	}
};

void solve(){
	ll n,m,q;
	cin>>n>>m>>q;
	vector<ll> val(n+1),del(m+1);
	vector<pair<ll,ll>> edg(m+1),que(q+1);
	for(ll i=1;i<=n;i++)
		cin>>val[i];
	for(ll i=1;i<=m;i++)
		cin>>edg[i].first>>edg[i].second;
	for(ll i=1;i<=q;i++){
		cin>>que[i].first>>que[i].second;
		if(que[i].first==2)
			del[que[i].second]=1;
	}

	H_Dsu dsu(n);
	vector<ll> root(n+1),bel(q+1);
	vector<array<ll,2>> eg(2*n+1);
	for(ll i=1;i<=n;i++)
		root[i]=i;
	ll tot=n;
	auto merge=[&](ll u,ll v){
		ll fx=dsu.Fa(u),fy=dsu.Fa(v);
		if(fx==fy)
			return;
		eg[++tot]={root[fx],root[fy]};
		dsu.merge(fx,fy);
		root[dsu.Fa(fx)]=tot;
	};

	for(ll i=1;i<=m;i++)
		if(!del[i])
			merge(edg[i].first,edg[i].second);
	for(ll i=q;i>=1;i--){
		ll typ=que[i].first,x=que[i].second;
		if(typ==2)
			merge(edg[x].first,edg[x].second);
		else
			bel[i]=root[dsu.Fa(x)];
	}

	vector<ll> lft(2*n+1),rgt(2*n+1),ord(n+1);
	ll cnt=0;
	stack<pair<ll,ll>> stk;
	for(ll i=1;i<=n;i++){
		if(dsu.Fa(i)!=i)
			continue;
		stk.emplace(root[i],0);
		while(!stk.empty()){
			auto [u,vis]=stk.top();
			stk.pop();
			if(u<=n){
				lft[u]=rgt[u]=++cnt;
				ord[cnt]=val[u];
			}
			else if(!vis){
				stk.emplace(u,1);
				stk.emplace(eg[u][1],0);
				stk.emplace(eg[u][0],0);
			}
			else{
				lft[u]=lft[eg[u][0]];
				rgt[u]=rgt[eg[u][1]];
			}
		}
	}

	H_Segment_tree<ll> sgm(n,ord);
	for(ll i=1;i<=q;i++){
		if(que[i].first!=1)
			continue;
		ll u=bel[i];
		auto ans=sgm.query(lft[u],rgt[u]);
		cout<<ans.mx<<'\n';
		if(ans.mx)
			sgm.modify(ans.pos,ans.pos,H_Segment_tree<ll>::Tag(0));
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
