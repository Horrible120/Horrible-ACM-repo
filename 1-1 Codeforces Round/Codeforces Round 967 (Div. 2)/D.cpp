#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1),ans;
	map<ll,ll> mp;
	for(ll i=1;i<=n;i++) cin>>v[i],mp[v[i]]++;
	
	ll l=1,cur=1,far=0;
	set<pair<ll,ll>> s;
	for(ll i=1;i<=n;i++){
		if(mp[v[i]]==1){
//			OOO
//			cout<<i<<endl;
			mp[v[i]]--;
			s.insert(make_pair(v[i],i));
			while(1){
				if(cur%2==1){
					auto [x,y]=*s.rbegin();
//					cout<<"S "<<x<<' '<<y<<endl;
					
					
					s.erase(*s.rbegin());
					while(s.size()&&(*s.rbegin()).first==x&&(*s.rbegin()).second>far){
						y=(*s.rbegin()).second;
						s.erase(*s.rbegin());
					}
					if(mp[x]!=-1&&y>far){
						ans.emplace_back(x);
						mp[x]=-1;
						far=y;
						++cur;
//						cout<<"Add "<<x<<' '<<y<<endl;
						if(x==v[i]) break;
					}
				}
				else{
					auto [x,y]=*s.begin();
					s.erase(s.begin());
					if(mp[x]!=-1&&y>far){
						ans.emplace_back(x);
						mp[x]=-1;
						far=y;
						++cur;
						if(x==v[i]) break;
					}
				}
			}
		}
		else if(mp[v[i]]>0){
			mp[v[i]]--;
			s.insert(make_pair(v[i],i));
		}
	}
//	OOO
	cout<<ans.size()<<endl;
//	OOO
	for(auto i:ans) cout<<i<<' ';
	cout<<endl;
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
