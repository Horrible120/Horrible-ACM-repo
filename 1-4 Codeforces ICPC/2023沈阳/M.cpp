#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void solve(){
	string s,t;
	ll k;
	cin>>s>>t;
	cin>>k;
	
	ll len=max(s.size(),t.size())+2;
	
	vector<ll> vs(len+5,0),vt(len+5,0);
	
	for(ll i=0;i<s.size();i++)
		vs[i]=s[i]-'0';
	for(ll i=0;i<t.size();i++)
		vt[i]=t[i]-'0';
	
	auto calc=[](ll u)->ll{
		if(u==1)
			return 1ll;
		else{
			u-=2;
			ll c=4,res=0,tmp=1;
			
			while(u>0){
				if(u&1ll){
					tmp=tmp*c%Mod;
				}
				u/=2;
				c=c*c%Mod;
			}
			
			res=(tmp*(4+4*inv(3))%Mod-4*inv(3)+Mod)%Mod;
			return res;
		}
	};
	
	if(s==t&&k==1){
		cout<<0<<endl;
		return;
	}
	if(s==t){
		k-=2;
		ll c=4,ans=0,tmp=1;
		
		while(k>0){
			if(k&1ll){
				tmp=tmp*c%Mod;
			}
			k/=2;
			c=c*c%Mod;
		}
		
		ans=(tmp*(4+4*inv(3))%Mod-4*inv(3)+Mod)%Mod;
		cout<<ans<<endl;
	}
	else{
		ll n=(max(s.size(),t.size())-1)/2;
		
		ll c=1,ans=0;
		
		for(ll i=0;i<=n;i++){
			
			c=(c*4+4)%Mod;
		}
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
