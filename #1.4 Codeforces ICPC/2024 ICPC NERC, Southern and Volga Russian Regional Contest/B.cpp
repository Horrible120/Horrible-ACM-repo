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

bool check(vector<ll> v,ll h,ll n){
	for(ll i=1;i<=n;i++)
		v[i]-=h;
//	for(ll i=1;i<=n;i++)
//		cout<<v[i]<<' ';
//	cout<<endl;
	ll f=1;
	
	while(f){
		f=0;
		for(ll i=1;i<=n;i++)
			if(v[i]>0){
				v[(i%n)+1]+=(v[i]+1)/2;
				v[i]-=2*((v[i]+1)/2);
				
			}
		for(ll i=1;i<=n;i++)
			if(v[i]>0) f=1;
	}
	
	for(ll i=1;i<=n;i++)
		if(v[i])
			return 0;
	return 1;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n,sum=0;
		cin>>n;
		vector<ll> v(n+1);
		for(ll i=1;i<=n;i++)
			cin>>v[i],sum+=v[i];
		ll l=-1e9,r=1e9,h,H=-1;
		while(l<=r){
			h=(l+r)>>1;
			
			if(check(v,h,n))
//				cout<<"!!!"<<h<<endl,
				H=h,l=h+1;
			else
				r=h-1;
		}
//		cout<<H<<endl;
		if(H>=0)
			cout<<sum-1ll*H*n<<endl;
		else
			cout<<-1<<endl;
	}
	
	cout.flush();
	
	return 0;
}
