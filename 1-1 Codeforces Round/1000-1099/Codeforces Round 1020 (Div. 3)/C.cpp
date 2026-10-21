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
	ll n,k;
	cin>>n>>k;
	vector<ll> a(n+1,0),b(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=n;i++)
		cin>>b[i];
//	OOO
	ll sum=-1;
	for(ll i=1;i<=n;i++){
		if(a[i]>=0&&b[i]>=0){
			if(sum>=0&&a[i]+b[i]!=sum){
				cout<<0<<endl;
				return;
			}
			else{
				sum=a[i]+b[i];
			}
		}
	}
	
	if(sum>=0){
		for(ll i=1;i<=n;i++)
			if(b[i]==-1){
				if(sum-a[i]>k||sum-a[i]<0){
					cout<<0<<endl;
					return;
				}
			}
		cout<<1<<endl;
		return;
	}
	
	ll bx=0;
	for(ll i=1;i<=n;i++)
		sum=max(sum,a[i]);
	for(ll i=1;i<=n;i++){
		if(sum-a[i]>k||sum-a[i]<0){
			cout<<0<<endl;
			return;
		}
		else{
			bx=max(bx,sum-a[i]);
		}
	}
	cout<<k-bx+1<<endl;
	
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
