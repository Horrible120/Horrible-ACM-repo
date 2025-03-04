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

ull n,ans=INF;
ull a[1000010],v[1000010],cntp[1000010],cnts[1000010];
map<ull,ull> hs,cnta,cntv;


int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin>>n;
	
	for(ll i=1;i<=n;i++)
		cin>>a[i],v[i]=a[i];
	
	sort(v+1,v+n+1);
	
	ull l=0,r;
	for(ll i=1;i<=n;i++){
		cnta[a[i]]++;
		while(l<i&&cnta[v[l+1]]>cntv[v[l+1]])
			cntv[v[++l]]++;
		cntp[i]=l;
	}
	
	cnta.clear();
	cntv.clear();
	
	r=n+1;
	for(ll i=n;i>=1;i--){
		cnta[a[i]]++;
		while(r>i&&cnta[v[r-1]]>cntv[v[r-1]])
			cntv[v[--r]]++;
		cnts[i]=n-r+1;
	}
	
//	for(ll i=1;i<=n;i++)
//		cout<<cntp[i]<<' ';
//	cout<<endl;
//	for(ll i=1;i<=n;i++)
//		cout<<cnts[i]<<' ';
//	cout<<endl;
	
	l=0,r=1;
	while(l<=n){
		if(l==n) r=n+1;
		else if(cntp[l]==l){
			r=l+1;
			while(r<=n&&a[r]==v[r]) r++;
		}
		else r=cntp[l]+1;

		ll xr=n-r+1;
//		cout<<'['<<l<<','<<r<<']'<<' '<<l*l+xr*xr<<endl;
		ans=min(ans,l*l+xr*xr);
		
		if(r>l) l=r;
		else l++;
	}
	
	l=n,r=n+1;
	while(r>=1){
		if(r==1) l=0;
		else if(cnts[r]==n-r+1){
			l=r-1;
			while(l>=1&&a[l]==v[l]) l--;
		}
		else l=n-cnts[r];
		
		ll xr=n-r+1;
//		cout<<'['<<l<<','<<r<<']'<<' '<<l*l+xr*xr<<endl;
		ans=min(ans,l*l+xr*xr);
		
		if(l<r) r=l;
		else r--;
	}
	
	cout<<ans<<endl;
	cout.flush();
	
	return 0;
}
