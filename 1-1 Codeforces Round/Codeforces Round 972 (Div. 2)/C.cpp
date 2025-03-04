#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){	//"narek"
	ll n,m;
	cin>>n>>m;
	vector<string> s(n+1);
	for(ll i=1;i<=n;i++) cin>>s[i];
	vector<ll> dp(5,-INF),tmp(5);
	string q="narek";
	/*map<char,ll> tab;
	tab['n']=0;
	tab['a']=1;
	tab['r']=2;
	tab['e']=3;
	tab['c']=4;*/
	dp[0]=0;
	for(ll i=1;i<=n;i++){
		tmp=dp;
		for(ll j=0;j<5;j++){
			ll cur=j;
			ll tp=dp[j];	//巧思：j是下一个要匹配的字符，有的时候为了方便更新和维护答案，我们就将dp数组的含义修改：
							//改变为“下一个要匹配第 i 个字符时的最高分数”，这样做比起修改维护策略要方便得多，也好理解得多
			for(ll k=0;k<m;k++) 
				if(s[i][k]==q[cur]){
					cur++;
					if(cur==5) cur=0,tp+=5;
				}else if(q.find(s[i][k])!=q.npos){
					tp--;
				}
//			cout<<"!!!"<<tp<<' '<<cur<<endl;
			tmp[cur]=max(tp,tmp[cur]);
		}
		dp=tmp;
	}
	ll ans=-INF;
//	OOO
	for(ll i=0;i<5;i++)
		ans=max(ans,dp[i]-i);
	cout<<ans<<endl;
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
