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
vector<ll> Z_Algo(string &s){
	vector<ll> z(s.size());
	for(ll i=1,l=0,r=0;i<s.size();i++){
		if(r>=i&&z[i-l]<r-i+1)
			z[i]=z[i-l];
		else{
			z[i]=max(0LL,r-i+1);
			while(i+z[i]<s.size()&&s[z[i]]==s[i+z[i]])
				++z[i];
		}
		if(i+z[i]-1>r)
			l=i,r=i+z[i]-1;
	}
	return z;
}

void solve(){
	string s,t;
	ll ans=0;
	cin>>s>>t;
	string st=s+t;
	ll ls=s.size();
	ll lt=t.size();
	ll len=st.size();
	
	vector<ll> z(len+1,0);
	
	for(ll i=0;i<ls;i++){
		ll l=i,r=i;
		for(ll j=0;j<=len;j++)
			z[j]=0;
		for(ll d=i,l=i,r=i;d<len;d++){
			if(r>=d&&z[d-l+i]<r-d+1)
				z[d]=z[d-l+i];
			else{
				z[d]=max(0ll,r-d+1);
				while(d+z[d]<st.size()&&st[d+z[d]]==st[z[d]+i])
					++z[d];
			}
			if(d+z[d]-1>r)
				l=d,r=d+z[d]-1;
		}
		
		for(ll j=0;j<len;j++)
			cout<<z[j]<<' ';
		cout<<endl;
		
		for(ll j=ls;j<len;j++)
			ans+=z[j];
	}
	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
