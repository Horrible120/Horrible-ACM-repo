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
		if(n>=2&&n<=4){
			cout<<-1<<'\n';
			continue;
		}
		for(int i=1;i<=n;i+=2)
			if(i!=5)
				cout<<i<<' ';
		cout<<"5 4 ";
		for(int i=2;i<=n;i+=2)
			if(i!=4)
				cout<<i<<' ';
	}
	cout.flush();
	return 0;
}
