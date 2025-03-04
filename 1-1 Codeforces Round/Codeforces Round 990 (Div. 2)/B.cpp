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
		ll n;
		string s;
		
		map<char,ll> mp;
		
		cin>>n;
		cin>>s;
		
		for(ll i=0;i<n;i++){
			mp[s[i]]++;
		}
		char mx=s[0],mn=s[0];
		for(char i='a';i<='z';i++){
			if(mp[i]>mp[mx]) mx=i;
			if(mp[i]&&(mp[i]<mp[mn]||(mp[i]==mp[mn]&&i!=mx))) mn=i;
		}
//		cout<<"!"<<mn<<' '<<mx<<endl;
		ll flag=1;
		for(ll i=0;i<n;i++)
			if(s[i]==mn&&flag){
				cout<<mx;
				flag=0;
			}
		else
			cout<<s[i];
		cout<<endl;
	}
	
	cout.flush();
	
	return 0;
}
