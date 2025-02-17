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
v2ct<ll> fct(5001,vector<ll>());

void solve(){
	ll a,b;
	cin>>a>>b;
	queue<tuple<ll,ll,ll>> q;
	q.push(make_tuple(a/__gcd(a,b),b/__gcd(a,b),0));
	while(q.size()){
		auto [x,y,cnt]=q.front();
		q.pop();
		if(x+y==1){
			cout<<cnt+1<<endl;
			break;
		}
		else{
			q.push(make_tuple((x-1)/__gcd(x-1,y),y/__gcd(x-1,y),cnt+1));
			q.push(make_tuple(x/__gcd(x,y-1),(y-1)/__gcd(x,y-1),cnt+1));
		}
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	for(ll i=1;i<=5000;i++)
		for(ll j=i;j<=5000;j+=i)
			fct[j].emplace_back(i);
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
