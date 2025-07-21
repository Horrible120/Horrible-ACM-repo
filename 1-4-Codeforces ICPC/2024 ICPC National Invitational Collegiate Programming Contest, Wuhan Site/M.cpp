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
	ll n;
	cin>>n;
	
	vector<ll> v(n+1,0);
	vector<ll> ans;
	multiset<ll> s;
	
	for(ll i=1;i<=n;i++)
		cin>>v[i],
		s.insert(v[i]);
	
	sort(v.begin()+1,v.end(),greater<ll>());
	
	auto slv=[&](auto &&self,ll x)->ll{
		if(s.find(x)==s.end())
			return 0;
		
		if(x&1ll){
			if(s.find(x+1)!=s.end()){
				s.erase(s.find(x+1));
				s.erase(s.find(x));
				return x*2+1;
			}
			else if(s.find(x-1)!=s.end()){
				s.erase(s.find(x-1));
				s.erase(s.find(x));
				return x*2-1;
			}
			else
				return 0;
		}
		else{
			if(s.find(x+1)!=s.end()){
				s.erase(s.find(x+1));
				s.erase(s.find(x));
				return x*2+1;
			}
			else if(x==2){
				if(s.find(3)!=s.end()){
					s.erase(s.find(3));
					s.erase(s.find(2));
					return 5;
				}
				else{
					s.erase(s.find(2));
					if(s.find(1)!=s.end()){
						if(s.find(2)!=s.end()){
							s.erase(s.find(2));
							s.erase(s.find(1));
							return 5;
						}
						else{
							s.erase(s.find(1));
							return 3;
						}
					}
					else{
						s.insert(2);
						return 0;
					}
				}
			}
			else{
				ll tmp=self(self,x/2);
				if(tmp){
					s.erase(s.find(x));
					return x+tmp;
				}
				else if(s.find(x-1)!=s.end()){
					s.erase(s.find(x-1));
					s.erase(s.find(x));
					return x*2-1;
				}
				else
					return 0;
			}
		}
	};
	
	for(ll i=1;i<=n;i++){
		if(s.size()&&s.find(v[i])!=s.end()){
			ll tmp=slv(slv,v[i]);
			if(tmp==0){
				s.erase(s.find(v[i]));
				ans.emplace_back(v[i]);
			}
			else{
				ans.emplace_back(tmp);
			}
//			cout<<"!!! "<<i<<' '<<tmp<<' '<<s.size()<<endl;
		}
	}
	
	sort(ans.begin(),ans.end(),greater<ll>());
	
//	OOO
	cout<<ans.size()<<endl;
	for(auto it:ans)
		cout<<it<<' ';
	cout<<endl;
	
	
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
