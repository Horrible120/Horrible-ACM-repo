#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	
	ll flag[2]={1,1};
	ll fg=0;
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		
		if(i>1&&v[i]>=v[i-1]-1)
			flag[0]=0;
		
		if(i>1&&v[i]<=v[i-1]+1)
			flag[1]=0;
		
		if(i>1&&abs(v[i]-v[i-1])<=1ll)
			fg=1;
		
//		cout<<abs(v[i]-v[i-1])<<endl;
	}
	
	
//	OOO
	
	if(flag[0]||flag[1]){
		cout<<-1<<endl;
	}
	else{
		if(fg==1)
			cout<<0<<endl;
		else
			cout<<1<<endl;
	}
	
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
