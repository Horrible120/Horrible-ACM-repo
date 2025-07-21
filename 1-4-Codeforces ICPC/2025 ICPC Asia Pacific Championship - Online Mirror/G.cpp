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
	ll n,m;
	string s1,s2;
	cin>>n>>m;
	cin>>s1>>s2;
	vector<pair<ll,ll>> v1,v2;
	ll l1=0,r1=s1.size()-1;
	while(s1[l1]=='1') l1++;
	while(s1[r1]=='1') r1--;
	for(ll i=l1;i<=r1;i++){
		ll tmp=i;
		while(tmp+1<=r1&&s1[tmp+1]==s1[i])
			tmp++;
		v1.emplace_back(tmp-i+1,s1[i]-'0');
		i=tmp;
	};
	
	ll l2=0,r2=s2.size()-1;
	while(s2[l2]=='1') l2++;
	while(s2[r2]=='1') r2--;
	for(ll i=l2;i<=r2;i++){
		ll tmp=i;
		while(tmp+1<=r2&&s2[tmp+1]==s2[i])
			tmp++;
		v2.emplace_back(tmp-i+1,s2[i]-'0');
		i=tmp;
	};
	
//	OOO
	
	if(l2>l1||s2.size()-r2>s1.size()-r1){
		cout<<"no"<<endl;
		return;
	}
	
	if((v2.size()==0&&v1.size()!=0)||(v1.size()==0&&v2.size()!=0)){
		cout<<"no"<<endl;
		return;
	}
	
	ll p1=0;
	for(ll i=0;i<v2.size();i++){
		auto [len,col]=v2[i];
		if(col==0){
			ll sum0=0;
			while(p1<v1.size()){
				if(v1[p1].second==0)
					sum0+=v1[p1].first;
				if(sum0>=len)
					break;
				++p1;
			}
			if(sum0<len){
				cout<<"no"<<endl;
				return;
			}
		}
		else{
			while(p1<v1.size()){
				if(v1[p1].second==1&&v1[p1].first>=len)
					break;
				++p1;
			}
			if(p1==v1.size()){
				cout<<"no"<<endl;
				return;
			}
		}
	}

	cout<<"yes"<<endl;
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
