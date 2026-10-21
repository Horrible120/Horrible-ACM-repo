#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937 rnd(time(0));

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> book(n+1,0);
	ll a,b,c;
	
	ll tmp=rnd()%n+1;
	while(book[tmp]) tmp=rnd()%n+1;
	a=tmp;
	book[a]=1;
	while(book[tmp]) tmp=rnd()%n+1;
	b=tmp;
	book[b]=1;
	while(book[tmp]) tmp=rnd()%n+1;
	c=tmp;
	book[c]=1;
	for(ll i=1;i<=75;i++){
		ll f;
		cout<<"? "<<a<<' '<<b<<' '<<c<<endl;
		cin>>f;
		if(f==0){
			cout<<"! "<<a<<' '<<b<<' '<<c<<endl;
			return;
		}
		else{
			book[f]=1;
			if(i%3==0)
				a=f;
			else if(i%3==1)
				b=f;
			else
				c=f;
		}
	}
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
