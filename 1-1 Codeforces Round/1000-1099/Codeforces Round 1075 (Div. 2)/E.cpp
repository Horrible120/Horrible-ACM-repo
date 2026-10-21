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
	ll n;
	string s;
	cin>>n>>s;

	ll cnt=0,sum=0,pre=-INF,suf=-INF;
	bool adj=false;
	for(ll i=0;i<n;i++){
		cnt+=(s[i]=='1');
		sum+=(s[i]=='1'?1:-1);
		pre=max(pre,sum);
		if(i&&s[i-1]=='1'&&s[i]=='1')
			adj=true;
	}

	ll cur=0;
	for(ll i=n-1;i>=0;i--){
		cur+=(s[i]=='1'?1:-1);
		suf=max(suf,cur);
	}

	if(cnt==0)
		cout<<-1<<'\n';
	else if(n==1)
		cout<<0<<'\n';
	else if(sum>=0)
		cout<<n<<'\n';
	else if(sum==-1||pre>0||suf>0)
		cout<<n+1<<'\n';
	else if(pre>=0||suf>=0||adj)
		cout<<n+2<<'\n';
	else
		cout<<n+3<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
