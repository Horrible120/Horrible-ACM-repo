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
		if(a.cap!=cap) return cap<a.cap;
		else return w>a.w;
	}
};

bool cmp(ll v,Rest a){
	return a.cap>=v;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n,m,tot=0,ans=0,c=0;
		cin>>n>>m;
		if(n==0){
			cout<<0<<endl;
			continue;
		}
		vector<Tr> tr;
		set<Rest> s;
		
		Tr it={};
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
			
			
				cap+=it.r-it.l;
				
				Rest a={};
				a.c=sum;
				a.cap=cap;
				a.w=it.w;
				a.g=it.r-it.l;
				s.insert(a);
				
				sum+=(it.r-it.l)*it.w;
			
			it.cap=cap;
		}
	
//		cout<<tot<<endl;
		
//		Rest a={};
//		a.cap=8;
//		a=(s.lower_bound(a)!=s.end())?(*s.lower_bound(a)):(*s.rbegin());
//		cout<<a.cap<<' '<<a.c<<' '<<a.w<<' '<<a.g<<endl;

//		while(s.size()){
//			Rest a=*s.begin();
//			cout<<a.cap<<' '<<a.c<<' '<<a.w<<' '<<a.g<<endl;
//			s.erase(s.begin());
//		}
		
		for(auto it:tr){
			
			if(it.l==it.r&&m-tot+it.l>it.cap){
				Rest a={};
				a.cap=it.cap;
				a.w=it.w;
				if(s.size()) a=(s.lower_bound(a)!=s.end())?(*s.lower_bound(a)):(*s.rbegin());
				else{
					ans=max(ans,c);
					break;
				}
				
//				cout<<it.w<<' '<<it.l<<' '<<it.r<<' '<<it.cap<<" || "<<a.cap<<' '<<a.c<<' '<<a.w<<' '<<a.g<<' '<<c-(it.l*it.w)+(a.c)+(m-tot+it.l-(a.cap-a.g))*a.w<<endl;
				
				ans=max(ans,c-(it.l*it.w)+(a.c)+(m-tot+it.l-(a.cap-a.g))*it.w);
				continue;
			}
			
			Rest a={};
			a.cap=min(m-tot+it.l,it.cap);
			a.w=it.w;
			if(s.size()) a=(s.lower_bound(a)!=s.end())?(*s.lower_bound(a)):(*s.rbegin());
			else{
				ans=max(ans,c);
				break;
			}
			
//			cout<<it.w<<' '<<it.l<<' '<<it.r<<' '<<it.cap<<" || "<<a.cap<<' '<<a.c<<' '<<a.w<<' '<<a.g<<' '<<c-(it.l*it.w)+(a.c)+(m-tot+it.l-(a.cap-a.g))*a.w<<endl;

			ans=max(ans,c-(it.l*it.w)+(a.c)+(m-tot+it.l-(a.cap-a.g))*a.w);
		}
//		ans=max(ans,c+(m-tot)*tr[0].w);
		cout<<ans<<endl;
		
	}
	
	cout.flush();
	
	return 0;
}
