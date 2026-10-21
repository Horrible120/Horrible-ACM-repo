#include <bits/extc++.h>
#define OOO cout<<">>>> ";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T >>;

template <typename T, typename Compare = std::less<T >>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( ( uintptr_t )( char* )( &INF ) + time( 0 ) );

ll tt = 1;

class Splay{
public:
	ll rt, id;
	vector<ll> tag, fa, val, siz;
	vector<array<ll, 2 >> ch;

	Splay() {}
	Splay( ll _n ) {
		rt=id=0;
		tag.assign( _n + 3, 0 );
		fa.assign( _n + 3, 0 );
		val.assign( _n + 3, 0 );
		siz.assign( _n + 3, 0 );
		ch.assign( _n + 3, array<ll, 2>() );
		
		build(_n);
	}

	void push_up( ll x ) {
		siz[x] = 1 + siz[ch[x][0]] + siz[ch[x][1]];
	}

	void rotate( ll x ) {
		ll y = fa[x], z = fa[y];
		bool r = dir( x );
		ch[y][r] = ch[x][!r];
		ch[x][!r] = y;
		if ( z ) ch[z][dir( y )] = x;
		if ( ch[y][r] ) fa[ch[y][r]] = y;
		fa[y] = x;
		fa[x] = z;
		push_up(y);
		push_up(x);
	}

	void splay( ll & z, ll x ) {
		ll w = fa[z];
		for ( ll y; ( y = fa[x] ) != w; rotate( x ) ) {
			if ( fa[y] != w ) rotate( dir( x ) == dir( y ) ? y : x );
		}
		z = x;
	}

	void build( ll n ) {
		for ( ll i = 0; i <= n + 1; i++ ) {
			ch[++id][0] = rt;
			if ( rt ) fa[rt] = id;
			rt = id;
			val[id] = i;
		}
		splay( rt, 1 );
	}

	bool dir( ll x ) {
		return x == ch[fa[x]][1];
	}

	void lazy_reverse( ll x ) {
		swap( ch[x][0], ch[x][1] );
		tag[x] ^= 1;
	}

	void push_down( ll x ) {
		if (tag[x]) {
			if ( ch[x][0] ) lazy_reverse( ch[x][0] );
			if ( ch[x][1] ) lazy_reverse( ch[x][1] );
			tag[x] = 0;
		}
	}

	void loc( ll & z, ll k ) {
		ll x = z;
		for ( push_down( x ); siz[ch[x][0]] != k - 1; push_down( x ) ){
			if ( siz[ch[x][0]] >= k ) {
				x = ch[x][0];
			}else {
				k -= siz[ch[x][0]] + 1;
				x = ch[x][1];
			}
		}
		splay(z,x);
	}

	void reverse( ll l, ll r ) {
		loc( rt, l );
		loc(ch[rt][1],r-l+2);
		ll x=ch[ch[rt][1]][0];
		lazy_reverse(x);
		push_down(x);
		splay(rt, x);
	}
	
	void print(ll x){
		if(!x) return;
		push_down(x);
		print(ch[x][0]);
		cout<<val[x]<<' ';
		print(ch[x][1]);
	}
	
	void print(){
		loc(rt,1);
		loc(ch[rt][1],siz[rt]-1);
		print(ch[ch[rt][1]][0]);
	}
	
};

void solve() {
	ll n,m;
	cin>>n>>m;
	Splay spl(n);
	for(ll i=1;i<=m;i++){
		ll l,r;
		cin>>l>>r;
//		spl.print();
//		cout<<endl;
		spl.reverse(l,r);
	}
	spl.print();
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
