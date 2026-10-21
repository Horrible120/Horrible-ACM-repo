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

vector<vector<ll>> mul(const vector<vector<ll>>& a,const vector<vector<ll>>& b,ll mod){
	ll n=a.size(),m=b[0].size(),len=b.size();
	vector<vector<ll>> res(n,vector<ll>(m));
	for(ll i=0;i<n;i++){
		for(ll j=0;j<m;j++){
			ll sum=0;
			for(ll k=0;k<len;k++)
				sum+=a[i][k]*b[k][j];
			res[i][j]=sum%mod;
		}
	}
	return res;
}

void solve(){
	ll k;
	cin>>k;
	ll len=k+1;
	vector<ll> rot(len+1),rev(len+1);
	for(ll i=1;i<=k;i++){
		string s;
		cin>>s;
		for(ll j=0;j<(ll)s.size();j++){
			if(s[j]=='a')
				rot[i]+=rev[i]?-1:1;
			else
				rev[i]^=1;
		}
	}

	ll n;
	string t;
	cin>>n>>t;
	ll mod=t.size();
	for(ll i=1;i<=k;i++)
		rot[i]=(rot[i]%mod+mod)%mod;
	for(ll i=k;i>=1;i--){
		ll sgn=rev[len]?-1:1;
		rot[len]=(rot[len]+sgn*rot[i]+mod)%mod;
		rev[len]^=rev[i];
	}

	ll cnt=(n-1)/len,pos=(n-1)%len;
	vector<vector<ll>> vec(len,vector<ll>(1));
	for(ll i=0;i<len;i++)
		vec[i][0]=rot[i+1];

	if(cnt){
		vector<vector<ll>> coef(2*len+1,vector<ll>(len));
		for(ll i=1;i<=len;i++)
			coef[i][i-1]=1%mod;
		for(ll i=len+1;i<=2*len;i++){
			ll par=0;
			for(ll j=1;j<=k;j++){
				ll sgn=par?-1:1;
				for(ll u=0;u<len;u++)
					coef[i][u]=(coef[i][u]+sgn*coef[i-j][u]+mod)%mod;
				par^=rev[(i-j-1)%len+1];
			}
		}

		vector<vector<ll>> mat(len,vector<ll>(len));
		for(ll i=0;i<len;i++)
			mat[i]=coef[len+i+1];
		while(cnt){
			if(cnt&1)
				vec=mul(mat,vec,mod);
			mat=mul(mat,mat,mod);
			cnt>>=1;
		}
	}

	rotate(t.begin(),t.begin()+vec[pos][0],t.end());
	if(rev[pos+1])
		reverse(t.begin(),t.end());
	cout<<t<<'\n';
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
