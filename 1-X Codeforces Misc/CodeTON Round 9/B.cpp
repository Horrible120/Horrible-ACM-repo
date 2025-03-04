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
		string s;
		cin>>s;
//		OOO
		for(ll i=0;i<s.size();i++){
			if(i>0&&s[i]==s[i-1]){
				cout<<s[i]<<s[i]<<endl;
				break;
			}
			if(i>1&&s[i]!=s[i-1]&&s[i]!=s[i-2]&&s[i-1]!=s[i-2]){
				cout<<s[i-2]<<s[i-1]<<s[i]<<endl;
				break;
			}
			if(i==s.size()-1)
				cout<<-1<<endl;
		}
	}
	
	cout.flush();
	
	return 0;
}
