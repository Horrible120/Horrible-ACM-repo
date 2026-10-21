#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
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
	v2ct<ll> ad(n+1,vector<ll>(3,0)),ti(n+1,vector<ll> (3,1));
	vector<ll> dp(n+2,0);
	for(ll i=1;i<=n;i++){
		char op1,op2;
		ll c1,c2;
		cin.ignore(100,'\n');
		cin>>op1>>c1;
//		cout<<op1<<endl;
		if(op1=='+')
			ad[i][1]=c1;
		else 
			ti[i][1]=c1;
		cin.ignore(100,' ');
		cin>>op2>>c2;
//		OOO  cout.flush();
		if(op2=='+')
			ad[i][2]=c2;
		else 
			ti[i][2]=c2;
	}
	dp[n+1]=1;
	for(ll i=n;i>=1;i--){
		if(ti[i][1]==ti[i][2])
			dp[i]=dp[i+1];
		else if(ti[i][1]>=ti[i][2])
			dp[i]=1;
		else
			dp[i]=2;
	}
	ll a1=1,a2=1;
	for(ll i=1;i<=n;i++){
		ll tmp1=0,tmp2=0;
		tmp1=a1*(ti[i][1]-1)+ad[i][1];
		tmp2=a2*(ti[i][2]-1)+ad[i][2];
//		OOO
//		cout<<ti[i][1]<<' '<<ti[i][2]<<endl;
//		cout<<tmp1<<' '<<tmp2<<endl;
		if(dp[i+1]==1)
			a1+=tmp1+tmp2;
		else
			a2+=tmp1+tmp2;
	}
	cout<<a1+a2<<endl;
	
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
