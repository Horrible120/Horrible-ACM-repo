#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,t,sum=n,ans=0;
	cin>>n>>t;
	vector<ll> v(n+1,0);
	multiset<ll,greater<ll>> st;
	string s;
	cin>>s;
	for(ll i=0;i<n;i++){
		v[i]=s[i]-'0';
		if(v[i]==1){
			sum=min(sum,i);
		}
	}
	
	if(sum==n){
		cout<<n<<endl;
		return;
	}
	
	for(ll i=sum;i<sum+n;i++){
		ll cnt=0;
		while(i+cnt<sum+n&&v[(i+cnt)%n]==0){
			++cnt;
		}
		st.insert(cnt);
		i=i+cnt;
	}
	
	if(st.size()){
		ans+=max(0ll,(*st.begin())-t-1);
		st.erase(st.begin());
		while(st.size()){
			ans+=max(0ll,(*st.begin())-2*t);
			st.erase(st.begin());
		}
	}
//	OOO
	cout<<ans<<"\n";
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
