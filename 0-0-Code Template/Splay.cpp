#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
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

class Splay {
public:
	ll rt, id;
	vector<ll> fa, val, siz, cnt;
	vector<array<ll, 2 >> ch;

	Splay() {}
	Splay( ll _n ) {
		rt = id = 0;
		fa.assign( _n + 1, 0 );
		val.assign( _n + 1, 0 );
		siz.assign( _n + 1, 0 );
		cnt.assign( _n + 1, 0 );
		ch.assign( _n + 1, array<ll, 2>() );
	}

	bool dir( ll x ) {
		return x == ch[fa[x]][1];
	}

	void push_up( ll x ) {
		siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x];
	}

	void rotate(ll x){ 		//在所有函数的实现时，都应注意不要修改节点 0 的信息
		ll y=fa[x],z=fa[y];
		bool r=dir(x);
		ch[y][r]=ch[x][!r];
		ch[x][!r]=y;
		if(z) ch[z][dir(y)]=x;
		if(ch[y][r]) fa[ch[y][r]]=y;
		fa[y]=x;
		fa[x]=z;
		push_up(y);
		push_up(x);
	}
	
	void splay(ll &z,ll x){	//可以指定任意根节点 z，并将它的子树内任意节点 x 上移至 z 处
		ll w=fa[z];
		for(ll y;(y=fa[x])!=w;rotate(x)){
			if(fa[y]!=w) rotate(dir(x)==dir(y)?y:x);
		}
		z=x;
	}
	
	void find(ll &z,ll v){	//该实现允许指定任何节点 z 作为根节点，并在它的子树内按值查找
		ll x=z,y=fa[x];
		while(x&&val[x]!=v){
			y=x;
			x=ch[x][v>val[x]];
		}
		splay(z,x?x:y);
	}
	
	void loc(ll &z,ll k){
		ll x=z;
		while(true){
			if(siz[ch[x][0]]>=k){
				x=ch[x][0];
			}else if(siz[ch[x][0]]+cnt[x]>=k){
				break;
			}else{
				k-=siz[ch[x][0]]+cnt[x];
				x=ch[x][1];
			}
		}
		splay(z,x);
	}
	
	ll find_kth(ll k){
		if(k>siz[rt]) return -1;
		loc(rt,k);
		return val[rt];
	}
	
	ll merge(ll x,ll y){
		if(!x||!y) return x|y;
		loc(y,1);
		ch[y][0]=x;
		fa[x]=y;
		push_up(y);
		return y;
	}
	
	void insert(ll v){
		ll x=rt,y=0;
		while(x&&val[x]!=v){
			y=x;
			x=ch[x][v>val[x]];
		}
		if(x){
			cnt[x]++;
			siz[x]++;
		}else{
			x=++id;
			val[x]=v;
			siz[x]=cnt[x]=1;
			fa[x]=y;
			if(y) ch[y][v>val[y]]=x;
		}
		splay(rt,x);
	}
	
	bool remove(ll v){
		find(rt,v);
		if(!rt||val[rt]!=v) return false;
		cnt[rt]--;
		siz[rt]--;
		if(!cnt[rt]){
			ll x=ch[rt][0],y=ch[rt][1];
			fa[x]=fa[y]=0;
			rt=merge(x,y);
		}
		return true;
	}
	
	ll find_rank(ll v){
		find(rt,v);
		return siz[ch[rt][0]]+(val[rt]>=v?0:cnt[rt])+1;
	}
	
	ll find_prev(ll v){
		find(rt,v);
		if(rt&&val[rt]<v) return val[rt];
		ll x=ch[rt][0];
		if(!x) return -1;
		while(ch[x][1]) x=ch[x][1];
		splay(rt,x);
		return val[rt];
	}
	
	ll find_next(ll v){
		find(rt,v);
		if(rt&&val[rt]>v) return val[rt];
		ll x=ch[rt][1];
		if(!x) return -1;
		while(ch[x][0]) x=ch[x][0];
		splay(rt,x);
		return val[rt];
	}
	
};

void solve() {
	ll n;
	cin>>n;
	Splay spl(2000000);
	
	for(ll i=1;i<=n;i++){
		ll op,k;
		cin>>op>>k;
		if(op==1){
			spl.insert(k);
		}else if(op==2){
			spl.remove(k);
		}else if(op==3){
			cout<<spl.find_rank(k)<<'\n';
		}else if(op==4){
			cout<<spl.find_kth(k)<<'\n';
		}else if(op==5){
			cout<<spl.find_prev(k)<<'\n';
		}else{
			cout<<spl.find_next(k)<<'\n';
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
