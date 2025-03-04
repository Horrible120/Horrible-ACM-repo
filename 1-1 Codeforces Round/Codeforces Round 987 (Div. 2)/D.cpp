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

struct DP{
	ll coo,h;
};

struct cmp1{
	const operator()(DP a,DP b) const{
		if(a.h!=b.h) return a.h<b.h;
		return a.coo>b.coo;
	}
};

ll get_fa(vector<ll> &fa,ll a){
	if(fa[a]==a)
		return a;
	else
		return fa[a]=get_fa(fa,fa[a]);
}

void join(vector<ll> &fa,vector<ll> &ans,ll a,ll b){
	a=get_fa(fa,a);
	b=get_fa(fa,b);
	if(a==b) return;
	if(a<b) swap(a,b);
	fa[b]=a;
	ans[a]=max(ans[a],ans[b]);
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n;
		cin>>n;
		vector<ll> v(n+1),fa(n+1),ans(n+1);
		
		set<DP,cmp1> s; 
		
		for(int i=1;i<=n;i++){
			fa[i]=i;
		}
		
		for(int i=1;i<=n;i++){
			cin>>v[i];
			s.insert({i,v[i]});
			ans[i]=v[i];
		}
		
		for(int i=1;i<=n;i++){
			while((*s.begin()).h<v[i]){
				//cout<<(*s.begin()).h<<endl;
				if((*s.begin()).coo>i){
					join(fa,ans,i,(*s.begin()).coo);
//					cout<<"["<<i<<','<<(*s.begin()).coo<<']'<<endl;
					s.erase(s.begin());
				}
				else
					s.erase(s.begin());
			}
			if(get_fa(fa,i)!=i) s.insert({get_fa(fa,i),v[get_fa(fa,i)]});
		}
//		cout<<">>";
		for(int i=1;i<=n;i++){
			cout<<ans[get_fa(fa,i)]<<' ';
		}
		cout<<endl;
		
	}
	cout.flush();
	return 0;
}
