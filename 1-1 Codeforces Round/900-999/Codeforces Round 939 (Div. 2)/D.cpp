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
	ll ans=-1,ans_par=0;
	vector<pll> op;
	vector<ll> v(n+1,0);
	for(ll i=0;i<n;i++)
		cin>>v[i];
	
	for(ll i=0;i<(1<<n);i++){
		ll tmp=0,cnt=0;
		for(ll j=0;j<n;j++)
			if((i>>n-j-1)&1)
				tmp+=v[j]+cnt*cnt,
				cnt=0;
			else
				cnt++;
		tmp+=cnt*cnt;
		if(tmp>ans)
			ans=tmp,
			ans_par=i;
	}
	
	auto mdf=[&](auto &&self,ll l,ll r)->void{
		if(l==r)
			return;
		
		self(self,l,r-1);
		op.emplace_back(l,r);
		op.emplace_back(l,r-1);
		self(self,l,r-1);
	};
	
//	for(ll i=0;i<n;i++)
//		cout<<((ans_par>>n-i-1)&1)<<' ';
//	cout<<endl;
	
	ll cnt=0;
	for(ll i=0;i<n;i++){
		if(~(ans_par>>n-i-1)&1)
			cnt++;
		else if(cnt){
//			cout<<">>>"<<i<<' '<<cnt<<endl;
			for(ll j=i-1;j>=i-cnt;j--)
				if(v[j]==0){
					op.emplace_back(i-cnt+1,i);
					break;
				}
			op.emplace_back(i-cnt+1,i);
			mdf(mdf,i-cnt+1,i);
			op.emplace_back(i-cnt+1,i);
			cnt=0;
		}
	}
	
	if(cnt){
//		cout<<">>>"<<n<<' '<<cnt<<endl;
		for(ll j=n-1;j>=n-cnt;j--)
			if(v[j]==0){
				op.emplace_back(n-cnt+1,n);
				break;
			}
		op.emplace_back(n-cnt+1,n);
		mdf(mdf,n-cnt+1,n);
		op.emplace_back(n-cnt+1,n);
		cnt=0;
	}
	
	cout<<ans<<' '<<op.size()<<endl;
	
	for(auto [l,r]:op)
		cout<<l<<' '<<r<<'\n';
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
