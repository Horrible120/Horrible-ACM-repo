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

void solve(){
	string s;
	cin>>s;
	ll n=s.size();
	vector<char> ch;
	vector<ll> pra;
	
	ll cnt=0;
	for(ll i=0;i<n;i++){
		if(s[i]!='a'){
			ch.emplace_back(s[i]);
			pra.emplace_back(cnt);
		} 
		else cnt++;
	}
	
	if(cnt==n){
		cout<<n-1<<endl;
		return;
	}
	
	ll la=pra[0],ra=n-ch.size()-pra.back();
	
//	cout<<la<<' '<<ra<<endl;
	
	ll ans=0,m=ch.size();
	for(ll i=1;i<=m;i++){
		if(m%i==0){	//字符串 t 的原形当中含有 i 个非 a 字符
			ll flag=1,gap=INF;
			
			for(ll cur=i;cur<m&&flag;cur++){
				if(ch[cur]!=ch[cur%i]||(cur%i>0&&pra[cur]-pra[cur-1]!=pra[cur%i]-pra[cur%i-1])) flag=0;
				if(cur%i==0) gap=min(gap,pra[cur]-pra[cur-1]);
			}
			if(!flag) continue;
			for(ll i=0;i<=la;i++)
				ans+=max(min(gap-i,ra)+1,0ll);
//			cout<<"!!"<<i<<' '<<ans<<endl;
		}
	}
//	OOO
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
