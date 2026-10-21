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

const ll MAXN=1e6;
vector<ll> minp(MAXN+1), prm, val, id(MAXN+1,-1), bas;
string mode;

void sieve(){
	for ( ll i=2; i<=MAXN; i++ ) {
		if ( !minp[i] ) {
			minp[i]=i;
			prm.emplace_back(i);
		}
		for ( ll j=0; j<(ll)prm.size(); j++ ) {
			if ( prm[j]>minp[i] || i*prm[j]>MAXN )
				break;
			minp[i*prm[j]]=prm[j];
		}
	}

	for ( ll i=0; i<150; i++ ) {
		ll cur=1;
		while ( cur<=MAXN/prm[i] )
			cur*=prm[i];
		bas.emplace_back(cur);
	}

	val.emplace_back(1);
	id[1]=0;
	for ( ll i=2; i<=MAXN; i++ ) {
		if ( minp[i]<=prm[149] && id[i/minp[i]]!=-1 ) {
			id[i]=val.size();
			val.emplace_back(i);
		}
	}
}

void solve(){
	ll n;
	if ( !(cin>>n) || n==-1 )
		exit(0);
	vector<ll> bit(20*n+18);

	if ( mode=="first" ) {
		for ( ll i=0; i<n; i++ ) {
			ll cur;
			if ( !(cin>>cur) || cur==-1 )
				exit(0);
			for ( ll j=0; j<20; j++ )
				bit[20*i+j]=(cur>>j)&1;
		}

		vector<ll> b=bas;
		for ( ll i=0; i<20*n; i+=18 ) {
			ll cur=0;
			for ( ll j=0; j<18; j++ )
				cur|=bit[i+j]<<j;
			b.emplace_back(val[cur]);
		}

		cout << b.size() << '\n';
		for ( ll i=0; i<(ll)b.size(); i++ )
			cout << b[i] << ' ';
		cout << endl;
		return;
	}

	ll k;
	if ( !(cin>>k) || k==-1 )
		exit(0);
	for ( ll i=151; i<=k; i++ ) {
		ll cur=1;
		for ( ll j=1; j<=150; j++ ) {
			cout << "? " << i << ' ' << j << endl;
			ll res;
			if ( !(cin>>res) || res==-1 )
				exit(0);
			cur*=res;
		}
		cur=id[cur];
		for ( ll j=0; j<18; j++ )
			bit[(i-151)*18+j]=(cur>>j)&1;
	}

	cout << '!';
	for ( ll i=0; i<n; i++ ) {
		ll cur=0;
		for ( ll j=0; j<20; j++ )
			cur|=bit[20*i+j]<<j;
		cout << ' ' << cur;
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	if ( !(cin>>mode) || mode=="-1" )
		return 0;
	sieve();

	cin >> tt;	//非多组测试数据时注释掉即可
	if ( !cin || tt==-1 )
		return 0;

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
