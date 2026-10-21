#include <bits/stdc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
//using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll n;
	cin>>n;
	string s;
	cin>>s;
	vector<ll> v(n+3,0),ans(n+3,0);
	
	for(ll i=0;i<n;i++){
		v[i+1]=s[i]-'0';
	}
	
	vector<ll> stk1(n+3,0),stk2(n+3,0);
	ll top1=(n+1)/2,top2=(n)/2;
	ll cnt=0;
	for(ll i=1;i<=n;i++){
		cnt+=v[i];
		if(cnt>=n-i){
			top1=i;
			top2=n-i;
			break;
		}
	}
	
//	cout<<vb<<endl;
	
//	cout<<top1<<' '<<top2<<endl;
	
	for(ll i=1;i<=n;i++){
		if(v[i]){
			if((top1<=top2&&top1>0)||top2==0){
				stk1[top1--]=v[i];
//				cout<<"1-1"<<endl;
			}else{
				stk2[top2--]=v[i];
//				cout<<"1-2"<<endl;
			}
		}else{
			if(top1>=top2){
				stk1[top1--]=v[i];
//				cout<<"0-1"<<endl;
			}else{
				stk2[top2--]=v[i];
//				cout<<"0-2"<<endl;
			}
		}
	}
	
//	for(ll i=n;i>=1;i--){
//		cout<<stk1[i];
//	}
//	cout<<endl;
//	for(ll i=n;i>=1;i--){
//		cout<<stk2[i];
//	}
//	cout<<endl;
	
	ll top=0;
	
	for(ll i=1;i<=n;i++){
		ans[i]=stk1[i]+stk2[i];
	}
	
	for(ll i=1;i<=n;i++){
		ans[i+1]+=ans[i]/2;
		ans[i]%=2;
		if(ans[i]) top=i;
	}
	
//	cout<<top<<endl;
	if(top==0){
		cout<<0<<endl;
		return;
	}
	for(ll i=top;i>=1;i--){
		cout<<ans[i];
	}
	cout<<endl;
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
