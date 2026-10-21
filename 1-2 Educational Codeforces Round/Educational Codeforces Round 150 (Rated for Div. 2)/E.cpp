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
	ll n,sum=0,ans=0;
	cin>>n;
	vector<ll> v(n+2,0);
	for(ll i=1;i<=n;i++) cin>>v[i];
	
	cin>>sum;
	
	ll top=0;
	vector<ll> stk(n+3,0),cnt(n+1,0);
	
	stk[++top]=0;
	v[0]=n;
	
	for(ll i=1;i<=n;i++){
		ll hi=0;
		while(top>0&&v[i]>=v[stk[top]]){
			cnt[i-stk[top]-1]+=v[stk[top]]-hi;
			hi=v[stk[top]];
			top--;
		}
		cnt[i-stk[top]-1]+=v[i]-hi;
		stk[++top]=i;
	}
	
	ll hi=0;
	while(top){
		cnt[n-stk[top]]+=v[stk[top]]-hi;
		hi=v[stk[top]];
		--top;
	}
	
	for(ll i=n;i>=1;i--){
//		cout<<">>> "<<i<<' '<<cnt[i]<<endl;
		if(sum>=i*cnt[i]){
			ans+=(i-1)*cnt[i];
			sum-=i*cnt[i];
		}else if(sum>0){
			ans+=(sum/i)*(i-1);
			sum%=i;
			if(sum>0){
				ans+=sum-1;
				sum=0;
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
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
