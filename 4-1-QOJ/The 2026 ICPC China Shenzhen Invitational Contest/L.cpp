#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

const ll N=3009;
ll tt=1;
ll n,m=0;
struct node{
	ld p;
	ll v,w;
	bool operator <(const node &b)const{
		return v<b.v;
	}
};
node a[N];
ld f[N];
void solve(){
	for(int i=1;i<=m;i++)f[i]=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].p>>a[i].v>>a[i].w;
		a[i].p/=100;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		for(int j=m;j>=a[i].w;j--){
			f[j]=max(f[j],(1-a[i].p)*f[j-a[i].w]+a[i].v*a[i].p);
		}
	}
	
	printf("%.9Lf\n",f[m]);
}

int main() {
//	ios::sync_with_stdio( 0 );
//	cin.tie( 0 );
//	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
