#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll n=128,m;
	cin>>m;
	
	vector<multiset<string>> eg(n+1);
	vector<ll> fa(n+1,0),du(n+1,0),ind(n+1,0),oud(n+1,0);
	
	for(ll i=1;i<=n;i++)
		fa[i]=i;
	
	auto gf=[&](auto &&self,ll u)->ll{
		if(fa[u]==u)
			return u;
		return self(self,fa[u]);
	};
	
	auto merge=[&](ll x,ll y)->void{
		ll fx=gf(gf,x),fy=gf(gf,y);
		if(fx==fy)
			return;
		fa[fy]=fx;
	};
	
	for(ll i=1;i<=m;i++){
		string s;
		cin>>s;
		ll u=s[0]-'a'+1;
		ll v=s[s.size()-1]-'a'+1;
		
		merge(u,v);
		
		du[u]++;
		du[v]++;
		ind[v]++;
		oud[u]++;
		
		eg[u].insert(s);
	}
	
	ll cnt=0,flag=1;
	set<ll> fff;
	for(ll i=1;i<=n;i++){
		if(du[i]){
			if(ind[i]!=oud[i]){
				if(abs(ind[i]-oud[i])==1)
					cnt++;
				else
					flag=0;
			}
			
			fff.insert(gf(gf,i));
		}
	}
	
//	cout<<"!!! "<<cnt<<' '<<fff.size()<<endl;
	
	if((cnt==0||cnt==2)&&fff.size()==1&&flag){
		vector<string> ans;
		auto DFS=[&](auto &&self,ll u)->void{
			while(eg[u].size()){
				string sv=*eg[u].begin();
				ll v=sv[sv.size()-1]-'a'+1;
				eg[u].erase(eg[u].begin());
				ans.emplace_back(sv);
				self(self,v);
			}
		};
		
		if(cnt==0){
			for(ll i=1;i<=n;i++)
				if(du[i]){
					DFS(DFS,i);
					break;
				}
		}
		else{
			for(ll i=1;i<=n;i++)
				if((du[i]&1)&&(ind[i]+1==oud[i])){
					DFS(DFS,i);
					break;
				}
		}
		
		for(ll i=0;i<ans.size();i++){
			cout<<ans[i];
			if(i<ans.size()-1)
				cout<<'.';
		}
		cout<<endl;
	}
	else{
		cout<<"***"<<endl;
	}
	
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
