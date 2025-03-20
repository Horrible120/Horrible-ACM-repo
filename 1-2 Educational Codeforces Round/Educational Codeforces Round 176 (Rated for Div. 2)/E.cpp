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

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

ll Calc(ll x){
	ll c=2,res=1;
	while(x){
		if(x&1)
			res=res*c%Mod;
		c=c*c%Mod;
		x=x/2;
	}
	return res-2+Mod;
}

void solve(){
	ll n,m,a,b,ans=0;
	cin>>n>>m>>a>>b;
	ans+=(a+1)*(b+1)%Mod;
	ans+=(a*(a+1)/2%Mod)*((b+1)*Calc(n)%Mod)%Mod;
	ans+=(b*(b+1)/2%Mod)*((a+1)*Calc(m)%Mod)%Mod;
	
	
	v2ct<ll> dp(30,vector<ll>(17,0));
	vector<ll> lst={a,a,b,b};
	
	dp[29][0]=1ll;
	for(ll i=28;i>=0;i--){	//第 i 位上的情况
		for(ll j=0;j<16;j++){	//枚举数位限制情况
			for(ll d=0;d<=15;d++)	//枚举新增数位的情况
				if(((d>>0&1)^(d>>1&1)^(d>>2&1)^(d>>3&1))==0)
				{
					ll flag=1,tmpj=j;
					for(ll k=0;k<4;k++)
						if(j>>k&1||(~j>>k&1&&(d>>k&1)==(lst[k]>>i&1)))
							continue;
						else if(~j>>k&1&&(d>>k&1)<(lst[k]>>i&1))
							tmpj|=(1<<k);
						else
							flag=0;
					if(flag)
						dp[i][tmpj]=(dp[i][tmpj]+dp[i+1][j])%Mod;
				}
		}
	}
	ll tmp=0;
	for(ll i=0;i<16;i++)
		tmp+=dp[0][i];
	tmp=((tmp-(a+1)*(b+1))%Mod+Mod)*((Mod+1)/2)%Mod*((Mod+1)/2)%Mod;
	ans=(ans+tmp*Calc(n)%Mod*Calc(m)%Mod)%Mod;
	
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );	
	
//	cout<<Calc(5)<<endl;
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
