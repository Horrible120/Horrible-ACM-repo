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

void solve(){
	ll n,ans=0;
	cin>>n;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++) cin>>v[i];
	
	vector<ll> tmp=v;
	sort(tmp.begin()+1,tmp.end());
	tmp.erase(std::unique(tmp.begin()+1,tmp.end()),tmp.end());
	
	for(ll i=1;i<=n;i++)
		v[i]=lower_bound(tmp.begin()+1,tmp.end(),v[i])-tmp.begin();
	
	auto check=[&](ll l,ll r){
		vector<pair<ll,ll>> stk(r-l+2);
		vector<ll> _v,tmp;
		_v.assign(v.begin()+l-1,v.begin()+r+1);
		tmp=_v;
		sort(tmp.begin()+1,tmp.end());
		tmp.erase(std::unique(tmp.begin()+1,tmp.end()),tmp.end());
		
		for(ll i=1;i<_v.size();i++)
			_v[i]=lower_bound(tmp.begin()+1,tmp.end(),_v[i])-tmp.begin();
//		for(ll i=1;i<=r-l+1;i++)
//			cout<<_v[i]<<" \n"[i==r-l+1];
//		cout.flush();
		
		ll top=0;
		for(ll i=1;i<_v.size();i++){
			stk[++top]=make_pair(_v[i],_v[i]);
			while(top>1&&(stk[top].first-1==stk[top-1].second||stk[top-1].first-1==stk[top].second)){
				stk[top-1]=make_pair(min(stk[top].first,stk[top-1].first),max(stk[top].second,stk[top-1].second));
				top--;
			}
		}
		if(top==1) return 1;
		else return 0;
	};
	
	for(ll i=1;i<=n;i++){
		ll l=i,r=i,c=1;
		while(r<n&&check(l,r)){
//			cout<<"$$$"<<i<<' '<<r<<' '<<check(l,r)<<endl;
			r+=c;
			c*=2;
			r=min(r,n);
		}
		
		while(l<r){
			ll mid=(l+r+1)/2;
//			cout<<"$$$"<<i<<' '<<mid<<' '<<check(l,mid)<<endl;
			if(check(i,mid)) l=mid;
			else r=mid-1;
		}
//		cout<<"!!!"<<i<<' '<<r<<endl;
		ans+=r-i;
		i=r;
	}
//	OOO
	cout<<ans<<endl;
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
