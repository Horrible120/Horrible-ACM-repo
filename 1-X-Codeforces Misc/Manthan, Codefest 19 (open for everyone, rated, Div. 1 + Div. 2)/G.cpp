#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

/***********************************************/

const ll MAXN=1e6;
vector<ll> minp,prm,phi;
void sieve(){
	minp.resize(MAXN);
	phi.resize(MAXN);
	
	phi[1]=1;
	
	for(ll i=2;i<=MAXN;i++){
		if(!minp[i]){
			minp[i]=i;
			phi[i]=i-1;
			prm.emplace_back(i);
		}
		for(auto j:prm){
			if(j>minp[i]||i*j>MAXN)
				break;
			minp[i*j]=j;
			if(i%j==0){
				phi[i*j]=phi[i]*j;
			}else{
				phi[i*j]=phi[i]*(j-1);
			}
			
		}
	}
}

/***********************************************/

void solve(){
	ll n,k,ans=0;
	cin>>n>>k;
	
	if(k==1){
		cout<<3<<endl;
		return;
	}
	
	sieve();
	
	sort(phi.begin()+1,phi.begin()+n+1);
		
//	for(ll i=1;i<=n;i++)
//		cout<<i<<' '<<phi[i]<<endl;
//	cout<<endl;
	
	for(ll i=1;i<=2+k;i++){
		ans+=phi[i];
	}
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
