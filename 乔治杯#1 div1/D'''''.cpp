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
		ll n,m,k,w;
		cin>>n>>m>>k>>w;
		
		ll cnt=0,flag=1;
		vector<ll> ans;
		
//		set<ll> red,black;
		set<pair<ll,ll>> block;
		
		block.insert(make_pair(0,-1));
		block.insert(make_pair(w+1,-1));
		
		
//		black.insert(0);
//		black.insert(w+1);
		ll x;
		for(ll i=1;i<=n;i++){
			cin>>x;
			block.insert(make_pair(x,1));
		}
		for(ll i=1;i<=m;i++){
			cin>>x;
			block.insert(make_pair(x,-1));
		}
		ll frt=0;
//		set<pair<ll,ll>> tmp;
		vector<ll> tit;
		
//		tmp.insert(*block.begin());
		block.erase(block.begin());
		
		tit.emplace_back(0);
		
		while(!block.empty()){
			auto [x,cl]=*block.begin();
			
//			cout<<"CH"<<x<<' '<<cl<<endl;
			
			if(cl==-1){
				tit.emplace_back(x);
				for(ll i=tit.size()-2;i>0;i--)
					tit[i]=min(tit[i+1]-k,tit[i]);
				
				if(tit.size()>2&&tit[1]>tit[0])
					for(ll i=1;i<(tit.size()-1);i++)
						ans.emplace_back(tit[i]);
				else if(tit.size()>2){
//					OOO cout<<x<<endl;
					flag=0;
					break;
				}
				frt=x;
				tit.clear();
				
				tit.emplace_back(x);
			}
			else if(x>frt){
//					tmp.insert(make_pair(x,cl));
					tit.emplace_back(x);
					frt=x+k-1;
				}
			block.erase(block.begin());
		}
//		OOO OOO
		if(flag){
			cout<<ans.size()<<endl;
			for(auto i:ans)
				cout<<i<<' ';
			cout<<endl;
		}
		else
			cout<<-1<<endl;
		
	}
	
	cout.flush();
	
	return 0;
}
