#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<array<ll,2>> v(n+1,array<ll,2>());
	
	for(ll i=1;i<=n;i++){
		cin>>v[i][0];
	}
	
	for(ll i=1;i<=n;i++){
		cin>>v[i][1];
	}
	
	struct cmp{
		bool operator () (const array<ll,2> &a,const array<ll,2> &b) const{
			return a[0]*a[1]<b[0]*b[1];
		}
	};
	
	sort(v.begin()+1,v.end(),cmp());
	
//	cout<<">>>> "<<v[1][0]<<endl;
	
	ll l=1,r=1,ans=n;
	
	while(l<=r&&r<=n){
		ll flag=0;
		
		ll ld=v[l][0]*v[l][1],rd=v[r][0]*v[r][1];
		
		if(rd-ld<=k){
			vector<ll> vk(k+2,0);
			ll mvl=0;
			
			for(ll i=1;i<l;i++){
				if((ld-1ll)/v[i][0]==rd/v[i][0]){
					ll tmp=(ld/v[i][0])*v[i][0];
					if(tmp>0&&rd-tmp<=k)
						vk[rd-tmp]=max(vk[rd-tmp],tmp+v[i][0]-rd);
					else
						mvl=max(mvl,tmp+v[i][0]-rd);
				}
			}
			
			for(ll i=r+1;i<=n;i++){
				if((ld-1ll)/v[i][0]==rd/v[i][0]){
					ll tmp=(ld/v[i][0])*v[i][0];
					if(tmp>0&&rd-tmp<=k)
						vk[rd-tmp]=max(vk[rd-tmp],tmp+v[i][0]-rd);
					else
						mvl=max(mvl,tmp+v[i][0]-rd);
				}
			}
			
			for(ll i=k;i>=rd-ld;i--){
				if(mvl+i<=k){
					flag=1;
				}
				mvl=max(mvl,vk[i]);
			}
			
		}
		
//		cout<<"W "<<l<<' '<<r<<' '<<flag<<endl;
		
		if(flag){
			ans=min(ans,n-(r-l+1));
			if(r<n) ++r;
			else break;
		}else{
			++l;
			if(r<l) ++r;
		}
		
		
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
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
