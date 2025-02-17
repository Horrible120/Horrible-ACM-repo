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
//#define endl '\n'

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt;

struct Mem{
	ll l,r;
};

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n;
		cin>>n;
		ll l,r;
		
		vector<ll> lf(n+1),rt(n+1);
		
		map<ll,Mem> mp;
		
		vector<tuple<ll,ll,ll>> v;
		
		for(ll i=1;i<=n;i++){
			cin>>l>>r;
			mp[i].l=l;
			mp[i].r=r;
			v.emplace_back(make_tuple(l,0,i));
			v.emplace_back(make_tuple(r,1,i));
		}
		sort(v.begin(),v.end());
		
		multiset<ll,greater<ll>> L;
		multiset<ll> R;
		
//		for(ll i=0;i<2*n;i++){
//			auto [coo,k,id]=v[i];
//			cout<<coo<<' '<<k<<' '<<id<<endl;
//		}
		
		for(ll i=0;i<2*n;i++){
			auto [coo,k,id]=v[i];
			if(k==0){
				
				if(i==0||(i!=0&&get<0>(v[i])!=get<0>(v[i-1])))
					for(ll j=i;j<2*n;j++){
						auto [coo,k,id]=v[j];
						if(k==1||coo!=get<0>(v[i]))
							break;
						R.insert(mp[id].r);
						L.insert(coo);
					}
				
				R.erase(R.find(mp[id].r));
				rt[id]=(R.lower_bound(mp[id].r)==R.end()?0:(*R.lower_bound(mp[id].r)));
				R.insert(mp[id].r);
				
//				cout<<"----"<<id<<'R'<<rt[id]<<endl;
			}
			else{
				L.erase(L.find(mp[id].l));
				lf[id]=(L.lower_bound(mp[id].l)==L.end()?0:*L.lower_bound(mp[id].l));
				L.insert(mp[id].l);
				
				if(i!=2*n-1&&get<0>(v[i])!=get<0>(v[i+1]))
					for(ll j=i;j>=0;j--){
						auto [coo,k,id]=v[j];
						if(k==0||coo!=get<0>(v[i]))
							break;
						R.erase(R.find(coo));
						L.erase(L.find(mp[id].l));
					}
				
//				cout<<"----"<<id<<'L'<<lf[id]<<endl;
			}
		}
		
//		OOO
		for(ll i=1;i<=n;i++){
			if(lf[i]==0||rt[i]==0)
				cout<<0<<endl;
			else
				cout<<rt[i]-lf[i]+1-(mp[i].r-mp[i].l+1)<<endl;
		}
	}
	
	
	
	cout.flush();
	
	return 0;
}
