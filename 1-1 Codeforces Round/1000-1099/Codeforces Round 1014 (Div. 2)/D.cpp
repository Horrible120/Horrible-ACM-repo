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
	ll n,cnt[4]={0,0,0,0};
	cin>>n;
	string s;
	cin>>s;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		if(s[i-1]=='L') v[i]=1;
		else if(s[i-1]=='I') v[i]=2;
		else v[i]=3;
		cnt[v[i]]++;
	}
	vector<ll> ans;
	ll sum=0;
	
	for(ll i=1;i<n;i++){
		if(v[i]!=v[i+1]){
			if(cnt[v[i]]>0){
				ll tp=i+sum;
				while(cnt[v[i]]){
					cnt[v[i]]--;
					ans.emplace_back(tp);
					ans.emplace_back(tp);
					sum+=2;
				}
			}
			
			if(cnt[v[i+1]]>0){
				while(cnt[v[i+1]]){
					cnt[v[i+1]]--;
					ans.emplace_back(i+sum);
					ans.emplace_back(i+sum+1);
					sum+=2;
				}
			}
		}
		if(cnt[1]+cnt[2]+cnt[3]==0) break;
	}
	if(cnt[1]+cnt[2]+cnt[3]>0)
		cout<<-1<<endl;
	else{
		cout<<sum<<endl;
		for(auto it:ans)
			cout<<it<<endl;
	}
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
