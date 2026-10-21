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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++){
		string op;
		cin>>op;
		
		if(op[0]=='F'){
			ll x;
			cin>>x;
			v[i]=x;
		}
	}
	
	ll pft=0,ans=0,tot=0;
	ll cntf=0,cntw=0,curw=0;
	
	oset<pair<ll,ll>,greater<pair<ll,ll>>> os;
	
	for(ll i=1;i<=n;i++){
		if(!v[i]){
			cntw++;
			if(i==n||v[i+1]==0){
				if(curw<cntf&&curw<cntw){
					pft+=(*os.find_by_order(curw)).first;
					curw++;
				}
				
//				cout<<">>> "<<curw<<' '<<pft<<endl;
				
				ans+=pft;
			}else{
				if(curw<cntf&&curw<cntw){
					pft+=(*os.find_by_order(curw)).first;
					curw++;
				}
				
				ll tmp=i+1;
				while(tmp<n&&v[tmp+1]) ++tmp;
				multiset<ll,greater<ll>> st;
				for(ll j=i+1;j<=tmp;j++) st.insert(v[j]*(tmp-j+1));
				
				ans+=pft*(tmp-i+1);
				ll tmpcur=curw;
				
				for(ll i=1;i<=cntw-curw;i++){
					if(st.size()){
						ans+=*st.begin();
						st.erase(st.begin());
					}
				}
				
				while(tmpcur>0&&st.size()){
					ll cc=(*os.find_by_order(tmpcur-1)).first;
					if(cc*(tmp-i+1)<(*st.begin())){
						ans+=(*st.begin())-cc*(tmp-i+1);
						st.erase(st.begin());
						tmpcur--;
					}else break;
				}
				
				for(ll j=i+1;j<=tmp;j++){
					if(curw<cntf&&curw<cntw){
						pft+=(*os.find_by_order(curw)).first;
						curw++;
					}else if(curw>0){
						ll cc=(*os.find_by_order(curw-1)).first;
						if(v[j]>cc){
							pft+=v[j]-cc;
						}
					}
					
					os.insert(make_pair(v[j],++tot));
					++cntf;
				}
				
				i=tmp;
			}
		}else{
			os.insert(make_pair(v[i],++tot));
			cntf++;
		}
//		cout<<i<<' '<<ans<<' '<<pft<<' '<<cntf<<' '<<cntw<<' '<<curw<<endl;
	}
	
	cout<<ans<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
