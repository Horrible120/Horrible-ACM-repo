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

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		string s;
		ll sum=0,flag=1;
		cin>>s;
		vector<ll> v(s.size()+1);
		for(ll i=0;i<s.size();i++)
			v[i+1]=s[i]-'0',sum+=v[i+1];
		sum=sum%9;
		ll cnt[5]={};
		for(ll i=1;i<=s.size();i++){
			if(v[i]>3||v[i]<2) continue;
			cnt[v[i]]++;
		}
//		cout<<"!!"<<sum<<endl;
		if(sum%3){
			if(cnt[2]<sum%3)
				flag=0;
			else{
				cnt[2]-=sum%3;
				sum=(sum+(sum%3)*2)%9;
			}
		}
		cnt[3]+=cnt[2]/3;
//		cout<<"!!"<<sum<<endl;
		if(sum%3==0) sum/=3;
		
		if(sum%3){
			if(cnt[3]<sum%3)
				flag=0;
		}
			
//		OOO
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	
	cout.flush();
	
	return 0;
}
