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
	ll n,k,ans=0;
	cin>>n>>k;
	
	vector<ll> vld(n+1,1);
	
	if(k==1){
		
		for(ll i=1;i<=n;i++){
			for(ll j=i+1;j<=n;j++){
				string x;
				cout<<"R"<<endl;
				cout<<"? "<<i<<endl;
				cin>>x;
				cout<<"? "<<j<<endl;
				cin>>x;
				if(x[0]=='Y'){
					vld[j]=0;
				}
			}
		}
		
		for(ll i=1;i<=n;i++){
			if(vld[i]) ans++;
		}
		
		cout<<"! "<<ans<<endl;
		
		
		return;
	}
	
	if(k==n){
		for(ll i=1;i<=n;i++){
			string x;
			cout<<"? "<<i<<endl;
			cin>>x;
			if(x[0]=='Y'){
				vld[i]=0;
			}
		}
		
		for(ll i=1;i<=n;i++){
			if(vld[i]) ans++;
		}
		
		cout<<"! "<<ans<<endl;
		
		
		return;
	}
	
	ll m=n/k;
	ll g=k/2;
	
	for(ll i=1;i<=m*2;i++){
		for(ll j=1;j<=i&&j+i<=m*2;j++){
			cout<<"R"<<endl;
			for(ll l=j;l<=m*2;l+=i){
				string x;
				for(ll p=(l-1)*g+1;p<=l*g;p++){
					cout<<"? "<<p<<endl;
					cin>>x;
					if(x[0]=='Y'){
						vld[p]=0;
					}
				}
			}
		}
	}
	for(ll i=1;i<=n;i++){
		if(vld[i]) ans++;
	}
	
	cout<<"! "<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
