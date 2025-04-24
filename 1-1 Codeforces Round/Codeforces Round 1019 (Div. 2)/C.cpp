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
	vector<ll> v(n+1,0),vis(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(v[i]<=k) vis[i]=1;
		vis[i]+=vis[i-1];
	}
	
	ll flag=1;
	
//	for(ll i=1;i<=n-2&&flag;i++){
//		
//		if(vis[i]>=(i+1)/2){
//			for(ll j=i+1;j<=n-1;j++)
//				if(vis[j]-vis[i]>=(j-i+1)/2||vis[n]-vis[j]>=(n-j+1)/2)
//					flag=0;
//		}
//		else{
//			for(ll j=i+1;j<=n-1;j++)
//				if(vis[j]-vis[i]>=(j-i+1)/2&&vis[n]-vis[j]>=(n-j+1)/2)
//					flag=0;
//		}
//	}
	
	ll aa=0,bb=0;
	for(ll i=1;i<=n-2&&aa==0;i++)
		if(vis[i]>=(i+1)/2)
			aa=i;
	
	for(ll i=n;i>=3&&bb==0;i--)
		if(vis[n]-vis[i-1]>=(n-i+2)/2)
			bb=i;
	
//	cout<<">>> "<<aa<<' '<<bb<<endl;
	
	if(aa&&bb&&aa<bb-1){
		cout<<"YES"<<endl;
		return;
	}
//	10 7 12 16 3 15 5 11
	if(aa&&aa<n-2&&vis[aa]==vis[aa+1]&&vis[aa+1]>=(aa+2)/2)
		aa++;
	if(bb&&bb>3&&vis[n]-vis[bb-1]==vis[n]-vis[bb-2]&&vis[n]-vis[bb-2]>=(n-bb+3)/2)
		bb--;
	
	if(aa)
	for(ll i=aa+1;i<=n-1&&flag;i++){
		if(vis[i]-vis[aa]>=(i-aa+1)/2)
			flag=0;
	}
	
	if(bb)
	for(ll i=bb-1;i>=2&&flag;i--){
		if(vis[bb-1]-vis[i-1]>=(bb-i+1)/2)
			flag=0;
	}
	
	if(flag)
		cout<<"NO"<<endl;
	else
		cout<<"YES"<<endl;
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
