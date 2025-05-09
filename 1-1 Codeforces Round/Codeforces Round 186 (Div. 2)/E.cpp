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
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+1,0),b(n+1,0);
	multiset<ll> sb1;
	multiset<ll,greater<ll>> sb2,ans;
	
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=n;i++)
		cin>>b[i],
		sb1.insert(b[i]);
	
	sort(a.begin()+1,a.end(),greater<ll>());
	
	for(ll i=1;i<=n;i++){
		
		while(sb1.size()&&(*sb1.begin()<=m-a[i]-1))
			sb2.insert(*sb1.begin()),
			sb1.erase(sb1.begin());
		
//		cout<<sb1.size()<<' '<<sb2.size()<<endl;
		
		if(sb2.size()){
			ans.insert(a[i]+(*sb2.begin()));
			sb2.erase(sb2.begin());
			a[i]=-1;
		}
	}
	
	for(auto it:sb1)
		sb2.insert(it);
	
	for(ll i=1;i<=n;i++)
		if(a[i]>=0&&sb2.size())
			ans.insert(a[i]+(*sb2.begin())-m),
			sb2.erase(sb2.begin());
	
//	cout<<ans.size()<<endl;
	
	for(auto it:ans)
		cout<<it<<' ';
	cout<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
