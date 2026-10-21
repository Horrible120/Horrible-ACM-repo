#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,a[maxn];
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
map<int,int>mp;
map<int,int>::iterator it;
inline pii ask(int l,int r){
	if(l<1)l=1;if(r>n)r=n;
	if(l>r)return mkp(0,0);
	printf("? %d %d\n",l,r);
	fflush(stdout);
	int x=read(),y=read();
	return mkp(x,y);
}
inline void solve(int l,int r){
	if(l>r)return;
	//printf("solving interval:[%d,%d]\n",l,r);
	pii now=ask(l,r);
	int x=now.fi,y=now.se;
	if(r-l+1==y){
		for(int i=l;i<=r;i++)a[i]=x;
		mp[x]=l;return;
	}
	if(!mp[x]){
		it=mp.lower_bound(x);--it;
		for(int i=max(l,it->se+y);;i+=y){
			pii cur=ask(i,i);
			mp[cur.fi]=i;
			if(cur.fi==x)break;
		}
	}int pos=mp[x];
	pii L=ask(pos-y+1,pos);
	pii R=ask(pos,pos+y-1);
	int lb=0,rb=0;
	if(L.fi==x)lb=1+pos-L.se,rb=lb+y-1;
	else lb=pos+R.se-y,rb=lb+y-1;
	for(int i=lb;i<=rb;i++)a[i]=x;
	solve(l,lb-1);solve(rb+1,r);
}
int main(){
	mp[0]=0;
	n=read();solve(1,n);
	printf("! ");
	for(int i=1;i<=n;i++)
		printf("%d ",a[i]);puts("");
	fflush(stdout);
	return 0;
}

