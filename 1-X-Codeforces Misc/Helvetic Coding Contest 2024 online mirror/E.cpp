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
	ll m,n,ts=0,tl=0;
	cin>>m>>n;
	vector<ll> s(m+1,0),l(m+1,0);
	vector<ll> stl(40),sts(40),ltl(40),lts(40);
	
	for(ll i=1;i<=m;i++)
		cin>>s[i],ts+=s[i];
	for(ll i=1;i<=m;i++)
		cin>>l[i],tl+=l[i];
	
	for(ll i=1;i<=m;i++){
		stl[0]+=s[i]*l[i];
		lts[0]+=l[i]*s[i];
		sts[0]+=s[i]*s[i];
		ltl[0]+=l[i]*l[i];
	}
	
	if(n==1){
		ll ans=0;
		ans=(s[1]*(tl+ts)+l[1]*ts)%Mod;
		cout<<ans<<endl;
		return;
	}
	
	n-=1;
	
	stl[0]%=Mod;
	sts[0]%=Mod;
	lts[0]%=Mod;
	ltl[0]%=Mod;
	
	ll anssl=0,ansls=0,ansss=0,ansll=0,c=0;
	while(n){
		if(n&1ll){
			if(anssl+ansls+ansll+ansss==0){
				anssl=stl[c];
				ansls=lts[c];
				ansll=ltl[c];
				ansss=sts[c];
			}
			else{
				ll tmpsl=(ansss*(ltl[c]+stl[c])%Mod+anssl*stl[c])%Mod;
				ll tmpls=(ansls*(lts[c]+sts[c])%Mod+ansll*sts[c])%Mod;
				ll tmpss=(ansss*(lts[c]+sts[c])%Mod+anssl*sts[c])%Mod;
				ll tmpll=(ansls*(ltl[c]+stl[c])%Mod+ansll*stl[c])%Mod;
				
				anssl=tmpsl;
				ansls=tmpls;
				ansll=tmpll;
				ansss=tmpss;
			}
		}
		n/=2;
		
		stl[c+1]=(sts[c]*(ltl[c]+stl[c])%Mod+stl[c]*stl[c])%Mod;
		lts[c+1]=(lts[c]*(lts[c]+sts[c])%Mod+ltl[c]*sts[c])%Mod;
		sts[c+1]=(sts[c]*(lts[c]+sts[c])%Mod+stl[c]*sts[c])%Mod;
		ltl[c+1]=(lts[c]*(ltl[c]+stl[c])%Mod+ltl[c]*stl[c])%Mod;
		
		c++;
	}
	
	ll ans=(s[1]*((ansls+ansss)*(tl+ts)%Mod+(ansll+anssl)*ts%Mod)%Mod+l[1]*(anssl*ts%Mod+ansss*(ts+tl)%Mod))%Mod;
	
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
