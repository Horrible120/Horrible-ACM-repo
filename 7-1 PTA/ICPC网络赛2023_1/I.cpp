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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	string s;
	cin>>s;
	
	vector<ll> v(n+1,0);
	
	for(ll i=0;i<n;i++){
		if('0'<=s[i]&&s[i]<='9'){
			v[i+1]=s[i]-'0'+1;
		}else if(s[i]>='a'&&s[i]<='z'){
			v[i+1]=s[i]-'a'+1+10;
		}else if(s[i]>='A'&&s[i]<='Z'){
			v[i+1]=s[i]-'A'+1+10+26;
		}else{
			v[i+1]=0;
		}
	}
	
	vector dp(71,array<array<array<ll,2>,2>,2>()),tmp(71,array<array<array<ll,2>,2>,2>());
	
	for(ll i=1;i<=63;i++){
		for(ll k1=0;k1<=1;k1++){
			for(ll k2=0;k2<=1;k2++){
				for(ll k3=0;k3<=1;k3++){
					dp[i][k1][k2][k3]=0;
				}
			}
		}
	}
	
	auto z=dp;
	
	if(v[1]==0){
		for(ll j=1;j<=62;j++){
			if(j<=10){
				dp[j][1][0][0]=1;
			}else if(j<=36){
				dp[j][0][1][0]=1;
			}else{
				dp[j][0][0][1]=1;
			}
		}
	}else if(v[1]<=10){
		dp[v[1]][1][0][0]=1;
	}else if(v[1]<=36){
		dp[v[1]][0][1][0]=1;
		dp[v[1]+26][0][0][1]=1;
	}else{
		dp[v[1]][0][0][1]=1;
	}
	
	for(ll j=1;j<=62;j++){
		for(ll k1=0;k1<=1;k1++){
			for(ll k2=0;k2<=1;k2++){
				for(ll k3=0;k3<=1;k3++){
					dp[63][k1][k2][k3]+=dp[j][k1][k2][k3];
				}
			}
		}
	}
	
