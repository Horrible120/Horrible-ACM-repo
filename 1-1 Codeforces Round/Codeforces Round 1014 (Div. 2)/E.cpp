
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
	ll n,m,k;
	cin>>n>>m>>k;
	
	ll bcnt[2]={};
	
	for(ll i=1;i<=k;i++){
		ll x,y,c;
		cin>>x>>y>>c;
		if(((x==1||x==n)&&(y>1&&y<m))||((y==1||y==m)&&(x>1&&x<n)))
			bcnt[c]++;
	}
	
	ll bsum=2*(n-2)+2*(m-2);
	
	if(bcnt[1]+bcnt[0]==bsum&&bcnt[0]%2==1){
		cout<<0<<endl;
		return;
	}
	else if(bcnt[1]+bcnt[0]==bsum&&bcnt[0]%2==0){
		ll tot=0;
		tot=n*m-k;
		ll c=2,ans=1;
		while(tot){
			if(tot&1ll){
				ans=ans*c%Mod;
			}
			c=c*c%Mod;
			tot/=2;
		}
		cout<<ans<<endl;
	}
	else{
		ll tot=0;
		tot=n*m-k-1;
		ll c=2,ans=1;
		while(tot){
			if(tot&1ll){
				ans=ans*c%Mod;
			}
			c=c*c%Mod;
			tot/=2;
		}
		cout<<ans<<endl;
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
