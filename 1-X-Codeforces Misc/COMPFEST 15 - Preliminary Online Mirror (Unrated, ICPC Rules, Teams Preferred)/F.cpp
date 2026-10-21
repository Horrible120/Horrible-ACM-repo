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
	
	vector<vector<ll>> eg(n+1,vector<ll>());
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	if(n==2){
		cout<<1<<' '<<2<<endl;
		return;
	}
	
	ll tot=0;
	vector<vector<ll>> tr(1,vector<ll>());
	vector<ll> id_L(21,0),id_R(21,0),siz(1,0);
	
	{
		vector<ll> tmp;
		
		ll csiz=0;
		
		auto DFS1=[&](this auto &&self,ll tar_siz,ll pre_siz,ll pre_id)->void{
			if(tar_siz==1){
				++tot;
				tr.emplace_back(tmp);
				siz.emplace_back(csiz);
				return;
			}
//			cout<<tar_siz<<' '<<pre_siz<<' '<<pre_id<<endl;
			for(ll nxt_siz=pre_siz;nxt_siz<tar_siz;nxt_siz++){
				for(ll id=max(pre_id,id_L[nxt_siz]);id<=id_R[nxt_siz];id++){
					tmp.emplace_back(id);
					self(tar_siz-nxt_siz,nxt_siz,id);
					tmp.pop_back();
				}
			}
		};
		
		tr.emplace_back();
		siz.emplace_back(1);
		++tot;
		id_L[1]=id_R[1]=1;
		
		for(csiz=2;tot<=n;csiz++){
			id_L[csiz]=tot+1;
			DFS1(csiz,1,1);
			id_R[csiz]=tot;
		}
	}
	
//	OOO
	
	map<vector<ll>,ll> iid;
	for(ll i=1;i<=tot;i++){
		iid[tr[i]]=i;
	}
	
	ll ans_id=-1;
	
	vector<ll> vis(n+1,0),Gid(n+1,0),visid(tot+1,0);

	auto DFS2=[&](this auto &&self,ll u)->void{
		vis[u]=1;
		vector<ll> tmp;
		for(auto v:eg[u])if(!vis[v]){
			self(v);
			tmp.emplace_back(Gid[v]);
		}
		sort(tmp.begin(),tmp.end());
		Gid[u]=iid[tmp];
		visid[Gid[u]]=1;
	};
	
	DFS2(1);
	
	for(ll i=1;i<=tot;i++){
		if(!visid[i]){
			ans_id=i;
			break;
		}
	}
	
	ll ans_tot=n-siz[ans_id]+1;
	
//	cout<<ans_id<<endl;
	
	vector<array<ll,2>> ans;
	
	for(ll i=1;i<ans_tot;i++){
		ans.emplace_back(array<ll,2>{{i,i+1}});
	}
	
	auto DFS3=[&](this auto &&self,ll cur_id,ll u)->void{
		for(auto v_id:tr[cur_id]){
			ans.emplace_back(array<ll,2>{{u,++ans_tot}});
			self(v_id,ans_tot);
		}
	};
	
	DFS3(ans_id,ans_tot);
	
	for(auto [u,v]:ans){
		cout<<u<<' '<<v<<"\n";
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
