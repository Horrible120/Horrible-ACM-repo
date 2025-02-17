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

ll tt;



int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n,flag=1;
		cin>>n;
		vector<ll> v(n+1);
		
		for(int i=1;i<=n;i++)
			cin>>v[i];
		
		for(int i=1;i<=n;i++){
			if(v[i]==i) continue;
			else{
				if(i==n){
					flag=0;
					
					break;
				}
					
				if(v[i]==i+1&&v[i+1]==i){
					i++;
					continue;
				}
				flag=0;
			}
		}
		
		if(flag)
			cout<<"YES"<<'\n';
		else
			cout<<"NO"<<'\n';
		
	}
	cout.flush();
	return 0;
}
