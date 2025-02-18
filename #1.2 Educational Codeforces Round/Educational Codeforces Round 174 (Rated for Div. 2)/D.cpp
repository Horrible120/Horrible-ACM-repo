#include <bits/stdc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;


const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,st=1,ans=INF;
	string s;
	cin>>s;
	n=s.size();
	vector<ll> v(n+2),cnt(30),ccnt(30);
	
	for(ll i=1;i<=n;i++)
		v[i]=s[i-1]-'a'+1;
	
	for(ll i=1;i<=n/2;i++)
		if(v[i]==v[n-i+1]) st=i+1;
		else break;
	
//	cout<<st<<endl;
	
	if(st>n/2){
		cout<<0<<endl;
		return;
	}
	
	for(ll i=st;i<=n/2;i++){
		cnt[v[i]]++;
		cnt[v[n-i+1]]--;
	}
	
	ll flag=0;
	for(ll j=1;j<=26;j++)
		if(cnt[j]) flag=1;
	if(!flag) ans=n/2-st+1;
	
	for(ll i=n/2;i>=st;i--){
		if(v[i]==v[n-i+1]){
			ll flag=0;
			for(ll j=1;j<=26;j++)
				if(cnt[j]) flag=1;
			if(flag) break;
			else ans=i-st;
		}
		else break;
	}
//	cout<<"!!! "<<ans<<endl;
	for(ll i=st;i<=n-st+1;i++)
		ccnt[v[i]]++;
	
	if(1){
		vector<ll> tmp1(30,0);
		for(ll i=st;i<=n-st+1;i++){
			tmp1[v[i]]++;
//			cout<<"!!!"<<i<<' '<<n<<endl;
			if(i>(n/2)){
				ll c=0;
				for(ll j=1;j<=26;j++)
					c+=max(0ll,tmp1[j]-(ccnt[j]/2));
//				cout<<c<<endl;
				if(c<=i-n/2){
//					cout<<"YES"<<i-st+1<<endl;
					ans=min(ans,i-st+1);
					break;
				}	
			}
		}
//		cout<<"!!! "<<ans<<endl;
		vector<ll> tmp2(30,0);
		for(ll i=n-st+1;i>=st;i--){
			tmp2[v[i]]++;
			if(i<=n/2){
				ll c=0;
				for(ll j=1;j<=26;j++)
					c+=max(0ll,tmp2[j]-(ccnt[j]/2));
//				cout<<endl;
//				cout<<c<<endl;
				if(c<=n/2+1-i){
//					cout<<"YES"<<n-st+1-i+1<<endl;
					ans=min(ans,n-st+1-i+1);
					break;
				}
			}
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
