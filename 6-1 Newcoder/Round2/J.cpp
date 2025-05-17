#include <bits/extc++.h>
// #define OOO print(">>>>");    //调试标识
// #define H_test(x) println("---> {} <---",x);    //调试输出

using namespace std;
using namespace __gnu_pbds;

typedef int ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7,N=3e5;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

int primes[N], cnt;     // primes[]存储所有素数
bool st[N];         // st[x]存储x是否被筛掉

void get_primes()
{
	for (int i = 2; i <= N; i ++ )
	{
		if (!st[i]) primes[cnt ++ ] = i;
		for (int j = 0; primes[j] <= N / i; j ++ )
		{
			st[primes[j] * i] = true;
			if (i % primes[j] == 0) break;
		}
	}
}

void solve(){
	ll a,b,flag=0;
	cin>>a>>b;
	for(auto pr:primes){
		if(pr>a||pr>b){
			break;
		}
		else if(a%pr&&b%pr){
			std::cout << pr << "\n";
			flag=1;
			break;
		}
	}
	if(!flag) std::cout << "-1\n";
	return;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	get_primes();
	cin >> tt;    //非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
