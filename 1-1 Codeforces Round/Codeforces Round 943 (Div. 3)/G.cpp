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

vector<ll> Z_Algo(string &s){
	vector<ll> z(s.size());
	for(ll i=1,l=0,r=0;i<s.size();i++){
		if(r>=i&&z[i-l]<r-i+1)
			z[i]=z[i-l];
		else{
			z[i]=max(0LL,r-i+1);
			while(i+z[i]<s.size()&&s[z[i]]==s[i+z[i]])
				++z[i];
		}
		if(i+z[i]-1>r)
			l=i,r=i+z[i]-1;
	}
	return z;
}

void solve(){
	ll n,l,r;
	cin>>n>>l>>r;
	string s;
	cin>>s;
	auto z=Z_Algo(s);
	z[0]=n;
	
//	for(ll i=0;i<n;i++)
//		cout<<z[i]<<' ';
//	cout<<endl;
	
	set<pll,greater<pll>> st;
	set<ll> idx;
	for(ll i=0;i<n;i++)
		st.insert(make_pair(z[i],i));
	
//	OOO cout<<st.size()<<endl;
	
	vector<ll> ans(n+1,0);
	for(ll len=n;len>=1;len--){
		while(st.size()&&(*st.begin()).first>=len){
			idx.insert((*st.begin()).second);
			st.erase(st.begin());
		}
		ll cnt=0;
		auto u=idx.begin();
		while(u!=idx.end()){
			cnt++;
			u=idx.lower_bound((*u)+len);
		}
		while(cnt>0&&ans[cnt]==0)
			ans[cnt--]=len;
	}
	
//	OOO
	for(ll i=l;i<=r;i++)
		cout<<ans[i]<<' ';
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
