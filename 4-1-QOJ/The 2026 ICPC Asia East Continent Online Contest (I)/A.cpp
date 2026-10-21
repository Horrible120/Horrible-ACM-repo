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

	vector<char> op(n+1);
	vector<ll> a(n+1),pos(n+1),last(n+1);
	for(ll i=1;i<=n;i++) cin>>op[i]>>a[i];

	vector<ll> b=a;
	sort(b.begin()+1,b.end());
	b.erase(unique(b.begin()+1,b.end()),b.end());

	for(ll i=1;i<=n;i++){
		ll x=lower_bound(b.begin()+1,b.end(),a[i])-b.begin();
		if(op[i]=='+'){
			pos[x]=i;
			last[i]=i;
		}else if(op[i]=='T') last[pos[x]]=i;
	}

	stack<ll> st;
	string ans;
	ans.reserve(2*n);
	for(ll i=1;i<=n;i++){
		if(op[i]=='+'){
			st.push(i);
			ans+='+';
		}else ans+='?';
		while(!st.empty()&&last[st.top()]<=i){
			st.pop();
			ans+='-';
		}
	}

	cout<<ans<<'\n';
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
