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

ll qpow(ll val,ll exp){
	ll ans=1;
	while (exp){
		if (exp&1)
			ans=ans*val%Mod;
		val=val*val%Mod;
		exp>>=1;
	}
	return ans;
}

void solve(){
	ll n;
	cin >> n;
	vector<ll> l(n+1),r(n+1),pos;
	ll den=1;
	for (ll i=1;i<=n;i++){
		cin >> l[i] >> r[i];
		r[i]++;
		den=den*(r[i]-l[i])%Mod;
		pos.emplace_back(l[i]);
		pos.emplace_back(r[i]);
	}
	sort(pos.begin(),pos.end());
	pos.erase(unique(pos.begin(),pos.end()),pos.end());

	vector<ll> inv(n+1),f(n+1);
	inv[1]=1;
	for (ll i=2;i<=n;i++)
		inv[i]=(Mod-Mod/i)*inv[Mod%i]%Mod;
	f[0]=1;

	for (ll s=(ll)pos.size()-2;s>=0;s--){
		ll lef=pos[s],rig=pos[s+1],len=rig-lef;
		vector<ll> cnt(n+1);
		cnt[0]=1;
		for (ll k=1;k<=n;k++)
			cnt[k]=cnt[k-1]*(len+k-1)%Mod*inv[k]%Mod;

		vector<ll> g=f;
		for (ll i=0;i<n;i++){
			for (ll j=i+1;j<=n;j++){
				if (l[j]>lef || r[j]<rig)
					break;
				g[j]=(g[j]+f[i]*cnt[j-i])%Mod;
			}
		}
		f.swap(g);
	}

	cout << f[n]*qpow(den,Mod-2)%Mod << '\n';
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
