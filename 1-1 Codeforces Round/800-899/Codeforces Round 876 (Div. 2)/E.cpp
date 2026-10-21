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
	ll n,sum=0;
	cin>>n;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		sum+=v[i];
	}
	
	vector<ll> cnt(100001,0);
	cnt[0]=1;
	
	for(ll i=1;i<=n;i++){
		for(ll j=n*300;j>=v[i];j--){
			if((!cnt[j])&&cnt[j-v[i]]){
				cnt[j]=i;
			}
		}
	}
	
	if(sum%2==0&&cnt[sum/2]){
		cout<<"Second"<<endl;
		ll cur=sum/2;
		
		set<ll> s[2];
		
		while(cur>0){
			s[0].insert(cnt[cur]);
			cur-=v[cnt[cur]];
		}
		
		for(ll i=1;i<=n;i++){
			if(!s[0].count(i)){
				s[1].insert(i);
			}
		}
		
		ll u;
		cin>>u;
		while(u>0){
			if(s[0].count(u)){
				cout<<*s[1].begin()<<endl;
				ll tmp=min(v[u],v[*s[1].begin()]);
				if((v[*s[1].begin()]-=tmp)==0) s[1].erase(s[1].begin());
				if((v[u]-=tmp)==0) s[0].erase(u);
			}else{
				cout<<*s[0].begin()<<endl;
				ll tmp=min(v[u],v[*s[0].begin()]);
				if((v[*s[0].begin()]-=tmp)==0) s[0].erase(s[0].begin());
				if((v[u]-=tmp)==0) s[1].erase(u);
			}
			cin>>u;
		}
		
	}else{
		cout<<"First"<<endl;
		set<ll> s;
		for(ll i=1;i<=n;i++){
			s.insert(i);
		}
		ll u;
		cout<<*s.begin()<<endl;
		cin>>u;
		while(u>0){
			ll tmp=min(v[u],v[*s.begin()]);
			if((v[*s.begin()]-=tmp)==0) s.erase(s.begin());
			if((v[u]-=tmp)==0) s.erase(u);
			cout<<*s.begin()<<endl;
			cin>>u;
		}
	}
	
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
