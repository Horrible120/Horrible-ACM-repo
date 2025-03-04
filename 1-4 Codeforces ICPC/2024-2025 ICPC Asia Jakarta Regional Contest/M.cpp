#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	

	ll r,c,cnt=0;
	cin>>r>>c;
	vector<vector<ll>> mr(r+1,vector<ll>(c+1));
	
	string s;
	for(ll i=1;i<=r;i++){
		cin>>s;
		for(ll j=0;j<c;j++){
			if(s[j]=='/') mr[i][j+1]=1;
			else if(s[j]=='\\') mr[i][j+1]=2;
			if(s[j]!='.') cnt++;
		}
	}
	
	ll mv[5][2]={{0,0},{-1,0},{1,0},{0,-1},{0,1}};	//上 下 左 右
	
	ll vis[210][210]={};
	
	vector<pair<ll,ll>> ans;
	
	function<void(ll&,ll&,ll&,ll&)> change=[&](ll &x,ll &y,ll &k,ll &ct){
		if(mr[x][y]==1)
			k=5-k;
		else if(mr[x][y]==2)
			k=(k+1)%4+1;
		
		if(mr[x][y]&&(!vis[x][y])) ct++,vis[x][y]=1; 
		
		x+=mv[k][0];
		y+=mv[k][1];
	};
	
	function<void(ll,ll,ll,ll)> search=[&](ll x,ll y,ll k,ll ct){
		if(x<1||x>r||y<1||y>c){
			if(ct==cnt)
				ans.emplace_back(make_pair(x,y));
		}
		else{
			change(x,y,k,ct);
			search(x,y,k,ct);
		}
	};
	
	for(ll i=1;i<=r;i++){
		
		for(ll j=1;j<=r;j++)
			for(ll k=1;k<=c;k++)
				vis[j][k]=0;
		search(i,1,4,0);
		
		for(ll j=1;j<=r;j++)
			for(ll k=1;k<=c;k++)
				vis[j][k]=0;
		search(i,c,3,0);
	}
	
	for(ll i=1;i<=c;i++){
		
		for(ll j=1;j<=r;j++)
			for(ll k=1;k<=c;k++)
				vis[j][k]=0;
		search(1,i,2,0);
		
		for(ll j=1;j<=r;j++)
			for(ll k=1;k<=c;k++)
				vis[j][k]=0;
		search(r,i,1,0);
	}
	
	cout<<ans.size()<<endl;
	
	for(auto it:ans){
		auto [x,y]=it;
		if(x==0) cout<<'N'<<y<<' ';
		if(y==0) cout<<'W'<<x<<' ';
		if(x>r) cout<<'S'<<y<<' ';
		if(y>c) cout<<'E'<<x<<' ';
//		cout<<x<<' '<<y<<endl;
	}
	
	cout<<endl;
	
	cout.flush();
	
	return 0;
}
