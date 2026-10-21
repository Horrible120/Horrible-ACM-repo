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
	vector<ll> v(n+1);
	long double mg=-1;
	ll ans=0;
	for(ll i=1;i<=n;i++) cin>>v[i];
//	OOO
	for(ll i=1;i<=n;i++){
		if(v[i]==1&&mg!=-1){
			cout<<-1<<endl;
			return;
		}
		else if(mg==-1){
			if(v[i]>1){
				long double tmp=std::log2l(std::log2l((long double)v[i]));
//				OOO
//				cout<<tmp<<endl;
				mg=tmp;
			}
			
			continue;
		}
		else{
			long double tmp=std::log2l(std::log2l((long double)v[i]));
//			OOO
//			cout<<tmp<<endl;
			if(mg>tmp){
				ll c=ceil((long double)mg-(long double)tmp);
				ans+=c;
				mg=tmp+c;
			}
			else
				mg=max(mg,tmp);
		}
		
	}
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
