#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,lim=1;
	cin>>n;
	vector<ll> a(n);
	for(ll i=0;i<n;i++){
		cin>>a[i];
		lim=max(lim,a[i]);
	}

	vector<ll> spf(lim+1);
	for(ll i=2;i<=lim;i++)
		if(!spf[i]){
			spf[i]=i;
			for(ll j=i*i;j<=lim;j+=i)
				if(!spf[j])
					spf[j]=i;
		}

	for(ll i=0;i<n;i++){
		ll x=a[i],val=1;
		while(x>1){
			ll p=spf[x],cnt=0;
			while(x%p==0){
				x/=p;
				cnt^=1;
			}
			if(cnt)
				val*=p;
		}
		a[i]=val;
	}
	sort(a.begin(),a.end());
	if(a[0]==1){
		cout<<1<<'\n';
		return;
	}
	for(ll i=1;i<n;i++)
		if(a[i]==a[i-1]){
			cout<<2<<'\n';
			return;
		}

	vector<ll> id(lim+1,-1),val;
	vector<vector<ll>> eg;
	auto get=[&](ll x)->ll{
		if(id[x]==-1){
			id[x]=val.size();
			val.emplace_back(x);
			eg.emplace_back();
		}
		return id[x];
	};
	for(ll i=0;i<n;i++){
		ll p=spf[a[i]],q=a[i]/p;
		ll u=get(p),v=get(q);
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}

	ll m=val.size(),ans=INF;
	vector<ll> dis(m),fa(m);
	for(ll s=0;s<m;s++){
		if(val[s]>1000)
			continue;
		fill(dis.begin(),dis.end(),-1);
		fill(fa.begin(),fa.end(),-1);
		queue<ll> que;
		dis[s]=0;
		que.push(s);
		while(!que.empty()){
			ll u=que.front();
			que.pop();
			for(ll i=0;i<(ll)eg[u].size();i++){
				ll v=eg[u][i];
				if(dis[v]==-1){
					dis[v]=dis[u]+1;
					fa[v]=u;
					que.push(v);
				}else if(fa[u]!=v&&fa[v]!=u)
					ans=min(ans,dis[u]+dis[v]+1);
			}
		}
	}
	cout<<(ans==INF?-1:ans)<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

//	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
