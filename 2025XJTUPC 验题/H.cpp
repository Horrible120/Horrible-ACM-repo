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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll tar=0;
	
	for(ll i=0;i<6;i++){
		string s;
		cin>>s;
		for(ll j=0;j<3;j++)
			tar+=(s[j]-'0')<<(i*3+j);
	}
	
//	cout<<tar<<endl;
	
	if(tar==0b000000000111111111){
		cout<<0<<endl;
		return;
	}
	
	vector<ll> l1_turn={2,5,8,1,4,7,0,3,6,9,10,11,12,13,14,15,16,17};
	vector<ll> r1_turn={6,3,0,7,4,1,8,5,2,9,10,11,12,13,14,15,16,17};
	vector<ll> l2_turn={0,1,2,3,4,5,6,7,8,11,14,17,10,13,16,9,12,15};
	vector<ll> r2_turn={0,1,2,3,4,5,6,7,8,15,12,9,16,13,10,17,14,11};
	
	vector<ll> c1={9,1,2,12,4,5,15,7,8,0,10,11,3,13,14,6,16,17};
	vector<ll> c2={0,10,2,3,13,5,6,16,8,9,1,11,12,4,14,15,7,17};
	vector<ll> c3={0,1,11,3,4,14,6,7,17,9,10,2,12,13,5,15,16,8};
 	
	vector<ll> vis((1<<18)+1,0),op((1<<18)+1,0),pre((1<<18)+1,0),ans;
	
	queue<ll> que;
	que.push(tar);
	vis[tar]=1;
	
	while(que.size()){
		auto cur=que.front();
		que.pop();
		{
			ll nxt=0;
			for(ll i=0;i<18;i++)
				nxt+=((cur>>l1_turn[i])&1)<<i;
			if(!vis[nxt]){
				que.push(nxt);
				op[nxt]=1;
				vis[nxt]=1;
				pre[nxt]=cur;
			}
		}
		
		{
			ll nxt=0;
			for(ll i=0;i<18;i++)
				nxt+=((cur>>r1_turn[i])&1)<<i;
			if(!vis[nxt]){
				que.push(nxt);
				op[nxt]=2;
				vis[nxt]=1;
				pre[nxt]=cur;
			}
		}
		
		{
			ll nxt=0;
			for(ll i=0;i<18;i++)
				nxt+=((cur>>l2_turn[i])&1)<<i;
			if(!vis[nxt]){
				que.push(nxt);
				op[nxt]=3;
				vis[nxt]=1;
				pre[nxt]=cur;
			}
		}
		
		{
			ll nxt=0;
			for(ll i=0;i<18;i++)
				nxt+=((cur>>r2_turn[i])&1)<<i;
			if(!vis[nxt]){
				que.push(nxt);
				op[nxt]=4;
				vis[nxt]=1;
				pre[nxt]=cur;
			}
		}
		
		{
			ll nxt=0;
			for(ll i=0;i<18;i++)
				nxt+=((cur>>c1[i])&1)<<i;
			if(!vis[nxt]){
				que.push(nxt);
				op[nxt]=5;
				vis[nxt]=1;
				pre[nxt]=cur;
			}
		}
		
		{
			ll nxt=0;
			for(ll i=0;i<18;i++)
				nxt+=((cur>>c2[i])&1)<<i;
			if(!vis[nxt]){
				que.push(nxt);
				op[nxt]=6;
				vis[nxt]=1;
				pre[nxt]=cur;
			}
		}
		
		{
			ll nxt=0;
			for(ll i=0;i<18;i++)
				nxt+=((cur>>c3[i])&1)<<i;
			if(!vis[nxt]){
				que.push(nxt);
				op[nxt]=7;
				vis[nxt]=1;
				pre[nxt]=cur;
			}
		}
	}
	
	ll st=0b111111111000000000;
	
	while(st!=tar){
//		OOO
//		cout<<endl;
		
		ans.emplace_back(op[st]);
		st=pre[st];
	}
	
	cout<<ans.size()<<endl;
	
	reverse(ans.begin(),ans.end());
	
	for(auto it:ans){
		string s;
		if(it==1)
			s="AL";
		if(it==2)
			s="AR";
		if(it==3)
			s="BL";
		if(it==4)
			s="BR";
		if(it==5)
			s="C1";
		if(it==6)
			s="C2";
		if(it==7)
			s="C3";
		cout<<s<<endl;
	}
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
