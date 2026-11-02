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

struct LCT {
	vector<array<ll,2>> ch;
	vector<ll> fa, rev, val, xr, tag, cnt, stk;

	LCT(ll n): ch(n), fa(n), rev(n), val(n), xr(n), tag(n), cnt(n) {}

	bool isroot(ll x){
		return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
	}

	void push_up(ll x){
		xr[x]=xr[ch[x][0]]^val[x]^xr[ch[x][1]];
		cnt[x]=cnt[ch[x][0]]+tag[x]+cnt[ch[x][1]];
	}

	void lazy_reverse(ll x){
		if (!x)
			return;
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}

	void push_down(ll x){
		if (!rev[x])
			return;
		lazy_reverse(ch[x][0]);
		lazy_reverse(ch[x][1]);
		rev[x]=0;
	}

	void rotate(ll x){
		ll y=fa[x], z=fa[y], k=(ch[y][1]==x);
		if (!isroot(y))
			ch[z][ch[z][1]==y]=x;
		fa[x]=z;
		ch[y][k]=ch[x][k^1];
		if (ch[y][k])
			fa[ch[y][k]]=y;
		ch[x][k^1]=y;
		fa[y]=x;
		push_up(y);
		push_up(x);
	}

	void splay(ll x){
		stk.clear();
		ll y=x;
		stk.emplace_back(y);
		while (!isroot(y)) {
			y=fa[y];
			stk.emplace_back(y);
		}
		while (!stk.empty()) {
			push_down(stk.back());
			stk.pop_back();
		}
		while (!isroot(x)) {
			y=fa[x];
			ll z=fa[y];
			if (!isroot(y))
				rotate((ch[y][1]==x)==(ch[z][1]==y)?y:x);
			rotate(x);
		}
	}

	void access(ll x){
		for (ll y=0; x; y=x,x=fa[x]) {
			splay(x);
			ch[x][1]=y;
			if (y)
				fa[y]=x;
			push_up(x);
		}
	}

	void makeroot(ll x){
		access(x);
		splay(x);
		lazy_reverse(x);
	}

	ll findroot(ll x){
		access(x);
		splay(x);
		push_down(x);
		while (ch[x][0]) {
			x=ch[x][0];
			push_down(x);
		}
		splay(x);
		return x;
	}

	void split(ll x,ll y){
		makeroot(x);
		access(y);
		splay(y);
	}

	void link(ll x,ll y){
		makeroot(x);
		fa[x]=y;
	}

	void cut(ll x,ll y){
		split(x,y);
		if (ch[y][0]==x && !ch[x][1]) {
			ch[y][0]=0;
			fa[x]=0;
			push_up(y);
		}
	}
};

void solve(){
	ll n,q;
	cin>>n>>q;
	ll lim=3*n+5, tot=n;
	LCT lct(lim);
	vector<array<ll,2>> eg(lim);
	vector<ll> vs,es;

	auto dfs=[&](this auto &&self,ll x)->void{
		if (!x)
			return;
		lct.push_down(x);
		if (x<=n)
			vs.emplace_back(x);
		else
			es.emplace_back(x);
		self(lct.ch[x][0]);
		self(lct.ch[x][1]);
	};

	while (q--) {
		ll u,v,w;
		cin>>u>>v>>w;
		if (lct.findroot(u)!=lct.findroot(v)) {
			ll e=++tot;
			lct.val[e]=lct.xr[e]=w;
			eg[e]={u,v};
			lct.link(u,e);
			lct.link(e,v);
			cout<<"YES\n";
			continue;
		}

		lct.split(u,v);
		if (lct.cnt[v] || (lct.xr[v]^w)!=1) {
			cout<<"NO\n";
			continue;
		}

		vs.clear();
		es.clear();
		dfs(v);
		for (auto e:es) {
			auto [a,b]=eg[e];
			lct.cut(a,e);
			lct.cut(e,b);
		}

		ll c=++tot;
		lct.tag[c]=lct.cnt[c]=1;
		for (auto x:vs)
			lct.link(x,c);
		cout<<"YES\n";
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
