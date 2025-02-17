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

struct Tr{
	ll w,l,r,cap;
	bool operator<(const Tr &a) const{
		return w>a.w;
	}
};

struct Rest{
	ll cap,w,c,g;
	bool operator<(const Rest &a) const{
		return cap<a.cap;
	}
	bool operator<=(const Rest &a) const{
		return cap<=a.cap;
	}
};

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n,m,tot=0,ans=0,c=0;
		cin>>n>>m;
		vector<Tr> tr;
		set<Rest> s;
		
		Tr it;
		for(ll i=1;i<=n;i++){
			
			cin>>it.w>>it.l>>it.r;
			tr.emplace_back(it);
			
			tot+=it.l;
			c+=it.l*it.w;
		}
		
//		cout<<c<<endl;
		
		sort(tr.begin(),tr.end());
		
		ll cap=0,sum=0;
		for(auto &it:tr){
			if(it.r-it.l){
				cap+=it.r-it.l;
				
				Rest a={};
				a.c=sum;
				a.cap=cap;
				a.w=it.w;
				a.g=it.r-it.l;
				s.insert(a);
				
				sum+=(it.r-it.l)*it.w;
			}
			it.cap=cap;
		}
		
		
		for(auto it:tr){
			Rest a={};
			a.cap=m-tot+it.l;
			a=(s.lower_bound(a)!=s.end())?(*s.lower_bound(a)):(*s.rbegin());
			
			cout<<it.w<<' '<<it.l<<' '<<it.r<<' '<<m-tot+it.l<<" || "<<a.cap<<' '<<a.c<<' '<<a.w<<endl;
			
			ll rcap=min((m-tot+it.l)-(a.cap-a.g),it.cap);
			
			if(rcap+tot==m)
				ans=max(ans,c-(it.l*it.w)+a.c+rcap*a.w);
			else
				ans=max(ans,c-(it.l*it.w)+a.c+rcap*a.w+(m-tot-rcap)*it.w);
		}
		
		cout<<ans<<endl;
		
		
	}
	
	cout.flush();
	
	return 0;
}
