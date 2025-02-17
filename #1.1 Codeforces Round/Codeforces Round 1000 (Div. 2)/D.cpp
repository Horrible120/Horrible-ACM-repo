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
	ll n,m;
	cin>>n>>m;
	
	vector<ll> a(n+1),b(m+1);
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=m;i++) cin>>b[i];
	
	sort(a.begin()+1,a.end());	//排序
	sort(b.begin()+1,b.end());
	
	ll mk=min((n+m)/3,min(n,m));	//最多的三角形个数
	
	vector<ll> A(n+1),B(m+1);	//底边长度序列
	
	for(ll i=1;i<=n/2;i++)
		A[i]=(a[n-i+1]-a[i]);
	for(ll i=1;i<=m/2;i++)
		B[i]=(b[m-i+1]-b[i]);
	
	ll s=0,t=0,ans=0;
	cout<<mk<<endl;
	if(mk)
		for(ll i=1;i<=mk;i++){
			ll sx=n-i,tx=m-i;
			if(A[s+1]>=B[t+1])	//贪心，加入一个大的元素
				ans+=A[++s];
			else
				ans+=B[++t];
				
			while(s>sx){	//调整，如果超出限制就减少所选的元素数量
				ans-=A[s--];
				ans+=B[++t];
			}
			while(t>tx){
				ans-=B[t--];
				ans+=A[++s];
			}
			cout<<ans<<' ';
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

//	a<n-k
//	b<m-k
