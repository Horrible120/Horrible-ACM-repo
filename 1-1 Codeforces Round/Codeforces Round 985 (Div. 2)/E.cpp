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
const ll MAXN=1e6+7;

ll tt;
bool np[1000010];
ll pr[1000010];
vector<ll> prime;

void init(){
	np[1]=1;
	for(ll i=2;i<=MAXN;i++){
		if(!np[i]){
			prime.emplace_back(i);
			pr[i]=i;
		}
		for(auto j:prime){
			if(i*j>MAXN) break;
//			pr[i*j]=j;
			np[i*j]=1;
			pr[i*j]=j;
			if(i%j==0){
				pr[i*j]=j;
				break;
			}
		}
	}
//	for(ll i=1;i<=100;i++)
//		cout<<i<<' '<<pr[i]<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	init();
	
	while ( tt-- ) {
		ll n,mxp=0;
		cin>>n;
		vector<ll> v(n+1);
		
		for(ll i=1;i<=n;i++)
			cin>>v[i];
		
		for(ll i=1;i<=n&&mxp!=INF;i++){
			if((!np[v[i]])){
				if(!mxp)
					mxp=v[i];
				else if(v[i]!=mxp)
					mxp=INF;
			}
				
		}
		
//		OOO
		
		if(mxp==INF)
			cout<<-1<<endl;
		else{
			if(!mxp) mxp=2;
			ll flag=1;
			for(ll i=1;i<=n;i++)
				if(np[v[i]]&&(v[i]/pr[v[i]]/2)*pr[v[i]]<mxp&&v[i]/pr[v[i]]<mxp)
					flag=0;
			if(flag)
				cout<<mxp<<endl;
			else
				cout<<-1<<endl;
		}
	}
	
	cout.flush();
	
	return 0;
}
