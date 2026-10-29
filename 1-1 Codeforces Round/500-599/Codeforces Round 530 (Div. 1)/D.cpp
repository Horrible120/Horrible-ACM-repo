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
	ll q;
	cin>>q;
	vector<multiset<ll>> bag(30);
	vector<ll> sum(30);
	ll cnt=0;

	while(q--){
		char op;
		ll x;
		cin>>op>>x;
		ll k=__lg(x);

		if(op=='+'){
			bag[k].insert(x);
			sum[k]+=x;
			cnt++;
		}else{
			bag[k].erase(bag[k].find(x));
			sum[k]-=x;
			cnt--;
		}

		ll pre=0,cut=0;
		for(ll i=0;i<30;i++){
			if(!bag[i].empty()&&*bag[i].begin()>2*pre)
				cut++;
			pre+=sum[i];
		}

		cout<<cnt-cut<<'\n';
	}
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
