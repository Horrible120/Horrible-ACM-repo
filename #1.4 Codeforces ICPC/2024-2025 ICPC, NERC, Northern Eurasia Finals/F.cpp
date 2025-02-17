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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,q;
	cin>>n>>m>>q;
	vector<ll> l(m+1),tm(m+1),que(q+1);
	vector<pair<ll,ll>> task(n+1),leis;
	for(ll i=1;i<=n;i++)
		cin>>task[i].first;
	for(ll i=1;i<=n;i++)
		cin>>task[i].second;
	for(ll i=1;i<=m;i++)
		cin>>l[i];
	for(ll i=1;i<=q;i++)
		cin>>que[i];
	
	
	
	partial_sum(l.begin(),l.end(),tm.begin());
	sort(task.begin()+1,task.end(),[](pair<ll,ll> a,pair<ll,ll> b)->bool{return a.second>b.second;});
	
	ll lst=task[1].second;
	leis.emplace_back(make_pair(lst,INF));
	for(ll i=1;i<=n;i++){
		ll ddl=min(lst,task[i].second);
		
		if(ddl<lst) leis.emplace_back(make_pair(ddl,lst-ddl));
		
		lst=ddl-task[i].first;
	}
	leis.emplace_back(make_pair(0ll,lst));
	
	vector<ll> prels(leis.size());
	prels[leis.size()-1]=leis[leis.size()-1].second;
	for(ll i=leis.size()-2;i>=0;i--)
		prels[i]=prels[i+1]+leis[i].second;
	
//	OOO
//	for(ll i=0;i<prels.size();i++)
//	cout<<prels[i]<<' ';
//	cout<<endl;
	
//	OOO
//	for(ll i=1;i<=m;i++)
//		cout<<tm[i]<<' ';
//	cout<<endl;
////	cout<<upper_bound(tm.begin(),tm.end(),5)-tm.begin()<<endl;
//	
//	OOO
//	for(auto [x,y]:leis)
//		cout<<x<<'|'<<y<<' ';
//	cout<<endl;
	
	auto comp=[](const ll &x,const pair<ll,ll> &a)->bool{
		return a.first<x;
	};
//	cout<<">>>> ";
	for(ll i=1;i<=q;i++){
		auto it=upper_bound(leis.begin(),leis.end(),que[i],comp);
		ll pos=it-leis.begin();
		
		ll sum=prels[pos]-leis[pos].second+min(que[i]-leis[pos].first,leis[pos].second);
		
//		cout<<endl<<"!!"<<pos<<' '<<sum<<endl;
		
		auto ans=(upper_bound(tm.begin(),tm.end(),sum)-tm.begin())-1;
		cout<<ans<<' ';
	}
	cout<<endl;
	
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
