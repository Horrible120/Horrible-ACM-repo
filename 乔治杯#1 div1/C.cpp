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
Mod = 998244353;

ll tt;

bool cmp(ll a,ll b){
	return a>b;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin>>tt;
	
	while(tt--)
	{
		ll n,cnt=0,ans=1;
		cin >> n;
		vector<ll> num;
		ll x;
		for(ll i=1;i<=n;i++){
			cin>>x;
			if(x){
				cnt++;
				num.emplace_back(x);
			}
		}
		
		if(cnt<3){
			ans=0;
			for(ll i=0;i<cnt;i++)
				ans=max(ans,num[i]);
		}
		
//		cout<<cnt<<endl;
		
		sort(num.begin(),num.end(),cmp);
		
		for(ll i=0;i<cnt;){
			if(i<=cnt-3){
				ans=(num[i]%Mod)*(num[i+1]*num[i+2]%Mod)%Mod;
				num[i+2]=ans;
				i+=2;
			}
			else break;
		}
		
		cout<<ans%Mod<<endl;
	}
	
	cout.flush();
	
	return 0;
}
