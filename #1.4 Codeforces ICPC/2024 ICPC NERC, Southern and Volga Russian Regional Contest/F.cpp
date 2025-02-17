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

ll Xor(ll m){
	if(m<=0) return 0;
	ll ans=0,cnt=1;
	while(m>=cnt){
		if(((m/(2*cnt))*cnt+max(0ll,m%(2*cnt)+1-cnt))%2)
			ans+=cnt;
		cnt<<=1;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll l,r,i,k,m,ans=0;
		cin>>l>>r>>i>>k;
		
		m=1<<i;
		l-=1;
		
		if(i==0){
			cout<<0<<endl;
			continue;
		}
		
		ll tl=(l/m)+((l%m>=k)?1:0);
		ll tr=(r/m)+((r%m>=k)?1:0);
		
//		cout<<tl<<' '<<tr<<' '<<Xor(r)<<endl;
		
		ans=Xor(l)^Xor(r)^((Xor(max(tl-1,0ll))^Xor(max(tr-1,0ll)))<<i)^(((tr-tl)%2)?k:0);
	
		cout<<ans<<endl;
	}
	
	cout.flush();
	
	return 0;
}
