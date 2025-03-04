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
		ll n,k;
		cin>>n>>k;
		
		string x;
		vector<ll> v,sum(n+1);
		cin>>x;
		for(ll i=0;i<n;i++){
			if(x[i]=='0') v.emplace_back(-1);
			else v.emplace_back(1);
		}
		for(ll i=1;i<=n;i++)
			sum[i]=sum[i-1]+v[i-1];
		for(ll i=1;i<=n;i++)
			sum[i]=sum[n]-sum[i];
		
		
		
		sort(sum.begin()+1,sum.end(),greater<ll>());
		
//		for(ll i=1;i<=n;i++)
//			cout<<sum[i]<<' ';
//		cout<<endl;
		
		ll key=0;
		for(ll i=1;i<=n;i++)
			if(sum[i]>0)
				key+=sum[i];
//		OOO
		if(key<k){
			cout<<-1<<endl;
			continue;
		}
		
		ll l=1,r=n+1,mid,ans=INF;
		while(l<=r){
			mid=(l+r)/2;
			ll key=0;
			for(ll i=1;i<=mid;i++)
				if(sum[i]>0)
					key+=sum[i];
			
//			cout<<"CK"<<mid<<' '<<key<<endl;
			
			if(key>=k){
				ans=min(ans,mid);
				r=mid-1;
			}
			else l=mid+1;
		}
		
		if(ans>=n)
			cout<<-1<<endl;
		else
			cout<<ans+1<<endl;
	}
	cout.flush();
	
	return 0;
}
