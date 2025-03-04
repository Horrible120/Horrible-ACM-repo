#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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
	ll n,ans=INF;
	cin>>n;
	vector<ll> v((1<<n)+1),vs((1<<n)+1),u((1<<(n+1))+1),l((1<<(n+1))+1),r((1<<(n+1))+1);
	//	叶子节点的值，是否被屏蔽，树枝权值，管辖左端点，右端点
	for(ll i=1;i<=(1<<(n+1))-2;i++) cin>>u[i];
	
	function<void(ll,ll)> DFS=[&](ll cur,ll cnt){//当前从后往前检查到第cur个结点，此前已经操作了cnt次
		if(cnt>n-__lg(cur)) return;
		ll flag=1;
		while(cur>0&&flag){	//找第一个有重复的节点
			unordered_map<ll,ll> tmp;
			for(ll i=l[cur];i<=r[cur];i++)
				if(!vs[i]){
					tmp[v[i]]++;
					if(tmp[v[i]]>1) flag=0;
				}
			if(flag) cur--;
		}
		if(cur==0||flag) ans=min(ans,cnt);	//如果没有重复了 更新答案
		else{								//否则枚举左右
			for(ll i=l[cur*2];i<=r[cur*2];i++) vs[i]++;
			DFS(cur,cnt+1);
			for(ll i=l[cur*2];i<=r[cur*2];i++) vs[i]--;
			
			for(ll i=l[cur*2+1];i<=r[cur*2+1];i++) vs[i]++;
			DFS(cur,cnt+1);
			for(ll i=l[cur*2+1];i<=r[cur*2+1];i++) vs[i]--;
		}
	};
	
	for(ll i=(1<<(n+1))-1;i>=1;i--){	//处理出v[]
		ll c=__lg(i),p=i-(1<<c);
		l[i]=p*(1<<(n-c))+1;r[i]=(p+1)*(1<<(n-c));
		for(ll j=p*(1<<(n-c))+1;j<=(p+1)*(1<<(n-c));j++)
			v[j]+=u[i-1];
	}
	DFS((1<<n)-1,0);
	cout<<(ans<=n?ans:-1)<<endl;
	
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
