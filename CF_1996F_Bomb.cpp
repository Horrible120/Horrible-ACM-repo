#include<cmath>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn=1000000000;
int t,k,n;
vector<long long> a,b;

void check(int &l,int &r)
{
	int mid=l+((r-l)>>1),cnt=0;
	
	for(int i=0;i<n&&cnt<=k;i++)
		if(a[i]>=mid)
			cnt+=(a[i]-mid)/b[i]+1;
	
	if(cnt>k) l=mid;
	if(cnt<=k) r=mid;
	return;
}

void solve(vector<long long> &a, vector<long long> &b,int &n,int &k)
{
    long long ans=0;
    
    int l=0,r=maxn;
    
	while(l<r-1)
		check(l,r); 
		
	int x;
    for(int i=0;i<n&&k>0;i++)
    if(a[i]>l)
    	{
    		x=min(k,int((a[i]-l-1)/b[i]+1));
    		ans+=(2*a[i]-(x-1)*b[i])*x/2;
    		a[i]-=x*b[i];
    		k-=x;
		}
	for(int i=0;i<n&&k>0;i++)
		if(a[i]>=l)
		{
			ans+=a[i];
			k--;
		}
	
	cout<<ans<<endl;
    return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t; 

	for(int i=1;i<=t;i++)
	{
		cin>>n>>k;
		
		for(int j=1;j<=n;j++) a.emplace_back([](){long long x;cin>>x;return x;}());
		for(int j=1;j<=n;j++) b.emplace_back([](){long long x;cin>>x;return x;}());
		
		solve(a,b,n,k);
		a={};
		b={};
	}
	
	return 0;
}
