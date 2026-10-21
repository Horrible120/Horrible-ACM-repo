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
	cin>>n>>q;
	vector<ll> v(n+2,0),ans(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	sort(v.begin()+1,v.begin()+n+1);
	
	if(n==1){
		for(ll i=1;i<=q;i++){
			ll k;
			cin>>k;
			if(k%2==1){
				cout<<v[1]+(k+1)/2<<' ';
			}else{
				cout<<v[1]-(k+1)/2<<' ';
			}
		}
		cout<<endl;
		return;
	}
	
	ans[0]=v[1];
	v[n+1]=v[n]+1;
	
	ll m1=0,m2=0;
	
	for(ll i=1;i<=n;i++){
		ans[i]=min(ans[i-1]+1,v[i+1]);
//		cout<<i<<' '<<ans[i]<<endl;
	}
	
	for(ll i=1;i<=n;i++){
		m1+=v[i]+n-i+1-ans[n];
	}
	
	for(ll i=1;i<=n-1;i++){
		m2+=v[i]+n-i-ans[n-1];
	}
	
//	OOO
//	cout<<m1<<' '<<m2<<endl;
	
	for(ll i=1;i<=q;i++){
		ll k;
		cin>>k;
		if(k<=n){
			cout<<ans[k]<<' ';
		}else if((k-n)%2==0){
			ll tmp=(k-n)/2;
			if(tmp<=m1){
				cout<<ans[n]+k-n<<' ';
			}else{
				cout<<ans[n]+k-n-(tmp-m1+n-1)/n<<' ';
			}
		}else{
			ll tmp=(k-n+1)/2;
			if(ans[n-1]+k-n+1>v[n]){
				if(tmp<=m2){
					cout<<v[n]<<' ';
				}else if((tmp-m2)<=(ans[n-1]+k-n+1-v[n])*(n-1)){
					cout<<v[n]<<' ';
				}else{
					cout<<v[n]-((tmp-m2)-(ans[n-1]+k-n+1-v[n])*(n-1)+n-1)/n<<' ';
				}
			}else{
				if(tmp<=m2+v[n]-(ans[n-1]+k-n+1)){
					cout<<ans[n-1]+k-n+1<<' ';
				}else{
					cout<<ans[n-1]+k-n+1-(tmp-(m2+v[n]-(ans[n-1]+k-n+1))+n-1)/n<<' ';
				}
			}
		}
	}
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
