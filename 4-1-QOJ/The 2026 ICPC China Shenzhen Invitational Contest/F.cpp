#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll tt=1;
ll n,k;
const ll N=6090;
ll to[N],ne[N],he[N];
ll tot;
void add(ll x,ll y){
	++tot;
	to[tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
}
unordered_map<ll,ll> sgg;
set<ll> s;
void clear(){
	for(int i=1;i<=tot;i++)to[i]=ne[i]=0;
	for(int i=1;i<=n;i++)he[i]=0;
	tot=0;
	sgg.clear();
}

void dfs(ll x,ll fa,ll now);
ll sg(ll x,ll fa);
ll ans(ll x);
void solve(){
	cin>>n>>k;
	ll u,v;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++){
		cout<<ans(i);
	}
	cout<<'\n';
}

int main() {
	cin >> tt;    //非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		clear();
		solve();
//        cout.flush();
	}
	cout.flush();
	
	return 0;
}

void dfs(ll x,ll fa,ll now,ll dep){
	if(dep>k)return;
	ll y;
	for(int i=he[x];i;i=ne[i]){
		y=to[i];
		if(y==fa)continue;
		now^=sg(y,x);
	}
	s.erase(now);
	for(int i=he[x];i;i=ne[i]){
		y=to[i];
		if(y==fa)continue;
		now^=sg(y,x);
		dfs(y,x,now,dep+1);
		now^=sg(y,x);
	}
}
ll sg(ll x,ll fa){
	if(sgg.count(x*1000000+fa)==0){
		ll y;
		for(int i=he[x];i;i=ne[i]){
			y=to[i];
			if(y==fa)continue;
			sg(y,x);
		}
		s.clear();
		for(int i=0;i<=n+1;i++)s.insert(i);
		dfs(x,fa,0,1);
		sgg[x*1000000+fa]=(*s.begin());
//        cerr<<(*s.begin());
		//printf("x:%d,fa:%d %d\n",x,fa,sgg[x*1000000+fa]);
	}
	return sgg[x*1000000+fa];
}
ll ans(ll x){
	ll y,res=0;
	for(int i=he[x];i;i=ne[i]){
		y=to[i];
		res^=sg(y,x);
	}
	if(res==0)return 0;
	else return 1;
}
