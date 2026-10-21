#include <bits/stdc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef int ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

//template <typename T, typename Compare = std::less<T>>
//using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e9, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

ll n,k;
ll v[4001][4001],dp[801][4001],Sum[4001][4001]; 

inline void calc(ll u,ll l,ll r,ll optl,ll optr){
	ll mid=l+r>>1;
	ll opt=0;
	for(ll i=optl;i<=min(mid,optr);i++){
		if(dp[u-1][i-1]+Sum[i][mid]<dp[u][mid]){
			dp[u][mid]=dp[u-1][i-1]+Sum[i][mid];
			opt=i;
		}
	}
	
	if(l<mid) calc(u,l,mid-1,optl,opt);
	if(r>mid) calc(u,mid+1,r,opt,optr);
};

//void Read( int &x ) {
//	x = 0; int f = 1;
//	char s = getchar( );
//	for( ; s < '0' || s > '9' ; s = getchar( ) ) f = s == '-' ? -f : f;
//	for( ; s >= '0' && s <= '9' ; s = getchar( ) ) x = x * 10 + s - '0';
//	x *= f;
//}

namespace io{
	const int MAXBUF=1<<15;
	const int OUTPUT=1<<24;
	char b[MAXBUF],*S=b,*T=b;
#define getc() (S==T&&(T=(S=b)+fread(b,1,MAXBUF,stdin),S==T)?0:*S++)
#define O(x) __attribute__((optimize("-O"#x)))
#define inline __inline__ __attribute__((always_inline))
	template<class Type> inline Type read(){
		register Type aa=0;
		register bool bb=0;
		register char ch,*S=io::S,*T=io::T;
		for(ch=getc();(ch<'0'||ch>'9')&&ch!='-';ch=getc());
		for(ch=='-'?bb=1:aa=ch-'0',ch=getc();'0'<=ch&&ch<='9';ch=getc())aa=aa*10+ch-'0';
		io::S=S,io::T=T;
		return bb?-aa:aa;
	}
	inline int gets(register char *s){
		register char *iter=s,*S=io::S,*T=io::T;
		while(*iter=getc(),*iter==' '||*iter=='\n'||*iter=='\r');
		while(*++iter=getc(),*iter&&*iter!=' '&&*iter!='\n'&&*iter!='\r');
		*iter=0;
		io::S=S,io::T=T;
		return iter-s;
	}
	char buff[OUTPUT],*iter=buff;
	template<class T> inline void P(register T x, register char ch = '\n'){
		static int ST[110];
		register int O=0;
		register char *iter=io::iter;
		if(!x)*iter++='0';
		else{
			(x<0)?x=-x,*iter++='-':1;
			for(;x;x/=10)ST[++O]=x%10;
			for(;O;*iter++='0'+ST[O--]);
		}
		*iter++=ch,io::iter=iter;
	}
	inline void output(){fwrite(buff, 1, iter - buff, stdout),iter=buff;}
}

void solve(){
	register int (*F)()=io::read<int>;
	
	n=F();
	k=F();
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			v[i][j]=F();
			v[i][j]+=v[i-1][j]+v[i][j-1]-v[i-1][j-1];
		}
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=i;j<=n;j++){
			Sum[i][j]=v[j][j]+v[i-1][i-1]-v[j][i-1]-v[i-1][j];
		}
	}
	
	for(ll i=0;i<=k;i++){
		for(ll j=0;j<=n;j++){
			dp[i][j]=INF;
		}
	}
	
	dp[0][0]=0;
	for(ll i=1;i<=k;i++){
		for(ll j=0;j<=n;j++){
			dp[i][j]=INF;
		}
		calc(i,i,n,1,n);
	}
	
	cout<<dp[k][n]/2ll<<endl;
}

int main() {
//	ios::sync_with_stdio( 0 );
//	cin.tie( 0 );
//	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
