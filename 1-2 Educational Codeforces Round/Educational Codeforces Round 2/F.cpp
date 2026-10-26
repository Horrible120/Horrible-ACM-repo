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
	ll a,b,m;
	cin>>a>>b>>m;
	vector<ll> lef(m+1),rig(m+1),col(m+1),deg(a+b+1);
	ll lim=0;
	for(ll i=1;i<=m;i++){
		cin>>lef[i]>>rig[i];
		rig[i]+=a;
		lim=max(lim,++deg[lef[i]]);
		lim=max(lim,++deg[rig[i]]);
	}

	vector<vector<ll>> eid(a+b+1,vector<ll>(lim+1));
	vector<ll> path,ver;
	path.reserve(a+b);
	ver.reserve(a+b);
	for(ll i=1;i<=m;i++){
		ll u=lef[i],v=rig[i],ca=0,cb=0,clr=0;
		for(ll c=1;c<=lim;c++){
			if(!eid[u][c]&&!eid[v][c]){
				clr=c;
				break;
			}
			if(!eid[u][c]&&!ca)
				ca=c;
			if(!eid[v][c]&&!cb)
				cb=c;
		}

		if(!clr){
			path.clear();
			ver.clear();
			ll cur=u,now=cb,nxt=ca;
			ver.emplace_back(cur);
			while(eid[cur][now]){
				ll id=eid[cur][now];
				path.emplace_back(id);
				cur=(lef[id]==cur?rig[id]:lef[id]);
				ver.emplace_back(cur);
				swap(now,nxt);
			}

			for(ll j=0;j<(ll)ver.size();j++)
				swap(eid[ver[j]][ca],eid[ver[j]][cb]);
			for(ll j=0;j<(ll)path.size();j++){
				ll id=path[j];
				col[id]=(col[id]==ca?cb:ca);
			}
			clr=cb;
		}

		col[i]=clr;
		eid[u][clr]=eid[v][clr]=i;
	}

	cout<<lim<<'\n';
	for(ll i=1;i<=m;i++)
		cout<<col[i]<<' ';
	cout<<'\n';
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
