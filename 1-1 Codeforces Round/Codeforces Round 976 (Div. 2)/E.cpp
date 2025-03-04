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
ll c[52];

void exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}

ll Inv(ll a){
	ll x=0,y=0;
	exgcd(a,Mod,x,y);
	return ((x%Mod)+Mod)%Mod;
}

void init(){
	c[0]=1;
	for(ll i=1;i<=50;i++){
		c[i]=2*c[i-1]%Mod;
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
//	cout<<c[6]<<' '<<Inv(717171)<<endl;
	

	cin >> tt;
	
	while ( tt-- ) {
		ll n,ans=0;
		cin>>n;
		vector<ll> v(n+1),p(n+1);
		ll per[21][21][2][2]={};
		
		for(ll i=0;i<=20;i++)
			for(ll j=0;j<=20;j++)
				per[i][j][0][0]=1;
		
		
		for(ll i=1;i<=n;i++)
			cin>>v[i];
		for(ll i=1;i<=n;i++)
			cin>>p[i];
		for(ll k=1;k<=n;k++){
			ll t=0;
			vector<ll> bin(21);
			while(v[k]){
				if(v[k]%2)
					bin[t]=1;
				t++;
				v[k]>>=1;
			}
			ll pi=p[k]*Inv(10000)%Mod;
			for(ll i=0;i<=20;i++){
				for(ll j=0;j<=20;j++){
					
					ll tmp[2][2]={{per[i][j][0][0],per[i][j][0][1]},{per[i][j][1][0],per[i][j][1][1]}};
					
					
					
					per[i][j][1][1]=(tmp[1^bin[i]][1^bin[j]]*pi+tmp[1][1]*(1-pi))%Mod;
					per[i][j][0][1]=(tmp[0^bin[i]][1^bin[j]]*pi+tmp[0][1]*(1-pi))%Mod;
					per[i][j][1][0]=(tmp[1^bin[i]][0^bin[j]]*pi+tmp[1][0]*(1-pi))%Mod;
					per[i][j][0][0]=(tmp[0^bin[i]][0^bin[j]]*pi+tmp[0][0]*(1-pi))%Mod;
					
				}
			}
			
		}
		
//		for(ll i=0;i<=2;i++){
//			for(ll j=0;j<=2;j++)
//				cout<<i<<j<<'|'<<per[i][j][1][1]<<' ';
//			cout<<endl;
//		}
			
		
		for(ll i=0;i<=20;i++){
			for(ll j=0;j<=20;j++){
				ans=(ans+c[i+j]*per[i][j][1][1])%Mod;
			}
		}
//		OOO
		cout<<(ans+Mod)%Mod<<endl;
	}
	
	cout.flush();
	
	return 0;
}
