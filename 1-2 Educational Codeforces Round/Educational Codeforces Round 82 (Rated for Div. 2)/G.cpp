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

void solve(){
	ll n;
	cin >> n;
	vector<vector<ll>> eg(n+1);
	for (ll i=1;i<n;i++) {
		ll u,v;
		cin >> u >> v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	vector<ll> val(n+1);
	for (ll i=1;i<=n;i++)
		cin >> val[i];

	vector<ll> siz(n+1),del(n+1);
	vector<ll> dep(n+1),sum(n+1),pre(n+1),suf(n+1);
	ll ans=-INF;
	auto getsiz=[&](this auto &&self,ll u,ll p)->void{
		siz[u]=1;
		for (auto v:eg[u])
			if (!del[v] && v!=p) {
				self(v,u);
				siz[u]+=siz[v];
			}
	};
	auto center=[&](this auto &&self,ll u,ll p,ll tot)->ll{
		for (auto v:eg[u])
			if (!del[v] && v!=p && siz[v]>tot/2)
				return self(v,u,tot);
		return u;
	};

	auto calc=[&](ll c)->void{
		dep[c]=0;
		sum[c]=pre[c]=val[c];
		suf[c]=0;
		ans=max(ans,val[c]);
		vector<vector<ll>> grp;
		ll lim=0;
		auto collect=[&](this auto &&self,ll u,ll p,vector<ll> &vec)->void{
			dep[u]=dep[p]+1;
			sum[u]=sum[p]+val[u];
			pre[u]=pre[p]+(dep[u]+1)*val[u];
			suf[u]=suf[p]+sum[u]-val[c];
			lim=max(lim,dep[u]);
			ans=max(ans,pre[u]);
			vec.emplace_back(u);
			for (auto v:eg[u])
				if (!del[v] && v!=p)
					self(v,u,vec);
		};
		for (auto v:eg[c]) {
			if (del[v])
				continue;
			vector<ll> vec;
			collect(v,c,vec);
			grp.emplace_back(move(vec));
		}

		vector<ll> tr(4*(lim+1));
		auto eval=[&](ll id,ll x)->ll{
			return sum[id]*x+pre[id];
		};
		auto add=[&](this auto &&self,ll p,ll l,ll r,ll id)->void{
			if (!tr[p]) {
				tr[p]=id;
				return;
			}
			ll mid=(l+r)/2;
			if (eval(id,mid)>eval(tr[p],mid))
				swap(id,tr[p]);
			if (l==r)
				return;
			if (eval(id,l)>eval(tr[p],l))
				self(p*2,l,mid,id);
			else if (eval(id,r)>eval(tr[p],r))
				self(p*2+1,mid+1,r,id);
		};
		auto qry=[&](this auto &&self,ll p,ll l,ll r,ll x)->ll{
			if (!tr[p])
				return -INF;
			ll res=eval(tr[p],x),mid=(l+r)/2;
			if (l==r)
				return res;
			if (x<=mid)
				return max(res,self(p*2,l,mid,x));
			return max(res,self(p*2+1,mid+1,r,x));
		};

		for (ll rep=0;rep<2;rep++) {
			fill(tr.begin(),tr.end(),0);
			add(1,0,lim,c);
			for (const auto &vec:grp) {
				for (auto u:vec)
					ans=max(ans,qry(1,0,lim,dep[u])+suf[u]);
				for (auto u:vec)
					add(1,0,lim,u);
			}
			reverse(grp.begin(),grp.end());
		}
	};

	auto divide=[&](this auto &&self,ll rt)->void{
		getsiz(rt,0);
		ll c=center(rt,0,siz[rt]);
		del[c]=1;
		calc(c);
		for (auto v:eg[c])
			if (!del[v])
				self(v);
	};
	divide(1);
	cout << ans << '\n';
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
