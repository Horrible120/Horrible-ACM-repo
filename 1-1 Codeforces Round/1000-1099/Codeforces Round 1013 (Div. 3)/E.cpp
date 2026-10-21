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

const ll MAXN = 1e7+1;
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

void solve(){
	ll n;
	cin>>n;
	ll ans=0;
	for(auto p:prm){
		
		if(p>n) break;ans++;
		for(ll i=2*p;i<=n;i+=p)
			ans++;
	}
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
