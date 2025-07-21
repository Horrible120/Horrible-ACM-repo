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
	ll n,q;
	cin>>n;
	
	vector<ll> v(n+1),cnt(5,0),in(n+1,0);
	v2ct<ll> eg(n+1,vector<ll>());
	
	for(ll i=1;i<=n;i++){
		string op,st;
		cin>>op>>st;
		if(op=="set"){
			if(st=="true")
				v[i]=2;	//0-1
			else
				v[i]=3;	//1-1
		}
		else{
			if(st=="true")
				v[i]=4;	//1-0
			else
				v[i]=1;	//0-0
		}
		cnt[v[i]]++;
	}
	
	

	cin>>q;
	
	for(ll i=1;i<=q;i++){
		ll x,y;
		cin>>x>>y;
		eg[x].emplace_back(y);
		in[y]++;
	}
	
	if(cnt[2]>1||cnt[4]>1){
//		OOO
		cout<<-1<<endl;
		return;
	}
	
	set<ll> ok[5];
	
	for(ll i=1;i<=n;i++)
		if(in[i]==0)
			ok[v[i]].insert(i);
	
	vector<ll> ans;
	
	ll now=0;
	for(ll i=1;i<=5;i++){
		ll ty=(i-1)%4+1;
		
		while(ok[ty].size()){
			ll u=*ok[ty].begin();
			ok[ty].erase(ok[ty].begin());
			if(ty==1){
				if(now!=0)
					break;
			}
			else if(ty==2){
				if(now!=0)
					break;
				now=1;
			}
			else if(ty==3){
				if(now!=1)
					break;
			}
			else if(ty==4){
				if(now!=1)
					break;
				now=0;
			}
			
			ans.emplace_back(u);
			for(auto it:eg[u]){
				in[it]--;
				if(in[it]==0)
					ok[v[it]].insert(it);
			}
				
		}
	}
	
	if(ans.size()==n){
		for(auto it:ans)
			cout<<it<<' ';
		cout<<endl;
	}
	else
		cout<<-1<<endl;
	
	
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
