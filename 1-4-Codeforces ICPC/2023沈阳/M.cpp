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
			
			res=(tmp*(4+4*inv(3))%Mod-4*inv(3)+Mod*10)%Mod;
			return res;
		}
	};
	
	if(s==t&&k==1){
//		OOO
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
		ans=(tmp*(4+4*inv(3))%Mod-4*inv(3)+Mod*10)%Mod;
//		OOO
		cout<<ans<<endl;
	}
	else{
		ll len=max(s.size(),t.size())+2;
		ll n=len/2,c=1,ans=0;
		
		v2ct<ll> bk(4);
		bk[0]={0,1,3,2};
		bk[1]={1,0,2,3};
		bk[2]={3,2,0,1};
		bk[3]={2,3,1,0};
		
		vector<ll> vs(len+5,0),vt(len+5,0);
		
		for(ll i=0;i<s.size();i++)
			vs[s.size()-i-1]=s[i]-'0';
		for(ll i=0;i<t.size();i++)
			vt[t.size()-i-1]=t[i]-'0';
		
//		for(ll i=1;i<=len;i++)
//			cout<<vs[i]<<' ';
//		cout<<endl;
//		for(ll i=1;i<=len;i++)
//			cout<<vt[i]<<' ';
//		cout<<endl;
		
		
		
		for(ll i=0;i<=n;i++){
			ll tmp1=vs[i*2]+vs[i*2+1]*2;
			ll tmp2=vt[i*2]+vt[i*2+1]*2;
			
			ans=(ans+bk[tmp1][tmp2]*c)%Mod;
			
			c=(c*4+1)%Mod;
		}
		
		if(k>1){
			ll flag=1;
			if(k-2>n){
				cout<<-1<<endl;
				return;
			}
			
			ll g=0;
			for(ll i=0;i<=k-2;i++){
				ll tmp1=vs[i*2]+vs[i*2+1]*2;
				ll tmp2=vt[i*2]+vt[i*2+1]*2;
				if(tmp1!=tmp2){
					cout<<-1<<endl;
					return;
				}
				g=(g*4+4)%Mod;
			}
			ans=(ans+g)%Mod;
		}
//		OOO
		cout<<ans<<endl;
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
