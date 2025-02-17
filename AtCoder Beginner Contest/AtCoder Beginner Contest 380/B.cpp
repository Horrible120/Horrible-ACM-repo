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
	
	string s;
	cin>>s;
	ll cur=0;
	vector<ll> arr;
	
	for(int i=1;i<s.size();i++)
		if(s[i]=='|'){
			arr.push_back(cur);
			cur=0;
		}
		else
			cur++;
	
	for(auto i:arr){
		cout<<i<<' ';
	}
	cout<<endl;
	
	return 0;
}
