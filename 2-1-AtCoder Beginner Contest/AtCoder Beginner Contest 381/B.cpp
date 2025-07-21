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
	
	string s;
	cin>>s;
	
	map<char,ll> mp;
	
	bool flag=1;
	
	if(s.size()%2)
		flag=0;
	else
		for(ll i=0;i<s.size();i+=2){
			if(s[i]!=s[i+1])
				flag=0;
			else if(mp[s[i]])
				flag=0;
			else
				mp[s[i]]=1;
		}
	if(flag)
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl;
	
	
	cout.flush();
	
	return 0;
}
