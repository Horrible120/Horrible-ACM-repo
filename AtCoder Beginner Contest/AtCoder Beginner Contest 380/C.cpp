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
	
	ll n,k,cur=1,num=0;
	string s;
	cin>>n>>k;
	cin>>s;

	for(ll i=0;i<n;){
		if(cur!=k){
			cout<<s[i];
			if(i<s.size()-1&&s[i]=='1'&&s[i+1]=='0'){
				cur++;
			}
			i++;
		}
			
		if(cur==k){
			while(s[i]=='0'){
				i++;
				num++;
			}
			while(i<s.size()&&s[i]=='1'){
				cout<<1;
				i++;
			}
			cout<<string(num,'0');
			cur++;
		}
		
	}
	cout.flush();
	return 0;
}
