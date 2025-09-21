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
ll p[4]={0,1,-1,0};

void solve(){
	ll n;
	cin>>n;
//	vector<ll> vis((1<<n)+1,0);
//	auto DFS=[&](auto &&self,ll cur,ll last,ll d)->void{
//		if(d==0){
//			vis[cur]=1;
//			return;
//		}else if(last!=0){
//			for(ll i=1;i<=3;i++){
//				self(self,cur+p[i]*(1<<d-1),p[i],d-1);
//			}
//		}else{
//			for(ll i=1;i<=2;i++){
//				self(self,cur+p[i]*(1<<d-1),p[i],d-1);
//			}
//		}
//	};
//	
//	DFS(DFS,0,1,n);
//	
//	for(ll i=0;i<=(1<<n);i++){
//		cout<<i<<' '<<vis[i]<<endl;
//	}
	
	vector<ll> ans(32,-1);
	
	if(n%4==0){
		cout<<"NO"<<endl;
		return;
	}
	
	cout<<"YES"<<endl;
	
	ans[31]=1;
	
	for(ll i=2;i<=30;i++){
		if((n&(1<<i))){
			ans[i-1]=1;
		}
	}
	
	if(n%4==1){
		ans[0]=-1;
	}else if(n%4==2){
		ans[0]=0;
	}else{
		ans[0]=1;
	}
	
	for(ll i=0;i<=31;i++){
		cout<<ans[i]<<" \n"[i%8==7];
	}
	
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
