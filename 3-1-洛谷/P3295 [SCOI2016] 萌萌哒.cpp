#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	v2ct<ll> fa(21,vector<ll>(n+1));
	for(ll i=0;i<=20;i++)
		for(ll j=1;j<=n;j++)
			fa[i][j]=j;
	
	auto GF=[&](auto &&self,ll x,ll k){
		if(fa[k][x]==x) return x;
		return fa[k][x]=self(self,fa[k][x],k);
	};
	auto merge=[&](ll a,ll b,ll k){
		ll f1=GF(GF,a,k),f2=GF(GF,b,k);
		if(f1!=f2) fa[k][f1]=f2;
	};
	
	for(ll i=1;i<=m;i++){
		ll l1,l2,r1,r2;
		cin>>l1>>r1>>l2>>r2;
		ll len=r1-l1+1,k=0;
		
		while(len){
			if(len&1){
//				cout<<l1<<' '<<l2<<' '<<k<<endl;
				merge(l1,l2,k);
				l1+=1<<k;
				l2+=1<<k;
			}
			len>>=1;
			k++;
		}
	}
	
	for(ll i=18;i>=1;i--){
		for(ll j=1;j<=n;j++){
			ll f=GF(GF,j,i);
			if(f!=j){
				merge(j,f,i-1);
				merge(j+(1<<i-1),f+(1<<i-1),i-1);
			}
		}
	}
	
	ll ans=9,cnt=-1;
	vector<ll> book(n+1,0);
	for(ll i=1;i<=n;i++){
		ll f=GF(GF,i,0);
//		cout<<i<<' '<<f<<endl;
		if(!book[f]){
			cnt++;
			book[f]=1;
		}
	}
	
//	cout<<cnt<<endl;
	while(cnt--)
		ans=ans*10%Mod;
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
