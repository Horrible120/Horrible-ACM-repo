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
	vector<ll> a(n+1),val;
	for (ll i=1;i<=n;i++) {
		cin >> a[i];
		val.emplace_back(a[i]);
	}

	ll q;
	cin >> q;
	vector<pair<ll,ll>> que(q);
	for (auto &[pos,x]:que) {
		cin >> pos >> x;
		val.emplace_back(x);
	}

	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());

	ll m=val.size(),inv=(Mod+1)/2;
	vector<ll> pw(n+1,1),cnt(m);
	for (ll i=1;i<=n;i++)
		pw[i]=pw[i-1]*inv%Mod;

	auto id=[&](ll x)->ll{
		return lower_bound(val.begin(),val.end(),x)-val.begin();
	};

	for (ll i=1;i<=n;i++) {
		a[i]=id(a[i]);
		cnt[a[i]]++;
	}

	for (auto &[pos,x]:que)
		x=id(x);

	struct Node {
		ll z=1,f=0,g=0,ans=0;
	};

	vector<Node> tr(4*m);

	auto pull=[&](ll u)->void{
		const auto &l=tr[u*2],&r=tr[u*2+1];
		tr[u].z=l.z*r.z%Mod;
		tr[u].f=(l.f+l.z*r.f)%Mod;
		tr[u].g=(r.g+r.z*l.g)%Mod;
		tr[u].ans=(l.ans+r.ans+l.g*r.f)%Mod;
	};

	auto leaf=[&](ll u,ll k)->void{
		ll x=val[k],c=cnt[k],z=pw[c];
		tr[u].z=z;
		tr[u].f=tr[u].g=x*(1-z+Mod)%Mod;
		tr[u].ans=x*x%Mod*((c*inv%Mod-1+z+Mod)%Mod)%Mod;
	};

	auto build=[&](this auto &&self,ll u,ll l,ll r)->void{
		if (l==r) {
			leaf(u,l);
			return;
		}
		ll mid=(l+r)/2;
		self(u*2,l,mid);
		self(u*2+1,mid+1,r);
		pull(u);
	};

	auto upd=[&](this auto &&self,ll u,ll l,ll r,ll k)->void{
		if (l==r) {
			leaf(u,l);
			return;
		}
		ll mid=(l+r)/2;
		if (k<=mid)
			self(u*2,l,mid,k);
		else
			self(u*2+1,mid+1,r,k);
		pull(u);
	};

	build(1,0,m-1);
	cout << tr[1].ans << '\n';

	for (auto [pos,x]:que) {
		cnt[a[pos]]--;
		upd(1,0,m-1,a[pos]);

		a[pos]=x;
		cnt[x]++;
		upd(1,0,m-1,x);

		cout << tr[1].ans << '\n';
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
