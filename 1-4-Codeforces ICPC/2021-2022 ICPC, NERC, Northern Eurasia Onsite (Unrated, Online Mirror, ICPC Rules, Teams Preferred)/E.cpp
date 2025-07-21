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
	ll L,n,flag=0,ansl=0,ansr=0;
	cin>>L>>n;
	vector<ll> v(n+3,0);
	vector<pll> pv(n+2);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	for(ll i=1;i<=n-1;i++){
		pv[i].first=v[i];
		pv[i].second=v[i+1];
	}
	pv[n].first=pv[n].second=L;
	ll del_l=0,del_r=L;
	while(del_l<del_r){
		ll del_mid=(del_r+del_l)/2;
		ll flag_del=0,len_l=0,len_r=L;
		while(len_l<=len_r){
			ll len_mid=(len_l+len_r)/2;
			ll l=0,r=0,flag_len=1;
			ll step_a=len_mid,step_b=len_mid+del_mid;
//			cout<<">>>>"<<step_a<<' '<<step_b<<endl;
			for(ll i=1;i<=n;i++){
				l=max(l+step_a,pv[i].first);
				r=min(r+step_b,pv[i].second);
				
//				cout<<"!!! "<<l<<' '<<r<<' '<<pv[i].first<<' '<<pv[i].second<<endl;
				
				if(l>pv[i].second){
					flag_len=-2;
					break;
				}
				else if(r<pv[i].first){
					flag_len=-1;
					break;
				}
			}
//			cout<<"//// "<<flag_len<<endl;
			if(flag_len==-2)
				len_r=len_mid-1;
			else if(flag_len==-1)
				len_l=len_mid+1;
			else{
				flag_del=1;
				ansl=step_a;
				ansr=step_b;
				break;
			}
			
		}
		
		flag|=flag_del;
		if(flag_del)
			del_r=del_mid;
		else
			del_l=del_mid+1;
	}
	assert(flag==1);
	vector<pll> ans(n+2);
	ans[0]=make_pair(0,0),ans[n]=make_pair(L,L);
	ll l=0,r=0;
	for(ll i=1;i<=n;i++){
		l=max(l+ansl,pv[i].first);
		r=min(r+ansr,pv[i].second);
		ans[i].first=l;
		ans[i].second=r;
	}
	
	for(ll i=n-1;i>=1;i--){
		ans[i].first=max(ans[i+1].first-ansr,ans[i].first);
		ans[i].second=ans[i].first;
	}
//	cout<<">>>"<<ansl<<' '<<ansr<<endl;
	for(ll i=0;i<n;i++)
		cout<<ans[i].first<<' '<<ans[i+1].first<<endl;
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
