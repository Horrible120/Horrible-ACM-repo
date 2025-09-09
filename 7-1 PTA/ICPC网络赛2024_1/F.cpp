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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),ld(n+1,0),rd(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	{
		vector<ll> stk(n+1,0);
		ll top=0;
		for(ll i=1;i<=n;i++){
			while(top>0&&v[stk[top]]<v[i]){
				top--;
			}
			ld[i]=stk[top];
			stk[++top]=i;
		}
	}
	
	{
		vector<ll> stk(n+1,0);
		ll top=0;
		for(ll i=n;i>=1;i--){
			while(top>0&&v[stk[top]]<v[i]){
				top--;
			}
			rd[i]=stk[top];
			stk[++top]=i;
		}
	}
	
	ll ans=0;
	
	for(ll i=1;i<=n;i++){
		ll lt=ld[i],rt=rd[i];
		if(lt==0){
			ans+=i-1;
		}else if(v[lt]!=v[i]){
			ans+=(i-lt)-1;
		}
		
		if(rt==0){
			ans+=n-i;
		}else{
			ans+=(rt-i)-1;
		}
	}
//	OOO
	cout<<ans<<endl;
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
