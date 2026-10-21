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
	vector<ll> pre(n+1),nxt(n+1);
	vector<vector<ll>> val(n+1,vector<ll>(n+1,-1));

	auto ask=[&](const vector<ll> &ord){
		cout<<'?';
		for(ll i=0;i<n;i++)
			cout<<' '<<ord[i];
		cout<<endl;

		string str;
		if(!(cin>>str)||str=="-1")
			exit(0);
		for(ll i=0;i<n-1;i++){
			ll u=ord[i],v=ord[i+1];
			val[u][v]=str[i]-'0';
			if(val[u][v]){
				nxt[u]=v;
				pre[v]=u;
			}
		}
		return str;
	};

	ll m=n-1-(n%2==0);
	vector<ll> base;
	for(ll i=0;i<m/2;i++){
		base.emplace_back(i);
		base.emplace_back(m-1-i);
	}
	for(ll k=0;k<m/2;k++){
		vector<ll> ord(m);
		for(ll i=0;i<m;i++)
			ord[i]=(base[i]+k)%m+1;
		for(ll dir=0;dir<2;dir++){
			vector<ll> qry;
			if(n%2==0)
				qry.emplace_back(n-1);
			for(ll i=0;i<m;i++)
				qry.emplace_back(ord[i]);
			qry.emplace_back(n);
			ask(qry);
			reverse(ord.begin(),ord.end());
		}
	}

	vector<vector<ll>> seg,cand;
	for(ll i=1;i<=n;i++)
		if(!pre[i]){
			vector<ll> cur;
			for(ll u=i;u;u=nxt[u])
				cur.emplace_back(u);
			seg.emplace_back(cur);
		}

	ll cnt=seg.size();
	vector<ll> per(cnt);
	iota(per.begin(),per.end(),0);
	do{
		vector<ll> ord;
		for(ll i=0;i<cnt;i++)
			for(ll j=0;j<(ll)seg[per[i]].size();j++)
				ord.emplace_back(seg[per[i]][j]);
		bool ok=1;
		for(ll i=0;i<n-1;i++)
			if(val[ord[i]][ord[i+1]]==0)
				ok=0;
		if(ok)
			cand.emplace_back(ord);
	}while(next_permutation(per.begin(),per.end()));

	ll tot=cand.size(),id=0;
	if(tot>1){
		string str=ask(cand[0]);
		for(ll k=0;k<tot;k++){
			vector<ll> pos(n+1);
			for(ll i=0;i<n;i++)
				pos[cand[k][i]]=i;
			bool ok=1;
			for(ll i=0;i<n-1;i++)
				if((pos[cand[0][i+1]]==pos[cand[0][i]]+1)!=(str[i]=='1'))
					ok=0;
			if(ok){
				id=k;
				break;
			}
		}
	}

	cout<<'!';
	for(ll i=0;i<n;i++)
		cout<<' '<<cand[id][i];
	cout<<endl;
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
