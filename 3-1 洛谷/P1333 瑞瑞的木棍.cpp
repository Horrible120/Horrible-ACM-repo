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
	string s,t;
	ll cnt=0;
	map<string,ll> eg;
	map<string,string> fa;
	
	auto gf=[&](auto &&self,string &u)->string{
		if(fa[u]==u)
			return u;
		return fa[u]=self(self,fa[u]);
	};
	
	while(cin>>s){
		cin>>t;
		cnt++;
		
		if(fa[s]=="")
			fa[s]=s;
		if(fa[t]=="")
			fa[t]=t;
		
		if(gf(gf,s)!=gf(gf,t)){
			fa[gf(gf,s)]=gf(gf,t);
		}
		eg[s]++;
		eg[t]++;
	}
	
	ll flag=0;
	set<string> f;
	for(auto &it:eg){
		if(it.second&1)
			flag++;
		string tmp=it.first;
		tmp=gf(gf,tmp);
		f.insert(tmp);
	}
		
	
	
	if(((flag==2||flag==0)&&f.size()==1)||cnt==0)
		cout<<"Possible"<<endl;
	else
		cout<<"Impossible"<<endl;
	
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
