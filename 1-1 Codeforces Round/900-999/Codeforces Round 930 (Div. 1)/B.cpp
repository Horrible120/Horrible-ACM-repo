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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),pr0(n+1,0),pr1(n+1,0),idx1(n+1,0),idx0(n+1,0),ans(n+1,0);
	
	string s;
	ll cnt0=0,cnt1=0;
	cin>>s;
	
	for(ll i=1;i<=n;i++){
		v[i]=(s[i-1]=='<'?0:1);
		
		if(v[i]==0){
			idx0[i]=++cnt0;
			idx1[i]=cnt1;
			pr0[cnt0]=pr0[cnt0-1]+i;
		}
		else{
			idx0[i]=cnt0;
			idx1[i]=++cnt1;
			pr1[cnt1]=pr1[cnt1-1]+i;
		}
//		cout<<v[i]<<'|'<<pr0[idx0[i]]<<'|'<<pr1[idx1[i]]<<' ';
	}
	
//	cout<<endl;
	
	for(ll i=1;i<=n;i++){
		ll k1=idx1[i],k0=cnt0-idx0[i]+(v[i]==0?1:0);
		ll len=min(k0,k1);
		
//		cout<<"!!! "<<i<<' '<<k0<<' '<<k1<<endl;
		
		if(len){
			if(v[i]==0){
				ans[i]+=pr0[idx0[i]+len-1]-pr0[idx0[i]-1];
				ans[i]-=pr1[idx1[i]]-pr1[idx1[i]-len];
				
				if(k1>=k0) ans[i]=ans[i]*2+n-i+1;
				else ans[i]=ans[i]*2+i+(pr0[idx0[i]+len]-pr0[idx0[i]+len-1]-i)*2;
			}
			else{
				ans[i]+=pr0[idx0[i]+len]-pr0[idx0[i]];
				ans[i]-=pr1[idx1[i]]-pr1[idx1[i]-len];
				
				if(k1<=k0) ans[i]=ans[i]*2+i;
				else ans[i]=ans[i]*2+n-i+1+(i-pr1[idx1[i]-len]+pr1[idx1[i]-len-1])*2;
			}
		}
		else{
			if(v[i]==0){
				if(k1>=k0) ans[i]=ans[i]*2+n-i+1;
				else ans[i]=ans[i]*2+i+(pr0[idx0[i]+len]-pr0[idx0[i]+len-1]-i)*2;
			}
			else{
				if(k1<=k0) ans[i]=ans[i]*2+i;
				else ans[i]=ans[i]*2+n-i+1+(i-pr1[idx1[i]-len]+pr1[idx1[i]-len-1])*2;
			}
		}
		
		
		cout<<ans[i]<<' ';
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
	}
	
	cout.flush();
	return 0;
}
