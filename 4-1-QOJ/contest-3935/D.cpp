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
const ll N=1000098;
ll n,m;
struct node{
	ll d;
	char op;
	bool operator <(const node &b)const{
		return d>b.d;
	}
};
node a[N];
ll fd(ll now){
	ll L=-1,R=-1;
	for(int i=now;i<=n;i++){
		if(a[i].op=='1'||a[i].op=='X'){
			R=i;break;
		}
	}
	for(int i=now;i>=1;i--){
		if(a[i].op=='1'){
			L=i;break;
		}
	}
	if(R==-1&&L==-1)return 0;
	if(R==-1){
		return max(0ll,a[now].d-a[L].d/2);
	}
	if(L==-1){
		return a[R].d/2;
	}
	return max(a[R].d/2,a[now].d-a[L].d/2);
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].op>>a[i].d;
		if(a[i].op=='1'||a[i].op=='X')a[i].d*=2;
	}
	sort(a+1,a+n+1);
//	for(int i=1;i<=n;i++){
//		cout<<a[i].op<<' '<<a[i].d<<'\n';
//	}
//	cout<<'\n';
	ll ans=0;
	for(int i=1;i<=n;i++){
//		cout<<ans<<'\n';
		if(!m)break;
		if(a[i].op=='X'){
			ans+=a[i].d/2*m;break;
		}
		if(a[i].op=='1'){
			ans+=a[i].d/2;
			m--;
		}
		if(a[i].op=='2'){
			if(m>=2){
				ans+=a[i].d;
				m-=2;
			}
			else{
				assert(m==1);
				ans+=fd(i);
				break;
			}
		}
	}
	cout<<ans;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	ll tt=1;
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
