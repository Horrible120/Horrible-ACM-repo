#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;

const ll INF = 1e18,
Mod = 1e9+7;

const ll MAXN=1000010;

ll n,a,b,sa,sb,ans;
ll dp[50][50];


int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cout<<__gcd(217152,510510)<<endl;
	
	cin>>n>>a>>b;
	
	for(ll i=n;i>=1&&(!sa);i--)
		if(__gcd(i,a)==1)
			sa=i;
	for(ll i=n;i>=1&&(!sb);i--)
		if(__gcd(i,b)==1)
			sb=i;
	
//	cout<<sa<<' '<<sb<<endl;
	
	for(ll i=1;i<=sa;i++)
		ans+=__gcd(i,a)+1;
	for(ll i=2;i<=sb;i++)
		ans+=__gcd(i,b)+1;
	
	for(ll i=sa;i<n+4;i++)
		dp[0][i-sa]=INF;
	for(ll i=sb;i<n+4;i++)
		dp[i-sb][0]=INF;
	
	ll A=sa-1,B=sb-1;
	for(ll i=sa;i<=n;i++)
		for(ll j=sb;j<=n;j++)
			if(i==sa&&j==sb) dp[i-A][j-B]=0;
			else dp[i-A][j-B]=__gcd(i,a)+__gcd(j,b)+min(dp[i-A-1][j-B],dp[i-A][j-B-1]);
	
	cout<<dp[n-A][n-B]+ans<<endl;
		
	cout.flush();
	
	return 0;
}
