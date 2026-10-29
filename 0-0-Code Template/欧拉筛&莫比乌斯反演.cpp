#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T >>;
template <typename T> using v3ct = vector<vector<vector<T >>>;

template <typename T, typename Compare = std::less<T >>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd ( ( uintptr_t ) ( char* ) ( &INF ) + time ( 0 ) );

ll tt = 1;

/***********************************************/

vector<ll> minp,prm,mu;
void sieve(ll n){
	minp.assign(n+1,0);
	mu.assign(n+1,0);
	prm.clear();
	if(n>=1)
		mu[1]=1;

	for(ll i=2;i<=n;i++){
		if(!minp[i]){
			minp[i]=i;
			prm.emplace_back(i);
			mu[i]=-1;
		}
		for(ll p:prm){
			if(p>minp[i]||i*p>n)
				break;
			minp[i*p]=p;
			mu[i*p]=(p==minp[i]?0:-mu[i]);
		}
	}
}

/***********************************************/

void solve() {

}

int main() {
	ios::sync_with_stdio ( 0 );
	cin.tie ( 0 );
	cout.tie ( 0 );

	
	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
	}

	cout.flush();
	return 0;
}
