#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,sum=0,ans=INF;
	cin>>n;
	vector<ll> v(n+1,0),bonus(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		sum+=v[i];
	}
	
	{
		set<array<ll,4>> st;
		ll cnt=0;	//当前的总贡献
		for(ll i=n;i>=1;i--){
			array<ll,4> a_block={i,i,v[i],v[i]};	//当前怪物所在的梯形块 {左端点,右端点,最高伤害,最低伤害}
			while(st.size()){
//				OOO
				auto tmp=st.lower_bound(a_block);
				if(tmp==st.end()){	//后面没有块了 -> 退出
					break;
				}else if((*tmp)[2]<a_block[3]){	//后面块的最高伤害比当前最低伤害低 -> 后面不发生修改 -> 退出
					break;
				}else{	//后面需要修改 并且和当前块合并
					auto b_block=*tmp;
					st.erase(tmp);	//删除块
					cnt-=(b_block[2]+b_block[3])*(b_block[1]-b_block[0]+1)/2;	//撤销贡献
					a_block[1]=min(b_block[1],a_block[0]+a_block[2]-1);	//计算新的右端点,注意保持块内均有贡献,也就是伤害都为正
					a_block[3]=a_block[2]+(a_block[0]-a_block[1]);	//计算新的最低伤害
				}
			}
//			cout<<"!!! "<<i<<' '<<a_block[0]<<' '<<a_block[1]<<' '<<a_block[2]<<' '<<a_block[3]<<endl;
			cnt+=(a_block[2]+a_block[3])*(a_block[1]-a_block[0]+1)/2;	//累加上这一块的贡献
			st.insert(a_block);	//加入这一块
			bonus[i]+=cnt-v[i];	//加到 在这个怪处施放魔法的总贡献 上 , 减去 v[i] 为了平衡释放爆炸消耗的 v[i] 点 MP
		}
	}
	
//	for(ll i=1;i<=n;i++){
//		cout<<i<<' '<<bonus[i]<<endl;
//	}
	
	{
		set<array<ll,4>,greater<array<ll,4>>> st;
		ll cnt=0;
		for(ll i=1;i<=n;i++){
			array<ll,4> a_block={i,i,v[i],v[i]};
			while(st.size()){
//				OOO
				auto tmp=st.lower_bound(a_block);
				if(tmp==st.end()){
					break;
				}else if((*tmp)[2]<a_block[3]){
					break;
				}else{
					auto b_block=*tmp;
					st.erase(tmp);
					cnt-=(b_block[2]+b_block[3])*(b_block[1]-b_block[0]+1)/2;
					a_block[0]=max(b_block[0],a_block[1]-a_block[2]+1);
					a_block[3]=a_block[2]+(a_block[0]-a_block[1]);
				}
			}
//			cout<<"!!! "<<i<<' '<<a_block[0]<<' '<<a_block[1]<<' '<<a_block[2]<<' '<<a_block[3]<<endl;
			cnt+=(a_block[2]+a_block[3])*(a_block[1]-a_block[0]+1)/2;
			st.insert(a_block);
			bonus[i]+=cnt-v[i];
		}
	}
	
//	cout<<endl;
//	for(ll i=1;i<=n;i++){
//		cout<<i<<' '<<bonus[i]<<endl;
//	}
	
	for(ll i=1;i<=n;i++){
		ans=min(ans,sum-bonus[i]);
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
