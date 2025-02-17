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
//	cin>>n;
	string s;
	cin>>s;
	n=s.size();
	vector<ll> v(n+1);
	
	for(ll i=1;i<=n;i++)
		v[i]=s[i-1]-'0';
	
	ll cnt[3][2]={};
	
	for(ll i=1;i<=n;i++)
		cnt[v[i]][i%2]++;
	
	
//	if(cnt[0][1]>cnt[0][0]) swap(cnt[0][1],cnt[0][0]);
//	if(cnt[1][1]>cnt[1][0]) swap(cnt[1][1],cnt[1][0]);
	
//	cout<<cnt[0][0]<<' '<<cnt[0][1]<<' '<<cnt[1][0]<<' '<<cnt[1][1]<<' '<<cnt[2][0]<<' '<<cnt[2][1]<<endl;
	
	if(cnt[0][1]<=cnt[0][0]){
		ll tmp=min(cnt[0][0]-cnt[0][1],cnt[2][1]);
		cnt[0][1]+=tmp;
		cnt[2][1]-=tmp;
	}
	else{
		ll tmp=min(cnt[0][1]-cnt[0][0],cnt[2][0]);
		cnt[0][0]+=tmp;
		cnt[2][0]-=tmp;
	}
	
	if(cnt[1][1]<=cnt[1][0]){
		ll tmp=min(cnt[1][0]-cnt[1][1],cnt[2][1]);
		cnt[1][1]+=tmp;
		cnt[2][1]-=tmp;
	}
	else{
		ll tmp=min(cnt[1][1]-cnt[1][0],cnt[2][0]);
		cnt[1][0]+=tmp;
		cnt[2][0]-=tmp;
	}
	
//	cout<<cnt[0][0]<<' '<<cnt[0][1]<<' '<<cnt[1][0]<<' '<<cnt[1][1]<<' '<<cnt[2][0]<<' '<<cnt[2][1]<<endl;
	cout<<n-2*(min(cnt[0][1],cnt[0][0])+min(cnt[1][1],cnt[1][0])+min(cnt[2][1],cnt[2][0]))<<endl;
	
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
// 1 2 3
// 4 5 6
// 1 2 3 . . . (36)
// 1 . 2 3 . .
// 
