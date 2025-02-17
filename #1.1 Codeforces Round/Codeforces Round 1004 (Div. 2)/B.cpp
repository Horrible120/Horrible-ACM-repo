#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++) cin>>v[i];
	sort(v.begin()+1,v.end());
	ll l=1,flag=1;
	while(l<=n&&flag){
		ll pos=l,cnt=0;
		while(pos<=n&&v[pos++]==v[l])
			cnt++;
		if(cnt>=2||cnt%2==0){
			for(ll i=l;i<=l+cnt-1;i++)
				v[i]+=1;
			l+=2;
		}
		else flag=0;
	}
	if(flag) CY
		else CN
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
