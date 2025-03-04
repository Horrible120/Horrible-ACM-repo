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
ll n,m,l;
ll start,po[25],card[20],N;

struct State{
	ll s,vis=0,pl,ans;
}state[600010][2];

void init(){
	po[1]=1;
	for(int i=2;i<=24;i++)
		po[i]=3*po[i-1];
	
}

ll Get(ll st,ll pos){
	return st/po[pos]%3;
}

ll DFS(ll st,ll pl){
	if(state[st][pl].vis)
		return state[st][pl].ans;
	
	state[st][pl].ans=pl^1;
	for(int i=1;i<=N;i++){
		if(Get(st,i)==pl){
			for(int j=1;j<=N;j++){
				if(Get(st,j)==2&&card[j]<card[i]){
					if(!state[st+po[i]*(2-pl)+po[j]*(pl-2)][pl^1].vis)
						state[st+po[i]*(2-pl)+po[j]*(pl-2)][pl^1].ans=DFS(st+po[i]*(2-pl)+po[j]*(pl-2),pl^1);
					if(state[st+po[i]*(2-pl)+po[j]*(pl-2)][pl^1].ans==pl)
						state[st][pl].ans=pl;
				}
				if(!state[st+po[i]*(2-pl)][pl^1].vis)
					state[st+po[i]*(2-pl)][pl^1].ans=DFS(st+po[i]*(2-pl),pl^1);
				if(state[st+po[i]*(2-pl)][pl^1].ans==pl)
					state[st][pl].ans=pl;
			}	
		}
	}
	state[st][pl].vis=1;
	return state[st][pl].ans;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	ll x;
	cin>>n>>m>>l;
	
	init();
	
	for(int i=1;i<=n;i++){
		cin>>x;
		card[i]=x;
		start+=po[i]*0;
	}
	for(int i=1;i<=m;i++){
		cin>>x;
		card[n+i]=x;
		start+=po[n+i]*1;
	}
	for(int i=1;i<=l;i++){
		cin>>x;
		card[n+m+i]=x;
		start+=po[n+m+i]*2;
	}
	N=n+m+l;	
	
	DFS(start,0);
	
	if(state[start][0].ans==0)
		cout<<"Takahashi"<<endl;
	else
		cout<<"Aoki"<<endl;
	
	return 0;
}
