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
#include <unordered_map>
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
	
	ll n,m;
	unordered_map<ll,ll> a,b,bk;
	vector<ll> stu,v;
	
	cin>>n>>m;
	ll x;
	for(ll i=1;i<=n;i++){
		cin>>x;
		a[x]=1;
		stu.emplace_back(x);
	}
	
	for(ll i=1;i<=m;i++){
		cin>>x;
		if(a[x]) b[x]^=1;
	}
	
	for(auto it:stu){
		if(a[it]&&(!b[it])&&(!bk[it])){
			v.emplace_back(it);
			bk[it]=1;
		}
	}
	
	sort(v.begin(),v.end());
	
	cout<<v.size()<<endl;
	
	for(auto it:v)
		cout<<it<<' ';
	cout<<endl;
	
	cout.flush();
	
	return 0;
}
