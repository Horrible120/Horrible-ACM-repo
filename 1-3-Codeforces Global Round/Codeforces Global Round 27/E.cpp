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
		ll x,y,z,k,ans=INF;
		cin>>x>>y>>z>>k;
		for(ll r=0;;r++){
//			此时剩余血量 h || 当前基础伤害 dmg || 当前基础花费 cost
			ll h=z-r*(r+1)*k/2,dmg=r*k,cost=r*(k*x+y);
			
			if(h<=0){
				ans=min(ans,cost);
				break;
			}
			else{						/*如果不在这里做 l<=min(dmg+k,h) 的处理的话，
											要么会在这一步突破 K 的限制，
											要么会因为取到了大于 h 的数，
											此时下取整为 0 ，则右边界可以取到无穷大*/
					
				for(ll l=max(dmg,1ll);l<=min(dmg+k,h);){
					ans=min(ans,cost+(l-dmg)*x+(ll)ceil(1.0*h/l)*y);
					l=l^h?((h-1)/((h-1)/l)+1):(h+1);
				}
				
//				不做整除分块优化的代码，会TLE
//				for(ll l=max(dmg,1ll);l<=min(dmg+k,h);l++){
//					ans=min(ans,cost+(l-dmg)*x+(ll)ceil(1.0*h/l)*y);
//				}
				
			}
		}
		cout<<ans<<endl;
	}
	
	cout.flush();
	
	return 0;
}
