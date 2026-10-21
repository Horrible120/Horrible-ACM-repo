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
	string s;
	cin >> s;
	ll n=s.size();
	s=" "+s;

	ll ans=0;
	for(ll k=1;k<=9;k++){
		vector<ll> cnt(2),sum(2);
		cnt[1]=1;

		for(ll i=1;i<=n;i++){
			vector<ll> ncnt(2),nsum(2);
			ll cur=s[i]-'0';

			for(ll t=0;t<2;t++){
				ll up=t?cur:9;
				for(ll d=0;d<=up;d++){
					ll nt=t&&(d==cur);
					ncnt[nt]=(ncnt[nt]+cnt[t])%Mod;
					if(d<k)
						nsum[nt]=(nsum[nt]+sum[t])%Mod;
					else
						nsum[nt]=(nsum[nt]+10*sum[t]+cnt[t])%Mod;
				}
			}

			cnt=ncnt;
			sum=nsum;
		}

		ans=(ans+sum[0]+sum[1])%Mod;
	}

	cout << ans << '\n';
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
