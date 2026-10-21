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
	ll n,q;
	cin>>n>>q;
	vector<ll> v(2*n,0);
	for(ll i=0;i<n;i++){
		cin>>v[i];
		v[n+i]=v[i];
	}
	
	vector<ll> que(q+1,0),rnk(q+1,0);
	for(ll i=1;i<=q;i++){
		cin>>que[i];
		rnk[i]=i;
	}
	
	sort(rnk.begin()+1,rnk.end(),[&](const ll a,const ll b){return que[a]>que[b];});
	
	
	
	vector<vector<ll>> st(2*n+1,vector<ll>(21,0));
	
	for(ll i=0;i<2*n;i++) st[i][0]=v[i];
	
	for(ll i=1;i<=20;i++){
		for(ll j=0;j<2*n;j++){
			st[j][i]=st[j][i-1]|st[min(2*n-1,j+(1<<i-1))][i-1];
		}
	}

	vector<pair<ll,ll>> val; 
	
	auto cal=[&](ll l,ll r)->ll{
		ll g=__lg(r-l+1);
		return st[l][g]|st[r-(1<<g)+1][g];
	};
	
	for(ll i=0;i<n;i++){
		ll tmp=0,cur=i;
		while(cur<i+n){
			ll l=cur,r=i+n-1;
			while(l<r){
				ll mid=l+r>>1;
				if(cal(i,mid)^tmp){
					r=mid;
				}else{
					l=mid+1;
				}
			}
			if(cal(i,l)^tmp){
				if(l%n==0&&i!=0){
					if(l+1<i+n) ++l;
					else break;
				}
				tmp=cal(i,l);
				val.emplace_back(make_pair(tmp,(i%n>l%n?(l-i-1ll)*n+i+1:(l-i)*n+i+1)));
//				cout<<">>> "<<i<<' '<<l<<' '<<tmp<<' '<<(i%n>l%n?(l-i-1ll)*n+i+1:(l-i)*n+i+1)<<endl;
				cur=l+1;
			}else{
				break;
			}
		}
	}
	
	sort(val.begin(),val.end(),less());
	
	ll siz=val.size();
	ll top=siz-1,mrnk=INF;
	
	vector<ll> ans(q+1,0);
	
//	cout<<"!!! "<<top<<' '<<val[top].first<<endl;
	
	for(ll i=1;i<=q;i++){
		while(top>=0&&val[top].first>que[rnk[i]]){
			mrnk=min(mrnk,val[top].second);
			top--;
		}
		if(top==siz-1){
			ans[rnk[i]]=-1;
		}else{
			ans[rnk[i]]=mrnk;
		}
	}
	
//	for(ll i=1;i<=q;i++) cout<<rnk[i]<<' ';
//	cout<<endl;
	
//	cout<<">>>"<<endl;
	for(ll i=1;i<=q;i++){
		cout<<ans[i]<<" \n"[i==q];
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测 试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
