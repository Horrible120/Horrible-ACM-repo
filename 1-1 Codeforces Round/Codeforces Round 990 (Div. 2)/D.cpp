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
		cin>>n;
		vector<ll> v(n+1),sub(n+2),ans;
		
		multiset<ll> s;
		
		for(ll i=1;i<=n;i++)
			cin>>v[i],s.insert(v[i]+1);
		sub[n+1]=n+1;
		sub[n]=n;
		for(ll i=n-1;i>=1;i--)
			sub[i]=(v[i]<=v[sub[i+1]]?i:sub[i+1]);
		for(ll i=1;i<=n;){
//			cout<<"!!"<<i<<' '<<sub[i]<<endl;
			if(v[sub[i]]>*s.begin()) break;
			ans.emplace_back(v[sub[i]]);
			s.erase(s.find(v[sub[i]]+1));
			i=sub[i]+1;
		}
		while(s.size()){
			ans.emplace_back(*s.begin());
			s.erase(s.begin());
		}
		for(auto i:ans)
			cout<<i<<' ';
		cout<<endl;
	}
	
	cout.flush();
	
	return 0;
}
