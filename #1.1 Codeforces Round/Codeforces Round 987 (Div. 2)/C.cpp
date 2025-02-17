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
		ll n;
		cin>>n;
		if(n%2==0){
			for(int i=1;i<=n/2;i++)
				cout<<i<<' '<<i<<' ';
			cout<<'\n';
		}
		else if(n<27){
			cout<<-1<<'\n';
		}
		else{
			cout<<"1 2 2 3 3 4 4 5 5 1 6 6 7 7 8 8 9 9 10 10 11 11 13 12 12 1 13 ";
			for(int i=28;i<=n;i++)
				cout<<i/2<<' ';
			cout<<'\n';
		}
	}
	cout.flush();
	return 0;
}
