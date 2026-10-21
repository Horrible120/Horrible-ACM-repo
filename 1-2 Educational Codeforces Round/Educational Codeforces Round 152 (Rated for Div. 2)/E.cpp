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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	vector<ll> max_stk(n+1,0),min_stk(n+1,0);
	vector<array<ll,2>> ans_stk(n+1,array<ll,2>());
	ll max_top=0,min_top=0,ans_top=0,cnt=0,ans=0;
	
	for(ll i=1;i<=n;i++){
		while(max_top>0&&v[max_stk[max_top]]<v[i]){
			max_top--;
		}
		while(min_top>0&&v[min_stk[min_top]]>v[i]){
			min_top--;
		}
		
		ll len=i-max_stk[max_top]-1;
		if(len){
//			cout<<"<+> "<<i<<' '<<len<<endl;
			ll tmp=len;
			while(tmp){
				if(ans_stk[ans_top][0]<=tmp){
					cnt-=ans_stk[ans_top][0]*ans_stk[ans_top][1];
					tmp-=ans_stk[ans_top][0];
					ans_top--;
				}else{
					cnt-=tmp*ans_stk[ans_top][1];
					ans_stk[ans_top][0]-=tmp;
					tmp=0;
				}
			}
			ans_stk[++ans_top]=array<ll,2>{len,1ll};
			cnt+=len;
		}
		
		len=i-min_stk[min_top]-1;
		if(len){
//			cout<<"<-> "<<i<<" "<<len<<endl;
			ll tmp=len;
			while(tmp){
				if(ans_stk[ans_top][0]<=tmp){
					cnt-=ans_stk[ans_top][0]*ans_stk[ans_top][1];
					tmp-=ans_stk[ans_top][0];
					ans_top--;
				}else{
					cnt-=tmp*ans_stk[ans_top][1];
					ans_stk[ans_top][0]-=tmp;
					tmp=0;
				}
			}
			ans_stk[++ans_top]=array<ll,2>{len,0ll};
		}
		
//		cout<<i<<' '<<max_top<<' '<<min_top<<' '<<cnt<<endl;
		
		ans+=cnt;
		ans_stk[++ans_top]=array<ll,2>{1,0};
		max_stk[++max_top]=i;
		min_stk[++min_top]=i;
	}
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
