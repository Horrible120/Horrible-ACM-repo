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
	string s;
	
	cin>>n;
	cin>>s;
	
	vector<ll> pre(n+1),sub(n+1);
	
	for(ll i=0;i<n;i++){
		if(s[i]!='1')
			continue;
		ll cnt=0;
		while(i<n&&s[i]=='1')
			cnt++,i++;
		pre[i]=cnt;
		if(i>0)
			pre[i]=max(pre[i],pre[i-1]);
	}
	
	for(ll i=n-1;i>=0;i--){
		if(s[i]!='2')
			continue;
		ll cnt=0;
		while(i>=0&&s[i]=='2')
			cnt++,i--;
		if(i<0)
			break;
		sub[i]=cnt;
		sub[i]=max(sub[i],sub[i+1]);
	}
	
//	for(ll i=0;i<n;i++)
//		cout<<sub[i]<<' ';
	
	ll ans=1;
	for(ll i=1;i<n;i++){
		if(s[i]=='/')
			ans=max(ans,1+2*min(pre[i],sub[i]));
	}
	
	cout<<ans<<endl;
	
	cout.flush();
	
	return 0;
}
