#include <bits/stdc++.h>
#define ll long long
#define U unsigned
using namespace std;
ll y,z,p,k,ans;
ll sqr(ll a,ll b){//快速幂
	ll num=1;
	a%=p;
	while(b){
		if(b&1)num=num*a%p;
		a=a*a%p;
		b>>=1;
	}
	return num;
}
map<ll,ll>vis;//映射
ll BSGS(){
	vis.clear();
	ll a,b=ceil(sqrt(p)),c,k=z%p,num=1;
	for(c=0;c<b;c++,k=y*k%p)vis[k]=c;//映射标记
	for(a=1;a<=b;a++){
		num=sqr(y,a*b);//查找
		if(vis.count(num)){
			return a*b-vis[num];//返回
		}
	}
	return -1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>p>>y>>z;
	if(z%p==1)cout<<"0\n";//特判
	else {
		ans=BSGS();
		if(ans!=-1)cout<<ans<<'\n';
		else cout<<"no solution\n";
	}
	return 0;
}

