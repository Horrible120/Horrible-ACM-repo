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

string s;


ll n,q;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin>>s;
	n=s.size();
	
	cin>>q;
	
	ll k,p,st,cnt;
	for(int i=1;i<=q;i++){
		cin>>k;
		cnt=0;
		p=(k+n-1)/n-1;
		st=(k+n-1)%n;
		while(p){
			cnt+=p%2;
			p>>=1;
		}
		if(cnt%2)
			if(islower(s[st]))
				cout<<char(toupper(s[st]))<<' ';
			else
				cout<<char(tolower(s[st]))<<' ';
		else
			cout<<s[st]<<' ';
	}
	cout.flush();
	return 0;
}
