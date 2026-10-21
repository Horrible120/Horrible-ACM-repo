#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> v(n+1,0);
	vector<tuple<ll,ll,ll>> ans;
	map<ll,ll> mp;
	ll flag=0,z=0;
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		
		if(!flag){
			if(mp[k-v[i]]){
				ll a=i,b=mp[k-v[i]];
				ans.emplace_back(a,b,v[i]);
				v[a]=0,v[b]=k;
				flag=b;
				z=a;
			}
		}
		
		mp[v[i]]=i;
	}
	
	if(!flag){
		ll f=1;
		for(ll i=2;i<=n;i++)
			if(v[i]<v[i-1])
				f=0;
		if(f)
			cout<<0<<endl;
		else
			cout<<-1<<endl;
		return;
	}
	else{
		if(v[1]+v[n]!=k){
			if(z==n){
				ans.emplace_back(flag,z,k-v[1]);
				v[flag]=v[1];
				v[n]=k-v[1];
			}
			else if(flag==1){
				ans.emplace_back(flag,z,v[n]);
				v[1]=k-v[n];
				v[z]=v[n];
			}
			else{
				ans.emplace_back(flag,z,v[1]);
				ans.emplace_back(1,flag,v[1]-k+v[n]);
				v[z]=v[1];
				v[flag]=v[n];
				v[1]=k-v[n];
			}
		}
	}
	
	vector<pll> tmp(n+1);
	for(ll i=2;i<n;i++)
		tmp[i]=make_pair(v[i],i);
	
	sort(tmp.begin()+2,tmp.end()-1);
	
	vector<pll> trans;
	vector<ll> vis(n+1,0);
	for(ll i=2;i<=n-1;i++){
		vis[i]=1;
		ll x=i;
		while(!vis[tmp[x].second]){
			vis[tmp[x].second]=1;
			trans.emplace_back(x,tmp[x].second);
			x=tmp[x].second;
		}
	}
	
	for(auto [a,b]:trans){
		ll va=v[a];
		ans.emplace_back(1,n,v[1]-k+v[a]);
		v[1]=k-v[a];
		v[n]=v[a];
		ans.emplace_back(a,1,v[a]-v[b]);
		v[1]=k-v[b];
		v[a]=v[b];
		ans.emplace_back(b,1,v[b]-va);
		v[b]=va;
		v[1]=k-va;
	}
	
	ans.emplace_back(1,n,v[1]);
	
	cout<<ans.size()<<endl;
	for(auto [a,b,w]:ans)
		cout<<a<<' '<<b<<' '<<w<<'\n';
	cout.flush();
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
