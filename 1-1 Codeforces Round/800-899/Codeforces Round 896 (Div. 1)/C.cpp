#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int t,n,m,ans[200005];
struct nd{
	int a[205],b[205];
}f[205];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
int check(int u,int n){
	int now1=u,now2=u,flag=1,dep1=0,dep2=0; 
	while(now1<=n){
		dep1++;
		if((now1<<1)<=n)now1=now1<<1;
		else if((now1<<1|1)<=n)now1=now1<<1|1,flag=0;
		else break;
	}
	while(now2<=n){
		dep2++;
		if((now2<<1|1)<=n)now2=now2<<1|1;
		else if((now2<<1)<=n)now2=now2<<1,flag=0;
		else break;
	}
	if(!flag)return 0;
	if(dep1!=dep2)return 0;
	return dep1;
}
nd dfs(int u,int n){
	nd a,b,ans;
	memset(a.a,0,sizeof a.a),memset(a.b,0,sizeof a.b);
	memset(b.a,0,sizeof b.a),memset(b.b,0,sizeof b.b);
	memset(ans.a,0,sizeof ans.a),memset(ans.b,0,sizeof ans.b);
	if((u<<1)<=n){
		int dep=check(u<<1,n);
		if(!dep)a=dfs(u<<1,n);
		else a=f[dep];
	}
	if((u<<1|1)<=n){
		int dep=check(u<<1|1,n);
		if(!dep)b=dfs(u<<1|1,n);
		else b=f[dep];
	}
	ans.b[0]=1;
	for(int j=1;j<=200;j++)ans.b[j]=a.b[j-1]+b.b[j-1],ans.b[j]%=mod;
	for(int j=0;j<=200;j++)ans.a[j]=ans.b[j];
	for(int j=0;j<=200;j++)ans.a[j]+=a.a[j]+b.a[j],ans.a[j]%=mod;
	for(int j=0;j<=200;j++)for(int k=0;k<=200;k++)ans.a[j+k+2]+=a.b[j]*b.b[k]%mod,ans.a[j+k+2]%=mod; 
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t,f[1].a[0]=f[1].b[0]=1;
	for(int i=2;i<=200;i++){
		f[i].b[0]=1;
		for(int j=1;j<=200;j++)f[i].b[j]=f[i-1].b[j-1]*2,f[i].b[j]%=mod;
		for(int j=0;j<=200;j++)f[i].a[j]=f[i].b[j];
		for(int j=0;j<=200;j++)f[i].a[j]+=f[i-1].a[j]*2,f[i].a[j]%=mod;
		for(int j=0;j<=200;j++)for(int k=0;k<=200;k++)f[i].a[j+k+2]+=f[i-1].b[j]*f[i-1].b[k]%mod,f[i].a[j+k+2]%=mod; 
	}
	while(t--){
		cin>>n>>m;
		nd now=dfs(1,n);
		for(int i=1;i<=m;i++)ans[i]=0;
		for(int i=1;i<=m;i++){
			int x=1,a=ksm(m,n),b=i*ksm(m,mod-2)%mod;
			for(int j=1;j<=200;j++){
				x*=b,x%=mod;
				ans[i]+=x*now.a[j-1]%mod*a%mod,ans[i]%=mod;
			}
		}
		int cnt=0;
		for(int i=1;i<=200;i++)cnt+=now.a[i-1],cnt%=mod;
		for(int i=m;i;i--)ans[i]-=ans[i-1],ans[i]+=mod,ans[i]%=mod;
		int anss=0;
		for(int i=1;i<=m;i++)anss+=ans[i]*i%mod,anss%=mod;
		cout<<anss<<"\n";
	}
}

