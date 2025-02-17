#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt;

template <typename T>
struct Fenwick{
	ll n{};
	vector<T> a;
	Fenwick(ll _n=0){
		init(_n);
	}
	void init(ll _n){
		a.assign(n=_n,T{});
	}
	void add(ll x,const T &k){
		for(ll i=x+1;i<=n;i+=i&-i)
			a[i-1]=a[i-1]+k;
	}
	T sum(ll x){
		T ans{};
		for(ll i=x;i>0;i^=i&-i)
			ans=ans+a[i-1];
		return ans;
	}
	T rangeSum(ll l,ll r){
		return sum(r)-sum(l-1);
	}
	ll select(const T &k){
		ll x{};
		T cur{};
		for(ll i=1<<__lg(n);i;i>>=1)
			if(x+i<=n&&cur+a[x+i-1]<=k){
				x+=i;
				cur=cur+a[x-1];
			}
				
		return x;
	}
};

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n;
		cin>>n;
		vector<ll> x(n),y(n);
		for(ll i=0;i<n;i++)
			cin>>x[i]>>y[i];
		auto xs=x,ys=y;
		sort(xs.begin(),xs.end());
		sort(ys.begin(),ys.end());
		
		xs.erase(unique(xs.begin(),xs.end()),xs.end());
		ys.erase(unique(ys.begin(),ys.end()),ys.end());
		
		for(ll i=0;i<n;i++){
			x[i]=lower_bound(xs.begin(),xs.end(),x[i])-xs.begin();
			y[i]=lower_bound(ys.begin(),ys.end(),y[i])-ys.begin();
		}
		
		Fenwick<ll> fl(n),fr(n);
		
		vector<ll> p(n);
		iota(p.begin(),p.end(),0);
		sort(p.begin(),p.end(),[&](int i,int j){return x[i]<x[j];});
		
		for(ll i=0;i<n;i++)
			fr.add(y[i],1);
		
		
//		for(ll i=0;i<n;i++)
//			cout<<fr.select(i)<<' ';
//		cout<<endl;
		
		ll k=0,ansx{},ansy{};
		for(ll i=0;i<n;i++){
			ll j=p[i];
			fl.add(y[j],1);
			fr.add(y[j],-1);
			if(i+1<n&&x[j]==x[p[i+1]])
				continue;
			while(1){
				if(i+1<2*(k+1)||n-i-1<2*(k+1)) break;
				ll top=max(fl.select(k),fr.select(k));
				ll flr=min(fl.select((i+1)-(k+1)),fr.select(n-(i+1)-(k+1)));
				if(top>=flr) break;
				
//				cout<<k<<' '<<top<<' '<<flr<<endl;
				
				k++;
				ansx=xs[x[p[i]]]+1;
				ansy=ys[flr];
			}
		}
//		OOO
		cout<<k<<endl<<ansx<<' '<<ansy<<endl;
	}
	
	cout.flush();
	
	return 0;
}
