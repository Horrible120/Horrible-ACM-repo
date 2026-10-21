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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

using i64 = long long;

template<class T>
constexpr T power(T a, i64 b) {
	T res = 1;
	for (; b; b /= 2, a *= a) {
		if (b % 2) {
			res *= a;
		}
	}
	return res;
}

template<int P>
struct MInt {
	int x;
	constexpr MInt() : x{} {}
	constexpr MInt(i64 x) : x{norm(x % getMod())} {}
	
	static int Mod;
	constexpr static int getMod() {
		if (P > 0) {
			return P;
		} else {
			return Mod;
		}
	}
	constexpr static void setMod(int Mod_) {
		Mod = Mod_;
	}
	constexpr int norm(int x) const {
		if (x < 0) {
			x += getMod();
		}
		if (x >= getMod()) {
			x -= getMod();
		}
		return x;
	}
	constexpr int val() const {
		return x;
	}
	explicit constexpr operator int() const {
		return x;
	}
	constexpr MInt operator-() const {
		MInt res;
		res.x = norm(getMod() - x);
		return res;
	}
	constexpr MInt inv() const {
		assert(x != 0);
		return power(*this, getMod() - 2);
	}
	constexpr MInt &operator*=(MInt rhs) & {
		x = 1LL * x * rhs.x % getMod();
		return *this;
	}
	constexpr MInt &operator+=(MInt rhs) & {
		x = norm(x + rhs.x);
		return *this;
	}
	constexpr MInt &operator-=(MInt rhs) & {
		x = norm(x - rhs.x);
		return *this;
	}
	constexpr MInt &operator/=(MInt rhs) & {
		return *this *= rhs.inv();
	}
	friend constexpr MInt operator*(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res *= rhs;
		return res;
	}
	friend constexpr MInt operator+(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr MInt operator-(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr MInt operator/(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res /= rhs;
		return res;
	}
	friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
		i64 v;
		is >> v;
		a = MInt(v);
		return is;
	}
	friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
		return os << a.val();
	}
	friend constexpr bool operator==(MInt lhs, MInt rhs) {
		return lhs.val() == rhs.val();
	}
	friend constexpr bool operator!=(MInt lhs, MInt rhs) {
		return lhs.val() != rhs.val();
	}
};

template<>
int MInt<0>::Mod = 1;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z = MInt<P>;

std::vector<int> rev;
template<int P>
std::vector<MInt<P>> roots{0, 1};

template<int P>
constexpr MInt<P> findPrimitiveRoot() {
	MInt<P> i = 2;
	int k = __builtin_ctz(P - 1);
	while (true) {
		if (power(i, (P - 1) / 2) != 1) {
			break;
		}
		i += 1;
	}
	return power(i, (P - 1) >> k);
}

template<int P>
constexpr MInt<P> primitiveRoot = findPrimitiveRoot<P>();

template<>
constexpr MInt<998244353> primitiveRoot<998244353> {31};

template<int P>
constexpr void dft(std::vector<MInt<P>> &a) {
	int n = a.size();
	if(n==1) return;
	
	if (int(rev.size()) != n) {
		int k = __builtin_ctz(n) - 1;
		rev.resize(n);
		for (int i = 0; i < n; i++) {
			rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (rev[i] < i) {
			std::swap(a[i], a[rev[i]]);
		}
	}
	if (int(roots<P>.size()) < n) {
		int k = __builtin_ctz(roots<P>.size());
		roots<P>.resize(n);
		while ((1 << k) < n) {
			auto e = power(primitiveRoot<P>, 1 << (__builtin_ctz(P - 1) - k - 1));
			for (int i = 1 << (k - 1); i < (1 << k); i++) {
				roots<P>[2 * i] = roots<P>[i];
				roots<P>[2 * i + 1] = roots<P>[i] * e;
			}
			k++;
		}
	}
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
			for (int j = 0; j < k; j++) {
				MInt<P> u = a[i + j];
				MInt<P> v = a[i + j + k] * roots<P>[k + j];
				a[i + j] = u + v;
				a[i + j + k] = u - v;
			}
		}
	}
}

