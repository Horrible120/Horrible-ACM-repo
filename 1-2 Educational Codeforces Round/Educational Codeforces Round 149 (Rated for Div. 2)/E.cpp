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

ll fct[1000001];
ll c2[1000001];

void init(){
	ll n=1e6;
	fct[0]=c2[0]=1;
	for(ll i=1;i<=n;i++)
		fct[i]=fct[i-1]*i%Mod,
		c2[i]=c2[i-1]*2%Mod;
}

void solve(){
	ll k,ans=1;
	cin>>k;
	
	vector<ll> v((1<<k)+1,0),g((1<<k)+1,0);
	
	for(ll i=1;i<=1<<k;i++){
		cin>>g[i];
		if(g[i]>0)
			v[g[i]]=i;
	}
	
	for(ll i=k-1;i>=0&&ans;i--){
		ll cnt=0,dnt=0;

//		for(ll j=(1<<i)+1;j<=1<<i+1;j++)
			
		
		
		for(ll j=0;j<1<<i;j++){
			ll tmp=0,ttmp=0;
			
			for(ll l=(j<<k-i)+1;l<=(j+1<<k-i);l++){
				if(g[l]>0&&__lg(g[l]-1)<i)
					tmp++;
				if(g[l]>0&&__lg(g[l]-1)==i)
					ttmp++;
			}
			
//			cout<<">>> "<<j<<' '<<ttmp<<' '<<tmp<<endl;
			
			if(ttmp==0)
				cnt++;
			if(ttmp==0&&tmp==0)
				dnt++;
			if(tmp>1||ttmp>1)
				ans=0;
		}
//		cout<<">>> "<<i<<' '<<dnt<<' '<<cnt<<endl;
		ans=ans*c2[dnt]%Mod*fct[cnt]%Mod;
	}
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
