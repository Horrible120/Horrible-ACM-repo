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
	vector<ll> v(n),vis(n);
	for(ll i=0;i<n;i++){
		cin>>v[i];
	}
	ll mx=-1,a=INF,b=0;
	sort(v.begin(),v.end());
	for(ll i=n-1;i>0;i--){
		if(v[i]==v[i-1]&&mx==-1){
			mx=i;
			vis[i]=vis[i-1]=1;
		}
		
	}
	for(ll i=n-1;i>0;i--){
		if(vis[i]==0&&vis[i-1]==0&&v[i]-v[i-1]<a-b){
			a=v[i];
			b=v[i-1];
		}
	}
	if(mx+1<n&&mx-2>=0){
		if(v[mx+1]-v[mx-2]<a-b){
			a=v[mx+1];
			b=v[mx-2];
		}
	}
	
//	OOO
	if(mx!=-1&&v[mx]*2>a-b) cout<<v[mx]<<' '<<v[mx]<<' '<<a<<' '<<b<<endl;
	else cout<<-1<<endl;
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