template<int P>
constexpr void idft(std::vector<MInt<P>> &a) {
	int n = a.size();
	std::reverse(a.begin() + 1, a.end());
	dft(a);
	MInt<P> inv = (1 - P) / n;
	for (int i = 0; i < n; i++) {
		a[i] *= inv;
	}
}

ll n,V,m;
vector<ll> a,cnt,inv,f,g;

void calc(ll l,ll mid,ll r){
	ll pos=upper_bound(a.begin()+1,a.end(),mid)-a.begin();
	if(pos>n||a[pos]>r||a[pos]+l>m) return;
	ll base=a[pos],R=min(mid,m-base);
	ll len=m-l-base+1,w=R-l+1,sz=1,lg=0;
	while(sz<len+w-1) sz<<=1,lg++;

	ll sum=0;
	for(ll i=pos;i<=n&&a[i]<=r&&a[i]+l<=m;i++){
		ll k=(m-R)/a[i],lim=(m-l)/a[i];
		sum+=k*w;
		for(ll j=k+1;j<=lim;j++) sum+=m-j*a[i]-l+1;
	}
	if(sum<=3*sz*max(1LL,lg)){
		for(ll i=pos;i<=n&&a[i]<=r&&a[i]+l<=m;i++){
			for(ll k=a[i];k+l<=m;k+=a[i]){
				ll R0=min(R,m-k);
				for(ll j=l;j<=R0;j++){
					f[j]+=g[j+k];
					if(f[j]>=Mod) f[j]-=Mod;
				}
			}
		}
		return;
	}

	vector<Z> x(sz),y(sz);
	for(ll i=0;i<len;i++) x[i]=g[m-i];
	for(ll i=pos;i<=n&&a[i]<=r&&a[i]+l<=m;i++){
		for(ll k=a[i];k+l<=m;k+=a[i]) y[k-base]+=1;
	}
	dft(x);
	dft(y);
	for(ll i=0;i<sz;i++) x[i]*=y[i];
	idft(x);
	for(ll i=l;i<=R;i++){
		f[i]+=x[m-base-i].val();
		if(f[i]>=Mod) f[i]-=Mod;
	}
}

void cdq(ll l,ll r){
	if(r<a[1]) return;
	if(cnt[r]==cnt[l]){
		for(ll i=max(l,a[1]);i<=r;i++) g[i]=f[i]*inv[cnt[i]]%Mod;
		return;
	}
	ll mid=(l+r)>>1;
	cdq(mid+1,r);
	calc(l,mid,r);
	cdq(l,mid);
}

void solve(){
	cin>>n>>V;
	a.assign(n+1,0);
	for(ll i=1;i<=n;i++) cin>>a[i];

	ll fac=1;
	for(ll i=1;i<=n;i++) fac=fac*i%Mod;
	vector<ll> ans(V+1,0);
	if(a[1]>V) ans[V]=fac;
	else if(a[1]==1) ans[0]=fac;
	else{
		ll k=upper_bound(a.begin()+1,a.end(),V)-a.begin()-1;
		m=0;
		for(ll i=1;i<=k;i++) m=max(m,V%a[i]);
		cnt.assign(m+1,0);
		f.assign(m+1,0);
		g.assign(m+1,0);
		inv.assign(k+1,1);
		for(ll i=2;i<=k;i++) inv[i]=Mod-Mod/i*inv[Mod%i]%Mod;
		for(ll i=1;i<=k&&a[i]<=m;i++) cnt[a[i]]=1;
		for(ll i=1;i<=m;i++) cnt[i]+=cnt[i-1];

		ll val=fac*inv[k]%Mod;
		for(ll i=1;i<=k;i++){
			ll x=V%a[i];
			f[x]+=val;
			if(f[x]>=Mod) f[x]-=Mod;
		}
		cdq(0,m);
		for(ll i=0;i<=m&&i<a[1];i++) ans[i]=f[i];
	}
	for(ll i=0;i<=V;i++) cout<<ans[i]<<(i==V?'\n':' ');
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
