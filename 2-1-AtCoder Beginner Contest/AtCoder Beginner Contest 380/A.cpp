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
	
	ll n;
	cin>>n;
	ll cnt[11]={};
	
	cnt[n%10]++;
	n/=10;
	cnt[n%10]++;
	n/=10;
	cnt[n%10]++;
	n/=10;
	cnt[n%10]++;
	n/=10;
	cnt[n%10]++;
	n/=10;
	cnt[n%10]++;
	
	if(cnt[1]==1&&cnt[2]==2&&cnt[3]==3)
		cout<<"Yes"<<'\n';
	else
		cout<<"No"<<'\n';
	
	cout.flush();
	
	
	return 0;
}
