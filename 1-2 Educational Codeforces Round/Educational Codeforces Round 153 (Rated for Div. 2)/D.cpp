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
bitset<20001> dp[101][101];

void solve(){
	string s{};
	cin>>s;
	ll n=s.size();
	
	ll cnt[2]{},sum[2]{};	//01 10
	
	for(ll i=0;i<n;i++){
		if(s[i]=='0'){
			sum[1]+=cnt[1];
			cnt[0]++;
		}else{
			sum[0]+=cnt[0];
			cnt[1]++;
		}
	}
	
	ll tar=(sum[0]-sum[1])/2;
	
	
	
	ll ccnt[2]{};
	
	dp[0][0][10000]=1;
	
	for(ll i=0;i<n;i++){
		if(s[i]=='0'){
			ccnt[0]++;
			for(ll j=ccnt[0]-1;j>=0;j--){
				for(ll k=ccnt[1];k>=0;k--){
					dp[j+1][k]|=dp[j][k]>>(i+1);
				}
			}
		}else{
			ccnt[1]++;
			for(ll j=ccnt[0];j>=0;j--){
				for(ll k=ccnt[1]-1;k>=0;k--){
					dp[j][k+1]|=dp[j][k]<<(i+1);
				}
			}
		}
	}
	
//	cout<<tar<<endl;
	
	for(ll i=0;i<=n;i++){
		if(dp[i][i][10000+tar]){
			cout<<i<<endl;
			return;
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
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
