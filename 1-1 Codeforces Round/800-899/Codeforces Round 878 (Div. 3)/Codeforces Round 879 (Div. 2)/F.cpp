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

void solve(){
	ll n,q;
	cin>>n;
	vector<ll> v(n+1,0);
	vector<ll> diff(n+2,0);
	vector<vector<ll>> ans(2,vector<ll>(n+1,0));
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(v[i]<i){
			diff[0]++;
			diff[n-i+1]--;
			diff[n-i+v[i]+1]++;
		}else{
			diff[v[i]-i+1]++;
			diff[n-i+1]--;
		}
	}
	
	for(ll i=0;i<n;i++){
		ans[0][i]+=diff[i];
		ans[0][i+1]+=ans[0][i];
	}
	
	reverse(v.begin()+1,v.end());
	for(ll i=0;i<=n;i++){
		diff[i]=0;
	}
	
	for(ll i=1;i<=n;i++){
		if(v[i]<i){
			diff[0]++;
			diff[n-i+1]--;
			diff[n-i+v[i]+1]++;
		}else{
			diff[v[i]-i+1]++;
			diff[n-i+1]--;
		}
	}
	
	for(ll i=0;i<n;i++){
		ans[1][i]+=diff[i];
		ans[1][i+1]+=ans[1][i];
	}
	
	cin>>q;
	ll cur=0,tp=1;
	
//	OOO
	cout<<ans[0][cur]<<endl;
	
	while(q--){
		ll op,k;
		cin>>op;
		if(op==1){
			cin>>k;
			cur-=k*tp;
		}else if(op==2){
			cin>>k;
			cur+=k*tp;
		}else{
			tp*=-1;
		}
		
//		OOO
		if(tp==-1){
			cout<<ans[1][((-cur)%n+n)%n]<<endl;
		}else{
			cout<<ans[0][(cur%n+n)%n]<<endl;
		}
		
	}
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
