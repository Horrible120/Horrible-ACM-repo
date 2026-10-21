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
	string s,t;
	cin>>s>>t;
	
	ll n=s.size(),m=t.size();
	
	vector<pll> vs,vt;
	
	for(ll i=0;i<n;i++){
		ll tmp=i;
		while(tmp<n&&s[tmp]==s[i]) tmp++;
		vs.emplace_back(s[i]-'0',tmp-i);
		i=tmp-1;
	}
	for(ll i=0;i<m;i++){
		ll tmp=i;
		while(tmp<n&&t[tmp]==t[i]) tmp++;
		vt.emplace_back(t[i]-'0',tmp-i);
		i=tmp-1;
	}
	
	ll ls=0,ans=0;
	
	vs.emplace_back(0,0);
	vs.emplace_back(0,0);	
	
	if(vs[0].first!=vt[0].first){
		vs[ls+2].second+=vs[ls].second;
		ls++;
		ans++;
	}
	
	for(ll i=0;i<vt.size();i++){
		
		while(ls+3<vs.size()&&vs[ls].second<vt[i].second){
			ans++;
//			if(ls+3<vs.size()){
				vs[ls+2].second+=vs[ls].second;
				vs[ls+3].second+=vs[ls+1].second;
				ls+=2;
//			}
//			else if(ls+2<vs.size()){
//				vs[ls+2].second+=vs[ls].second;
//				swap(vs[ls+2],vs[ls+1]);
//				ls++;
//			}
		}
		
		if(vs[ls].second!=vt[i].second||ls>=vs.size()){
			cout<<-1<<endl;
			return;
		}
		ls++;
	}
	
//	OOO
	
	cout<<ans<<endl;
	
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
