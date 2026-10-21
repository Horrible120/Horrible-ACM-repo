#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
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
	vector<ll> a(n+1,0),b(n+1,0),vld(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
	}
	
	vector<ll> que(n+1,0);
	ll head=0,tail=1;
	
	set<ll> s;
	
	for(ll i=1;i<=n;i++){
		while(head>=tail&&a[i]>=que[head]){
			s.erase(que[head--]);
		}
		que[++head]=a[i];
		s.insert(a[i]);
		if(s.find(b[i])!=s.end()) vld[i]=1;
		
//		cout<<i<<endl;
//		for(ll i=tail;i<=head;i++)
//			cout<<que[i]<<' ';
//		cout<<endl;
		
		while(head>=tail&&b[i]<que[tail]){
			s.erase(que[tail++]);
		}
	}
	
	s.clear();
	que=vector<ll>(n+1,0);
	head=0;
	tail=1;
	
//	cout<<endl;
	
	
	for(ll i=n;i>=1;i--){
		while(head>=tail&&a[i]>=que[head]){
			s.erase(que[head--]);
		}
		que[++head]=a[i];
		s.insert(a[i]);
		if(s.find(b[i])!=s.end()) vld[i]=1;
		
//		cout<<i<<endl;
//		for(ll i=tail;i<=head;i++)
//			cout<<que[i]<<' ';
//		cout<<endl;
		
		while(head>=tail&&b[i]<que[tail]){
			s.erase(que[tail++]);
		}
	}
	
	ll flag=1;
	for(ll i=1;i<=n;i++) flag&=vld[i];
	
	cout<<(flag?"YES":"NO")<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cout<<hex<<16<<endl;
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
