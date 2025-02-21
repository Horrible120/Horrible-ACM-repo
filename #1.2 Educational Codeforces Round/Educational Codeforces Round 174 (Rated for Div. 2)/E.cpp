#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	string s;
	cin>>s;
	ll n=s.size();
	vector<ll> AB,BA,ABA,BAB;
	ll a,b,ab,ba;
	cin>>a>>b>>ab>>ba;
 	for(ll i=0;i<n;i++){
		ll tmp=i;
		while(tmp<n-1&&s[tmp+1]!=s[tmp]) tmp++;
		if(tmp-i+1&1){
			if(s[i]=='A')
				ABA.emplace_back(tmp-i+1);
			else
				BAB.emplace_back(tmp-i+1);
		}
		else{
			if(s[i]=='A')
				AB.emplace_back(tmp-i+1);
			else
				BA.emplace_back(tmp-i+1);
		}
		i=tmp;
	}
	sort(AB.begin(),AB.end());
	sort(BA.begin(),BA.end());
	for(auto &it:BA){
		ll tmp=min(ba,it/2);
		it-=tmp*2;
		ba-=tmp;
		if(!ba&&ab&&it){
			tmp=min(ab,it/2-1);
			it-=tmp*2;
			ab-=tmp;
		}
		if(it){
			a-=it/2;
			b-=it/2;
			it=0;
		}
	}
	for(auto &it:AB){
		ll tmp=min(ab,it/2);
		it-=tmp*2;
		ab-=tmp;
		if(!ab&&ba&&it){
			tmp=min(ba,it/2-1);
			it-=tmp*2;
			ba-=tmp;
		}
		if(it){
			a-=it/2;
			b-=it/2;
			it=0;
		}
	}
	ll tot=ba+ab;
	for(auto &it:ABA){
		ll tmp=min(tot,it/2);
		it-=tmp*2;
		tot-=tmp;
		if(it){
			a-=it/2+1;
			b-=it/2;
			it=0;
		}
	}
	for(auto &it:BAB){
		ll tmp=min(tot,it/2);
		it-=tmp*2;
		tot-=tmp;
		if(it){
			a-=it/2;
			b-=it/2+1;
			it=0;
		}
	}
//	cout<<a<<' '<<b<<' '<<tot<<endl;
	if(a>=0&&b>=0)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
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
