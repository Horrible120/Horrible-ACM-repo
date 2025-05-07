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

const ll MAXN = 6e6+1;
ll mob[MAXN+1], pr[MAXN+1];
vector<ll> prm;				//素数序列
ll preprm[400001]={};

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
	
	for(ll i=1;i<=400000;i++)
		preprm[i]=preprm[i-1]+prm[i-1];
}

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	sort(v.begin()+1,v.end(),greater<ll>());
	
//	for(ll i=1;i<=20;i++)
//		cout<<i<<' '<<preprm[i]<<endl;
	
	vector<ll> pre(n+1,0);
	ll ans=min(n,1ll);
	
	for(ll i=1;i<=n;i++){
		pre[i]=pre[i-1]+v[i];
		if(pre[i]>=preprm[i])
			ans=max(ans,i);
	}
	
//	OOO
	cout<<n-ans<<endl;
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
