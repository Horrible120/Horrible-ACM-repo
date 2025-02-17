#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

struct Elm {
	ll status=0;
	ll cnt=0;
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++) cin>>v[i];
	
	auto check=[&](ll val)->Elm{
		Elm res={};
		ll mx=0,mn=0;
		ll tmp,i;
		for(i=1;i<=n;i++){
			tmp=((val/v[i])+1)/2;
			
//			cout<<tmp<<endl;
			
			res.cnt+=tmp;
			mx+=tmp*tmp*v[i];
			mn+=tmp*tmp*v[i];
			if((tmp*2-1)*v[i]==val) mn-=val,res.cnt-=1;
			if(mx<0||mn<0||mx<mn||tmp>1e9||tmp*v[i]>1e18) break;
		}
		if(mx<0||mn<0||mx<mn||tmp>1e9||tmp*v[i]>1e18){
			res.status=-1;
		}
		else if(m<=mx&&m>=mn){
			res.status=0;
			res.cnt+=(m-mn)/val;
			
		}
		else if(m<mn){
			res.status=-1;
		}
		else
			res.status=1;
//		cout<<"!!!"<<val<<' '<<res.status<<' '<<res.cnt<<' '<<mx<<' '<<mn<<endl;
		return res;
	};
	
	ll l=0,r=INF,ans=0;
	while(l<=r){
		ll mid=(l+r+1)/2;
		Elm flag=check(mid);
		if(flag.status==0){
			ans=flag.cnt;
			break;
		}
		else if(flag.status==1){
			l=mid+1;
		}
		else {
			r=mid-1;
		}
	}
	
//	OOO
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
