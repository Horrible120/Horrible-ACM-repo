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
	
	ll n;
	cin>>n;
	
	string s;
	cin>>s;
	if(n%2==0)
		cout<<"No"<<'\n';
	else{
		ll flag=1;
		for(int i=0;i<n/2;i++)
			if(s[i]!='1')
				flag=0;
		if(s[n/2]!='/')
			flag=0;
		for(int i=n/2+1;i<n;i++)
			if(s[i]!='2')
				flag=0;
		if(flag)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	
	cout.flush();
	
	return 0;
}
