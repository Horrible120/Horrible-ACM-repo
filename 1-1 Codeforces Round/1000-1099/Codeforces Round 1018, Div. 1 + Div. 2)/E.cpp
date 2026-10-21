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
	ll n,ans=0;
	cin>>n;
	string s;
	cin>>s;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++)
		v[i]=s[i-1]=='P';
	
	ll cnt=0,cnt0=0,ccnt=0;
	for(ll i=1;i<=n;i++){
		if(v[i]==0)
			cnt+=i,
			cnt0++;
		if(v[i]==0&&i%2==0)
			ccnt++;
	}
	
	ans=(cnt-(1+cnt0)*cnt0/2-abs(cnt0/2-ccnt))/2+abs(cnt0/2-ccnt);
	
	
//	OOO
	cout<<ans<<endl;
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
