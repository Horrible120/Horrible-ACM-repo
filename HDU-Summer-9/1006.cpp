#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void H_manacher(string &s,vector<array<ll,3>> &d){
	ll n=s.size();
	
	ll l=0,r=-1;
	for(ll i=0;i<n;i++){
		ll &k=d[i][1];
		if(i>r)
			k=1;
		else
			k=min(d[l+r-i][1],r-i+1);
		while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])
			k++;
		if(i+k>r){
			l=i-k+1;
			r=i+k-1;
		}
	}
	
	l=0,r=-1;
	for(ll i=0;i<n;i++){
		ll &k=d[i][2];
		if(i>r)
			k=0;
		else
			k=min(d[l+r-i+1][2],r-i+1);
		while(i-k-1>=0&&i+k<n&&s[i-k-1]==s[i+k])
			k++;
		if(i+k>r){
			l=i-k;
			r=i+k-1;
		}
	}
}

void solve(){
	string s;
	cin>>s;
	ll n=s.size();
	ll ans=0;
	
	vector<array<ll,3>> d(n+1,array<ll,3>{});
	
	H_manacher(s,d);
	
	vector<ll> lb,rb;
	
	for(ll i=0;i<n-1;i++){
		if(s[i]=='('&&s[i+1]==')'){
			lb.emplace_back(i);
			rb.emplace_back(i+1);
		}
	}
	
	if(lb.size()){
		ll l=0,r=0;
		for(ll i=0;i<n;i++){
			while(l+1<lb.size()&&lb[l+1]<i){
				l++;
			}
			while(r+1<rb.size()&&rb[r]<=i){
				r++;
			}
			
			cout<<i<<' '<<lb[l]<<' '<<rb[r]<<' '<<d[i][1]<<' '<<d[i][2]<<endl;
			
			if(lb[l]<i&&rb[r]>i){
				ans+=d[i][1];
				ans-=min(d[i][1],min(i-lb[l],rb[r]-i));
				ans+=d[i][2];
				ans-=min(d[i][2],min(i-1-lb[l],rb[r]-i));
			}else if(lb[l]<i){
				ans+=d[i][1];
				ans-=min(d[i][1],i-lb[l]);
				ans+=d[i][2];
				ans-=min(d[i][2],i-1-lb[l]);
			}else if(rb[r]>i){
				ans+=d[i][1];
				ans-=min(d[i][1],rb[r]-i);
				ans+=d[i][2];
				ans-=min(d[i][2],rb[r]-i);
			}
		}
	}
	cout<<ans<<endl;
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
