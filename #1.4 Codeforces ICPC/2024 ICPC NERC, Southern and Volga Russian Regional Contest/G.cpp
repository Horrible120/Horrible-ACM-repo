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
		ll n,a11,a1,a01,flag;
		cin>>n;
		cout<<1<<" 11"<<endl;
		cin>>a11;
		cout<<1<<" 1"<<endl;
		cin>>a1;
		cout<<1<<" 01"<<endl;
		cin>>a01;

		if(a01==(a1-a11))
			cout<<"0 1 0"<<endl;
		else
			cout<<"0 1 1"<<endl;
		cin>>flag;
		if(flag==-1)
			return 0;
	}
	
	cout.flush();
	
	return 0;
}
