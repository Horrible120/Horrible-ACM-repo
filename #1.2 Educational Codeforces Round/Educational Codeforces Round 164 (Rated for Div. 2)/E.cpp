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

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll n,m;
ll h[100010];
ll diff[100010];


int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin>>n;
	
	for(ll i=1;i<=n;i++)
		cin>>h[i],m=max(m,h[i]);
	
//	cout<<m<<endl;
	
	for(ll i=1;i<=n;i++){
		if(h[i]>h[i-1]){
			ll l=1,r=0;
			while(l<=h[i]){
				if(l==h[i]){
					diff[l]+=1;
					break;
				}
				r=min(m,(h[i]-1)/((h[i]-1)/l));
				
//				cout<<l<<' '<<r<<endl;
				diff[l]+=(h[i]+l-1)/l;
				diff[r+1]-=(h[i]+l-1)/l;
				
				l=r+1;
			}
			l=1,r=0;
//			cout<<l<<' '<<r<<endl;
			while(l<=h[i-1]){
				if(l==h[i-1]){
					diff[l]-=1;
					break;
				}
				r=min(m,(h[i-1]-1)/((h[i-1]-1)/l));
				
//				cout<<l<<' '<<r<<endl;
				diff[l]-=(h[i-1]+l-1)/l;
				diff[r+1]+=(h[i-1]+l-1)/l;
				
				l=r+1;
			}
		}
	}
	
	ll ans=0;
	for(ll i=1;i<=m;i++){
		ans+=diff[i];
		cout<<ans<<' ';
	}
	cout<<endl;
	return 0;
}
