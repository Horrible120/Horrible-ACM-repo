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
	ll n,k,sum=0;
	cin>>n>>k;
	vector<ll> a(n+1,0),b(n+1,0),pref(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
		pref[i]=pref[i-1]+a[i];
	}
	
	for(ll i=1;i<=n;i++){
		cin>>b[i];
		b[i]--;
	}
	
	vector<ll> nxt(n+1,0),lst(n+1,0);
	ll cur=0;
	for(ll i=1;i<=2*n;i++){
		if(b[(i-1)%n+1]==0) cur=(i-1)%n+1;
		lst[(i-1)%n+1]=cur;
	}
	
	if(!lst[1]){
//		OOO
		for(ll i=1;i<=n;i++){
			cout<<sum*2<<' ';
		}
		cout<<endl;
		return;
	}
	
	vector<ll> ans(n+1,0),dis(n+1,0);
	
	for(ll i=1;i<=n;i++){
		dis[lst[i]]+=a[i];
	}
	
	for(ll i=1;i<=n;i++){
		if(b[i]==0){
			ans[0]+=max(0LL,dis[i]-k);
		}
	}
	
//	for(ll i=1;i<=n;i++){
//		cout<<i<<' '<<lst[i]<<' '<<dis[i]<<endl;
//	}
	
	for(ll i=1;i<=n;i++){
		if(b[i]==0){
			ans[i]=ans[0];
		}else{
			ans[i]=ans[0]-max(0LL,dis[lst[i]]-k);
			ll tmp;
			if(lst[i]<i){
				tmp=pref[i-1]-pref[lst[i]-1];
			}else{
				tmp=pref[i-1]+pref[n]-pref[lst[i]-1];
			}
			
			ans[i]+=max(0LL,tmp-k)+dis[lst[i]]-tmp;
			
		}
	}
	
//	OOO
	
	for(ll i=1;i<=n;i++){
		cout<<ans[i]+sum<<' ';
	}
	
	cout<<endl;
	
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
