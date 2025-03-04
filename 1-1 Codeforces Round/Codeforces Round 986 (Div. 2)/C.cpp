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

mt19937_64 rnd(time(0));

typedef long long ll;
typedef uint64_t ull;


const ll INF=1e18,
		 Mod=1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> tt;

	while (tt--) {
		ll n,m,v,ans=0,flag=0;
		cin>>n>>m>>v;
		
		vector<ll> a(n+1),pre(n+1),pres(n+1),suf(n+2);
		
		pre[0]=0;
		suf[n+1]=0;
		
		for(int i=1;i<=n;i++)
			cin>>a[i];
		
		for(int i=1;i<=n;i++)
			pres[i]=pres[i-1]+a[i];
		
		ll cur=0;
		for(int i=1;i<=n;i++){
			cur+=a[i];
			if(cur>=v){
				pre[i]=pre[i-1]+1;
				cur=0;
			}
			else	
				pre[i]=pre[i-1];
		}
		cur=0;
		for(int i=n;i>=1;i--){
			cur+=a[i];
			if(cur>=v){
				suf[i]=suf[i+1]+1;
				cur=0;
			}
			else	
				suf[i]=suf[i+1];
		}
		
		ll r=1;
		for(int i=0;i<=n;i++){
			if(r<=i) r=i+1;
			while(r<=n&&pre[i]+suf[r+1]>=m) r++;
			
			if(pre[i]+suf[i+1]>=m)
				flag=1;
			
			ans=max(ans,pres[r-1]-pres[i]);
		}
		
		if(flag)
			cout<<ans<<endl;
		else
			cout<<-1<<endl;
	}

	return 0;
}

