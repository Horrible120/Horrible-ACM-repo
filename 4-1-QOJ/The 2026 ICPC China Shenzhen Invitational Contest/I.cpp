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
	ll n;
	cin>>n;
	
	vector<ll> ans(13,0);
	
	if(n>=34||(n>=23&&n<=32)||n==9||n==10||(n>=12&&n<=21)){
		cout<<"No"<<endl;
	}else{
		cout<<"Yes"<<endl;
		if(n<=8){
			ans[1]=ans[12]=0;
			for(ll i=2;i<=11;i++){
				if(i-1<n){
					ans[i]=i-1;
				}
			}
		}else if(n==11){
			ans[1]=ans[12]=0;
			n=9;
			for(ll i=2;i<=11;i++){
				if(i-1<n){
					ans[i]=i-1;
				}
			}
		}else if(n==22){
			ans[1]=ans[12]=0;
			ans[2]=ans[11]=1;
			n=9;
			for(ll i=3;i<=10;i++){
				if(i-1<n){
					ans[i]=i-1;
				}
			}
		}else if(n==33){
			ans[1]=ans[12]=0;
			ans[2]=ans[11]=1;
			ans[3]=ans[10]=2;
			n=9;
			for(ll i=4;i<=9;i++){
				if(i-1<n){
					ans[i]=i-1;
				}
			}
		}
		
		for(ll i=1;i<=12;i++){
			cout<<ans[i]<<' ';
		}
		cout<<endl;
	}
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
