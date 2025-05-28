#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef int ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

const ll MAXN = 2e5+1;
ll mob[MAXN+1], pr[MAXN+1];
vector<ll> prm;				//素数序列

void init() {
	bool np[MAXN+1] = {};		//not_prime 数组
	for (ll i = 1; i <= MAXN; i++)
		mob[i] = 1;				//初始化 莫比乌斯函数 数组
	
	np[1] = 1;
	mob[1] = 1;
	
	for (ll i = 2; i <= MAXN; i++) {
		if (!np[i]) {
			mob[i] = -1;
			pr[i] = i;			//素数在最小素因子是他本身
			prm.emplace_back(i);
		}
		
		for (auto j : prm) {
			
			if (j * i > MAXN) break;
			
			np[i *j] = 1;
			pr[i *j] = j;
			
			if (i % j == 0) {
				mob[i *j] = 0;
				break;
			}
			
			mob[i *j] = -mob[i];
		}
	}
	mob[1] = 0;
}

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void solve(){
	ll n,N=2e5;
	cin>>n;
	vector<ll> v(n+1,0),iv(N+1,0);
	
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	for(ll i=1;i<=N;i++)
		iv[i]=inv(i);
	
	class Info{
	public:
		ll lhs,rhs,mul;
		Info():lhs(0),rhs(0),mul(1){};
		Info(ll val):lhs(0),rhs(0),mul(val){};
	};
	
	ll tot=0;
	vector<ll> rt(n+1,0);
	vector<Info> tr((__lg(n)+2)*18*n,Info());
	
	auto modify=[&](auto &&self,ll &u,ll v,ll l,ll r,ll pos,ll key)->void{
		u=++tot;
		tr[u]=tr[v];
		if(l==r){
			tr[u].mul=(long long)tr[u].mul*key%Mod;
			return;
		}
		ll mid=l+r>>1;
		if(pos<=mid)
			self(self,tr[u].lhs,tr[v].lhs,l,mid,pos,key);
		else
			self(self,tr[u].rhs,tr[v].rhs,mid+1,r,pos,key);
		tr[u].mul=(long long)tr[tr[u].lhs].mul*tr[tr[u].rhs].mul%Mod;
//		cout<<"#### "<<u<<' '<<l<<' '<<r<<' '<<pos<<' '<<key<<' '<<tr[u].mul<<endl;
	};
	
	auto query=[&](auto &&self,ll u,ll l,ll r,ll s,ll t)->ll{
		if(!u)
			return 1;
		if(l>=s&&r<=t)
			return tr[u].mul;
		ll mid=l+r>>1;
		if(mid>=s&&mid+1<=t)
			return (long long)self(self,tr[u].lhs,l,mid,s,t)*self(self,tr[u].rhs,mid+1,r,s,t)%Mod;
		else if(mid>=s)
			return self(self,tr[u].lhs,l,mid,s,t);
		else
			return self(self,tr[u].rhs,mid+1,r,s,t);
	};
	
	vector<ll> lst(N+1,0);
	
	for(ll i=1;i<=n;i++){
		ll x=v[i];
		rt[i]=rt[i-1];
		while(x>1){
			ll k=pr[x],tmp=1;
			while(x%k==0){
				tmp*=k;
				x/=k;
//				cout<<"!!! "<<i<<' '<<k<<' '<<tmp<<' '<<lst[tmp]<<endl;
				if(lst[tmp])
					modify(modify,rt[i],rt[i],1,n,lst[tmp],iv[k]);
				lst[tmp]=i;
			}
		}
		modify(modify,rt[i],rt[i],1,n,i,v[i]);
	}
	
	ll q;
	cin>>q;
	
	ll last=0;
	
	for(ll i=1;i<=q;i++){
		ll l,r;
		cin>>l>>r;
		l=(l+last)%n+1;
		r=(r+last)%n+1;
		if(l>r)
			swap(l,r);
		last=query(query,rt[r],1,n,l,r);
//		OOO
		cout<<last<<endl;
	}
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	init();
	
//	for(ll i=2;i<=100;i++)
//		cout<<i<<' '<<pr[i]<<endl;
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
