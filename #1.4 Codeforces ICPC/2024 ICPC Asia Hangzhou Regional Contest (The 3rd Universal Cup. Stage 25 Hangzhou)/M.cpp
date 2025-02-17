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
	ll n,k,mg=0,mn=INF,flag=1;	//mg-全局差分数组gcd  mn-全局最小值  flag-是否需要特判
	cin>>n>>k;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(i>1&&v[i]!=v[i-1]) flag=0;
		mn=min(mn,v[i]);
	}
	
	if(flag){	//特判 输出 1 到 k 求和
		cout<<k<<' '<<k*(k+1)/2<<endl;
		return;
	}
	
	vector<ll> ls(n+1),rs(n+1);	//笛卡尔树-左右儿子
	v2ct<ll> g(22,vector<ll>(n+1,0));	//差分数组+ST表
	
	for(ll i=2;i<=n;i++){	//初始化ST表第一层 + 求全局差分数组gcd
		g[0][i]=abs(v[i]-v[i-1]);
		mg=__gcd(mg,abs(v[i]-v[i-1]));
		
	}
	for(ll i=1;i<=20;i++)	//构建ST表
		for(ll j=1;j<=n;j++)
			g[i][j]=__gcd(g[i-1][j],g[i-1][min(n,j+(1<<(i-1)))]);
	
	function<ll(ll,ll)> Gcd = [&](ll l,ll r){	//查询区间差分数组的gcd
		ll res=0,_lg=abs(__lg(r-l));
		if(l<r) res=__gcd(g[_lg][l+1],g[_lg][r-(1<<_lg)+1]);
		return res;
	};
	
	vector<ll> ans;
	for(ll i=1;i*i<=mg;i++)	//生成最初的答案序列
		if(mg%i==0){
			if(i>=mn+1&&i<=mn+k)
				ans.emplace_back(i-mn);
			if(mg!=i*i&&mg/i>=mn+1&&mg/i<=mn+k)
				ans.emplace_back(mg/i-mn);
		}
	
	stack<ll> stk;
	for(ll i=1;i<=n;i++){	//笛卡尔树建树
		ll tmp=stk.size(),lst=0;
		while(stk.size()&&v[stk.top()]>v[i]) lst=stk.top(),stk.pop();
		if(stk.size()) rs[stk.top()]=i;
		if(stk.size()<tmp) ls[i]=lst;
		stk.push(i);
	}
	
	function<void(ll,ll,ll)> DFS = [&](ll x,ll l,ll r){	//逐层检验 （当前最小值下标，左端点，右端点）
		if(l==r) return;
		ll rgcd=Gcd(l,r);	//区间差分数组gcd
		
		for(ll i=0;i<ans.size();i++)
			if(ans[i]&&rgcd%(ans[i]+v[x])!=0)	//被排除的答案设为 0 （这一步可以用链表进一步优化时间，但是懒得改了）
				ans[i]=0;
		
		if(ls[x])
			DFS(ls[x],l,x-1);
		if(rs[x])
			DFS(rs[x],x+1,r);
	};
	
	vector<ll> vis(n+1);
	ll rt;	//笛卡尔树的树根
	for(ll i=1;i<=n;i++){
		vis[ls[i]]=1;
		vis[rs[i]]=1;
	}
	for(ll i=1;i<=n;i++) if(!vis[i]) rt=i;	//没有被访问到的就是树根
	
	DFS(rt,1,n);	//开始筛选答案
	ll cnt=0,sum=0;
	for(ll i=0;i<ans.size();i++){	//计数 & 求和
		if(ans[i]){
			cnt++;
			sum+=ans[i];
		}
	}
//	OOO
	cout<<cnt<<' '<<sum<<endl;
	
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
