#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,a,b;
	cin>>n>>a>>b;
	string s,t;
	cin>>s>>t;
	ll cnt=0;
	ll ct[2]={};
	for(ll i=1;i<=n;i++){
		ct[0]+=(s[i-1]=='0');
		ct[1]+=(t[i-1]=='0');
		if(s[i-1]==t[i-1]&&s[i-1]=='0'){
			cnt++;
		}
	}
	
	double ans=(((double)max(ct[0]-a,0ll))/ct[0])*(((double)max(ct[1]-b,0ll))/ct[1]);

	cout<<fixed<<setprecision(9)<<(double)n-ans*cnt<<endl;
	
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
