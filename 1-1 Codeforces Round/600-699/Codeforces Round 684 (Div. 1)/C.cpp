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
	ll n,q;
	cin >> n >> q;
	vector<ll> a(n+1);
	for (ll i=1;i<=n;i++)
		cin >> a[i];

	vector<ll> sum(4*n+5),mn(4*n+5),tag(4*n+5);
	auto pull=[&](ll u)->void{
		sum[u]=sum[u*2]+sum[u*2+1];
		mn[u]=min(mn[u*2],mn[u*2+1]);
	};
	auto apply=[&](ll u,ll l,ll r,ll val)->void{
		sum[u]=(r-l+1)*val;
		mn[u]=tag[u]=val;
	};
	auto push=[&](ll u,ll l,ll r)->void{
		if (!tag[u])
			return;
		ll mid=(l+r)/2;
		apply(u*2,l,mid,tag[u]);
		apply(u*2+1,mid+1,r,tag[u]);
		tag[u]=0;
	};

	auto build=[&](this auto &&self,ll u,ll l,ll r)->void{
		if (l==r) {
			sum[u]=mn[u]=a[l];
			return;
		}
		ll mid=(l+r)/2;
		self(u*2,l,mid);
		self(u*2+1,mid+1,r);
		pull(u);
	};
	auto upd=[&](this auto &&self,ll u,ll l,ll r,ll ql,ll qr,ll val)->void{
		if (ql<=l&&r<=qr) {
			apply(u,l,r,val);
			return;
		}
		push(u,l,r);
		ll mid=(l+r)/2;
		if (ql<=mid)
			self(u*2,l,mid,ql,qr,val);
		if (qr>mid)
			self(u*2+1,mid+1,r,ql,qr,val);
		pull(u);
	};

	auto find=[&](this auto &&self,ll u,ll l,ll r,ll pos,ll val)->ll{
		if (r<pos||mn[u]>val)
			return n+1;
		if (l==r)
			return l;
		push(u,l,r);
		ll mid=(l+r)/2;
		ll res=self(u*2,l,mid,pos,val);
		if (res<=n)
			return res;
		return self(u*2+1,mid+1,r,pos,val);
	};
	auto take=[&](this auto &&self,ll u,ll l,ll r,ll pos,ll &val)->ll{
		if (r<pos)
			return n+1;
		if (pos<=l&&sum[u]<=val) {
			val-=sum[u];
			return n+1;
		}
		if (l==r)
			return l;
		push(u,l,r);
		ll mid=(l+r)/2;
		ll res=self(u*2,l,mid,pos,val);
		if (res<=n)
			return res;
		return self(u*2+1,mid+1,r,pos,val);
	};
	build(1,1,n);

	while (q--) {
		ll op,x,y;
		cin >> op >> x >> y;
		if (op==1) {
			ll pos=find(1,1,n,1,y-1);
			if (pos<=x)
				upd(1,1,n,pos,x,y);
		}
		else {
			ll ans=0;
			while (x<=n&&y) {
				ll pos=find(1,1,n,x,y);
				if (pos>n)
					break;
				ll nxt=take(1,1,n,pos,y);
				ans+=nxt-pos;
				x=nxt;
			}
			cout << ans << '\n';
		}
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
