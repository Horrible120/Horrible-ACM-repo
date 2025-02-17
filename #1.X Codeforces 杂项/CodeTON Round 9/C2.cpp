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

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll x,m,ans=0,ans1=0,ans2=0;
		cin>>x>>m;
		
		ll k=log2(x)+1;
		ll p=1ll<<k;
		
		vector<ll> cnt(p+1);
		
		for(ll i=1;i<=min(m,p);i++){
			if((x^i)%i==0&&(x^i)%x!=0) ans1++;
			cnt[(x^i)%x]++;
		}
		
		for(ll i=1;i*p<=m&&i<=x;i++)
			ans2+=cnt[(x-((i-1)*p)%x)%x];
		
		if(m>=x*p)
			ans+=(m/(x*p))*ans2;
		
		for(ll i=x*(m/(x*p))+1;i*p<=m;i++)
			ans+=cnt[(x-((i-1)*p)%x)%x];
		
		for(ll i=p*(m/p)+1;i<=m;i++)
			if((i^x)%x==0) ans++;
		
		cout<<ans+ans1<<endl;
	}
	
	cout.flush();
	
	return 0;
}
