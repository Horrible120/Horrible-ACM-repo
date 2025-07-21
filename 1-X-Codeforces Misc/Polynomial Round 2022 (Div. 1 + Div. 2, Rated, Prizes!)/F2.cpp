#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,max_sum=1e9,ans=0;
	cin>>n;
	vector<ll> tp(n+1,0),v(n+1,0);
	
	
	{
		ll sum=0;
		for(ll i=1;i<=n;i++){
			cin>>tp[i];
			if(tp[i]!=3){
				cin>>v[i];
				if(tp[i]==2){
					sum+=v[i];
				}
			}else{
				v[i]=sum;
				sum=min(2*sum,max_sum);
			}
		}
	}
	
	{
		ll top=0,sum=0,res=1;
		vector<ll> stk(n+1,0);
		
		for(ll i=n;i>=1;i--){
			
			if(tp[i]==2){
				sum+=v[i];
			}
			
			if(tp[i]==3){
				if(v[i]>=max_sum) continue;
				else if(v[i]==0){
					res=res*2%Mod;
					continue;
				}
				else{
					stk[++top]=v[i];
				}
			}
			
			if(tp[i]==1){
				ll tmp=v[i]-sum,tm=1;
				if(tmp<=0) continue;
				for(ll j=1;j<=top;j++){
					if(tmp-stk[j]>0){
						tmp-=stk[j];
						tm=(tm+(1<<top-j))%Mod;
					}
				}
				ans=(ans+tm*res)%Mod;
			}
		}
	}
	
//	OOO
	cout<<ans<<endl;
	
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
