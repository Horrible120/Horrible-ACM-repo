#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,b,k1,k2;
int a[5010];
struct Sort { int lst,a,b,c; } p[5010];
bool cmp(Sort x,Sort y)
{
	int xx=max(x.b,x.c)-max(x.lst,x.a),yy=max(y.b,y.c)-max(y.lst,y.a);
	return xx==yy?(x.b>=x.c && x.lst<x.a)>(y.b>=y.c && y.lst<y.a):xx>yy;
}
int check(int mid,bool op)
{
	for(int i=1; i<=n; ++i) p[i]={0,a[i]/2-mid,min(a[i],b),min(a[i]/2+b,a[i])-mid};
	sort(p+1,p+n+1,cmp);
	if(op==1)
	{
		int sum=0;
		for(int i=1; i<=n; ++i) sum+=max(p[i].lst,p[i].a);
		for(int i=1; i<=k2; ++i) sum+=max(max(p[i].b,p[i].c)-max(p[i].lst,p[i].a),0ll);
		return sum+k1*mid;
	}
	int cnt=n;
	for(int i=1; i<=n; ++i) cnt-=(p[i].lst>=p[i].a);
	for(int i=1; i<=k2; ++i)
	{
		if(max(p[i].b,p[i].c)>=max(p[i].lst,p[i].a)) cnt-=(p[i].b>=p[i].c && p[i].lst<p[i].a);//
	}
	return cnt<=k1;
}
signed main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n>>b>>k1>>k2;
		int sum=0;
		for(int i=1; i<=n; ++i) cin>>a[i],sum+=a[i];
		sort(a+1,a+n+1,greater<int>());
		int el=0,er=1e9,mid,ans;
		while(el<=er)
		{
			mid=el+er>>1;
			if(check(mid,0)) ans=mid,er=mid-1;
			else el=mid+1;
		}
		cout<<sum-check(ans,1)<<'\n';
	}
	return 0;
}