//	for(ll k1=0;k1<=1;k1++){
//		for(ll k2=0;k2<=1;k2++){
//			for(ll k3=0;k3<=1;k3++){
//				cout<<"    "<<k1<<' '<<k2<<' '<<k3<<' '<<dp[63][k1][k2][k3]<<endl;
//			}
//		}
//	}
	
	// 63 = sum
	
	for(ll i=2;i<=n;i++){
		tmp=dp;
		dp=z;
		if(v[i]==0){
			for(ll j=1;j<=62;j++){
				if(j<=10){
					dp[j][1][1][1]=tmp[63][0][1][1]+tmp[63][1][1][1]-tmp[j][0][1][1]-tmp[j][1][1][1];
					dp[j][1][0][1]=tmp[63][0][0][1]+tmp[63][1][0][1]-tmp[j][0][0][1]-tmp[j][1][0][1];
					dp[j][1][1][0]=tmp[63][0][1][0]+tmp[63][1][1][0]-tmp[j][0][1][0]-tmp[j][1][1][0];
					dp[j][1][0][0]=tmp[63][1][0][0]-tmp[j][1][0][0];
				}else if(j<=36){
					dp[j][1][1][1]=tmp[63][1][0][1]+tmp[63][1][1][1]-tmp[j][1][0][1]-tmp[j][1][1][1];
					dp[j][0][1][1]=tmp[63][0][0][1]+tmp[63][0][1][1]-tmp[j][0][0][1]-tmp[j][0][1][1];
					dp[j][1][1][0]=tmp[63][1][0][0]+tmp[63][1][1][0]-tmp[j][1][0][0]-tmp[j][1][1][0];
					dp[j][0][1][0]=tmp[63][0][1][0]-tmp[j][0][1][0];
				}else{
					dp[j][1][1][1]=tmp[63][1][1][0]+tmp[63][1][1][1]-tmp[j][1][1][0]-tmp[j][1][1][1];
					dp[j][0][1][1]=tmp[63][0][1][0]+tmp[63][0][1][1]-tmp[j][0][1][0]-tmp[j][0][1][1];
					dp[j][1][0][1]=tmp[63][1][0][0]+tmp[63][1][0][1]-tmp[j][1][0][0]-tmp[j][1][0][1];
					dp[j][0][0][1]=tmp[63][0][0][1]-tmp[j][0][0][1];
				}
			}
		}else if(v[i]<=10){
			ll j=v[i];
			{
				dp[j][1][1][1]=tmp[63][0][1][1]+tmp[63][1][1][1]-tmp[j][0][1][1]-tmp[j][1][1][1];
				dp[j][1][0][1]=tmp[63][0][0][1]+tmp[63][1][0][1]-tmp[j][0][0][1]-tmp[j][1][0][1];
				dp[j][1][1][0]=tmp[63][0][1][0]+tmp[63][1][1][0]-tmp[j][0][1][0]-tmp[j][1][1][0];
				dp[j][1][0][0]=tmp[63][1][0][0]-tmp[j][1][0][0];
			}
			
		}else if(v[i]<=36){
			ll j=v[i];
			{
				dp[j][1][1][1]=tmp[63][1][0][1]+tmp[63][1][1][1]-tmp[j][1][0][1]-tmp[j][1][1][1];
				dp[j][0][1][1]=tmp[63][0][0][1]+tmp[63][0][1][1]-tmp[j][0][0][1]-tmp[j][0][1][1];
				dp[j][1][1][0]=tmp[63][1][0][0]+tmp[63][1][1][0]-tmp[j][1][0][0]-tmp[j][1][1][0];
				dp[j][0][1][0]=tmp[63][0][1][0]-tmp[j][0][1][0];
			}
			j=v[i]+26;
			{
				dp[j][1][1][1]=tmp[63][1][1][0]+tmp[63][1][1][1]-tmp[j][1][1][0]-tmp[j][1][1][1];
				dp[j][0][1][1]=tmp[63][0][1][0]+tmp[63][0][1][1]-tmp[j][0][1][0]-tmp[j][0][1][1];
				dp[j][1][0][1]=tmp[63][1][0][0]+tmp[63][1][0][1]-tmp[j][1][0][0]-tmp[j][1][0][1];
				dp[j][0][0][1]=tmp[63][0][0][1]-tmp[j][0][0][1];
			}
		}else{
			ll j=v[i];
			{
				dp[j][1][1][1]=tmp[63][1][1][0]+tmp[63][1][1][1]-tmp[j][1][1][0]-tmp[j][1][1][1];
				dp[j][0][1][1]=tmp[63][0][1][0]+tmp[63][0][1][1]-tmp[j][0][1][0]-tmp[j][0][1][1];
				dp[j][1][0][1]=tmp[63][1][0][0]+tmp[63][1][0][1]-tmp[j][1][0][0]-tmp[j][1][0][1];
				dp[j][0][0][1]=tmp[63][0][0][1]-tmp[j][0][0][1];
			}
		}
		
		for(ll j=1;j<=62;j++){
			for(ll k1=0;k1<=1;k1++){
				for(ll k2=0;k2<=1;k2++){
					for(ll k3=0;k3<=1;k3++){
						dp[63][k1][k2][k3]+=dp[j][k1][k2][k3];
					}
				}
			}
		}
		
		for(ll j=1;j<=63;j++){
			for(ll k1=0;k1<=1;k1++){
				for(ll k2=0;k2<=1;k2++){
					for(ll k3=0;k3<=1;k3++){
						dp[j][k1][k2][k3]=(dp[j][k1][k2][k3]%Mod+Mod)%Mod;
					}
				}
			}
		}
		
//		cout<<i<<endl;
//		
//		for(ll k1=0;k1<=1;k1++){
//			for(ll k2=0;k2<=1;k2++){
//				for(ll k3=0;k3<=1;k3++){
//					cout<<"    "<<k1<<' '<<k2<<' '<<k3<<' '<<dp[63][k1][k2][k3]<<endl;
//				}
//			}
//		}
		
	}
	
	ll ans=0;
	ans=dp[63][1][1][1];
	
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
