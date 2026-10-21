#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
//using namespace __gnu_pbds;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

//template <typename T, typename Compare = std::less<T>>
//using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<int> v(n+1,0);
	ll ssum=0;
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		ssum+=v[i];
	}
	ll l=1,r=ssum;
	
	vector<ll> pref(n+2,0),suff(n+2,0);
	
	
	
	while(l<r){
		ll mid=l+r>>1;
		
		for(ll i=1;i<=n;i++){
			pref[i]=suff[i]=0;
		}
		
		
		ll sum=0,cnt=0,tmp=0,flag=0;
		
		{
			priority_queue <ll,vector<ll>> s;
			
			for(ll i=1;i<=n;i++){
				if(sum+v[i]<=mid){
					s.push(v[i]);
					cnt++;
					sum+=v[i];
				}else if(s.size()){
					tmp=s.top();
					if(tmp>v[i]){
						sum=sum+v[i]-tmp;
						s.pop();
						s.push(v[i]);
					}
				}
				
				if(cnt>=k){
					flag=1;
					break;
				}
				pref[i]=cnt;
			}
			
			if(flag){
				r=mid;
				continue;
			}
		}
		
		{
			priority_queue <ll,vector<ll>> s;
			sum=0,cnt=0,tmp=0;
			for(ll i=n;i>=1;i--){
				if(sum+v[i]<=mid){
					s.push(v[i]);
					cnt++;
					sum+=v[i];
				}else if(s.size()){
					tmp=s.top();
					if(tmp>v[i]){
						sum=sum+v[i]-tmp;
						s.pop();
						s.push(v[i]);
					}
				}
				suff[i]=cnt;
				if(cnt>=k){
					flag=1;
					break;
				}
			}
		}
		
			
		for(ll i=0;i<=n&&!flag;i++){
			if(pref[i]+suff[i+1]>=k){
				flag=true;
			}
		}
		
		if(flag){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	
//	OOO
	cout<<l<<'\n';
	
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
