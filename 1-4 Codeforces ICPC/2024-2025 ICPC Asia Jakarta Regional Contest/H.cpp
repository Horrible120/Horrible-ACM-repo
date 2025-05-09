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

vector<ll> Z_Algo(string s){
	ll n=s.size();
	vector<ll> z(n,0);
	for(ll i=1,l=0,r=0;i<n;i++){
		if(i<=r&&i+z[i-l]<=r)
			z[i]=z[i-l];
		else{
			z[i]=max(0ll,r+1-i);
			while(i+z[i]<n&&s[i+z[i]]==s[z[i]])
				++z[i];
		}
		if(i+z[i]-1>r){
			r=i+z[i]-1;
			l=i;
		}
	}
	return z;
}

void solve(){
	string s;
	cin>>s;
	ll n=s.size();
	
	v2ct<ll> dp(n,vector<ll>(n,1));
	v2ct<ll> suf(n,vector<ll>(n,1));
	vector<ll> cut(n,n-1);
	
	for(ll l=n-2;l>=0;l--){
		auto z=Z_Algo(s.substr(l));
//		for(auto it:z)
//			cout<<it<<endl;
		for(ll r=n-2;r>=l;r--){
			ll len=min(z[r-l+1],r-l+1);
			if(r+len<n-1)
				if(len==r-l+1||s[r+len+1]>s[l+len]){
					dp[l][r]=suf[r+1][r+len+1]+1;
//					cout<<"!!! "<<l<<' '<<r<<' '<<len<<' '<<dp[l][r]<<endl;
				}
			suf[l][r]=max(suf[l][r+1],dp[l][r]);
		}
	}
//	OOO
	cout<<suf[0][0]<<endl;
	ll cnt=suf[0][0];
	ll l=0;
	while(l<n){
		for(ll i=n-1;i>=l;i--)
			if(dp[l][i]==cnt){
				cout<<s.substr(l,i-l+1)<<endl;
				l=i+1;
				cnt--;
				break;
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
	}
	
	cout.flush();
	return 0;
}
