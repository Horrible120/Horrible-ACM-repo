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
	ll m,x,rst=0;
	cin>>m>>x;
	multiset<ll,greater<ll>> s;
	vector<ll> ci(m+1,0);
	for(ll i=1;i<=m;i++){
		cin>>ci[i];
		
		if(rst>=ci[i]){
			s.insert(ci[i]);
			rst-=ci[i];
		}
		else if(ci[i]<*s.begin()){
			rst+=*s.begin();
			s.erase(s.begin());
			s.insert(ci[i]);
			rst-=ci[i];
		}
		
		rst+=x;
	}
//	OOO
	cout<<s.size()<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
