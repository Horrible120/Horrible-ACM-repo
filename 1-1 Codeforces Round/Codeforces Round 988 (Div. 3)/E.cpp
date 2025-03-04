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

ll ask(ll l,ll r){
	cout<<"? "<<l<<' '<<r<<endl;
	ll x;
	cin>>x;
	return x;
}

void Ans(string ans){
	cout<<"! "<<ans<<endl;
	return;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		string ans={};
		ll n,cnt=0;
		cin>>n;
		
		vector<ll> res={};
		
		for(ll i=1;i<n;i++){
			if(ask(i,i+1)){
				res.emplace_back(i);
				i++;
			}
			cnt++;
		}
		
//		for(auto it:res)
//			cout<<"!!"<<it<<endl;
		
		if(res.empty()){
			Ans(string("IMPOSSIBLE"));
		}
//		else if(*res.begin()==n-1){
//			
//		}
		else{
			for(int i=0;i<res.size();i++){
				ll it=res[i];
				ll ct=0;
				if(i==0)
					if(res[0]==1)
						ct=1;
					else
						ct=ask(1,it+1);
				else{
//					cout<<"!!!!"<<res[i-1]<<it+1<<endl;
					ct=ask(res[i-1]+1,it+1);
				}
				if(i==0)
					ans+=string(it-ct,'1')+string(ct,'0');
				else
					ans+=string(it-res[i-1]-ct,'1')+string(ct,'0');
			}
			if(*res.rbegin()==n-1)
				ans+="1";
			else{
				ans+=string(ask(*res.rbegin(),n),'1');
				ans+=string(n-ans.size(),'0');
			}
			
			Ans(ans);
		}
	}
	
	return 0;
}
