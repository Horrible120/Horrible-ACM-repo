#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void H_manacher(string &s,vector<array<ll,3>> &d){
	ll n=s.size();
	
	ll l=0,r=-1;
	for(ll i=0;i<n;i++){
		ll &k=d[i][1];
		if(i>r)
			k=1;
		else
			k=min(d[l+r-i][1],r-i+1);
		while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])
			k++;
		if(i+k>r){
			l=i-k+1;
			r=i+k-1;
		}
	}
	
	l=0,r=-1;
	for(ll i=0;i<n;i++){
		ll &k=d[i][2];
		if(i>r)
			k=0;
		else
			k=min(d[l+r-i+1][2],r-i+1);
		while(i-k-1>=0&&i+k<n&&s[i-k-1]==s[i+k])
			k++;
		if(i+k>r){
			l=i-k;
			r=i+k-1;
		}
	}
}

void solve(){
	ll n,q;
	cin>>n>>q;
	string s;
	cin>>s;
	
	vector<array<ll,3>> d(n+1);
	vector<ll> lst0(n+1,-1),lst1(n+1,-1),lst2(n+1,-1),ls0(27,-1),ls1(27,-1),ls2(27,-1);
	H_manacher(s,d);
	for(ll i=0;i<n;i++){
		ll c=s[i]-'a'+1;
		for(ll j=1;j<=26;j++)if(j!=c){
			lst0[i]=max(lst0[i],ls0[j]);
			lst1[i]=max(lst1[i],ls1[j]);
			lst2[i]=max(lst2[i],ls2[j]);
		}
		
//		cout<<"!!! "<<i<<' '<<lst0[i]<<endl;
		
		ls0[c]=i;
		if(i&1) ls1[c]=i;
		else ls2[c]=i;
	}
	
	auto f=[](ll len,ll k){
		if(k==1)
			return (len+1)/2*2*((len+1)/2)/2-1;
		else
			return (len/2)*(len/2+1);
	};
	
	while(q--){
		ll l,r;
		cin>>l>>r;
		l--,r--;
		ll ans=0;
		if(r&1){
			if(lst1[r]>=l||(r>0&&lst2[r-1]>=l))
				ans+=f(r-l,1);
//			OOO
//			cout<<ans<<endl;
			if(lst0[r]>=l)
				ans+=f(r-l,2);
		}
		else{
			if((r>0&&lst1[r-1]>=l)||lst2[r]>=l)
				ans+=f(r-l,1);
//			OOO
//			cout<<ans<<endl;
			if(lst0[r]>=l)
				ans+=f(r-l,2);
		}
//		OOO
//		cout<<ans<<endl;
		if((l+r)%2==0){
			if(2*d[(l+r)/2][1]-1<r-l+1)
				ans+=r-l+1;
		}
		else{
			if(2*d[(l+r+1)/2][2]<r-l+1)
				ans+=r-l+1;
		}
//		OOO
		cout<<ans<<endl;
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
