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
	vector<array<ll,3>> seg(n);
	vector<ll> pos;
	for(ll i=0;i<n;i++){
		cin>>seg[i][0]>>seg[i][1]>>seg[i][2];
		seg[i][2]--;
		pos.emplace_back(seg[i][0]);
		pos.emplace_back(seg[i][1]);
	}
	sort(pos.begin(),pos.end());
	pos.erase(unique(pos.begin(),pos.end()),pos.end());
	ll m=pos.size();
	for(ll i=0;i<n;i++){
		seg[i][0]=lower_bound(pos.begin(),pos.end(),seg[i][0])-pos.begin()+1;
		seg[i][1]=lower_bound(pos.begin(),pos.end(),seg[i][1])-pos.begin()+1;
	}
	sort(seg.begin(),seg.end(),[&](const auto &a,const auto &b){
		return a[1]<b[1];
	});

	vector<vector<ll>> mx(2,vector<ll>(4*m+8,-INF));
	vector<vector<ll>> tag(2,vector<ll>(4*m+8));
	auto apply=[&](ll c,ll p,ll v)->void{
		mx[c][p]+=v;
		tag[c][p]+=v;
	};
	auto push=[&](ll c,ll p)->void{
		apply(c,p*2,tag[c][p]);
		apply(c,p*2+1,tag[c][p]);
		tag[c][p]=0;
	};
	auto add=[&](auto &&self,ll c,ll p,ll l,ll r,ll ql,ll qr,ll v)->void{
		if(ql<=l&&r<=qr){
			apply(c,p,v);
			return;
		}
		push(c,p);
		ll mid=(l+r)/2;
		if(ql<=mid)
			self(self,c,p*2,l,mid,ql,qr,v);
		if(qr>mid)
			self(self,c,p*2+1,mid+1,r,ql,qr,v);
		mx[c][p]=max(mx[c][p*2],mx[c][p*2+1]);
	};
	auto upd=[&](auto &&self,ll c,ll p,ll l,ll r,ll x,ll v)->void{
		if(l==r){
			mx[c][p]=max(mx[c][p],v);
			return;
		}
		push(c,p);
		ll mid=(l+r)/2;
		if(x<=mid)
			self(self,c,p*2,l,mid,x,v);
		else
			self(self,c,p*2+1,mid+1,r,x,v);
		mx[c][p]=max(mx[c][p*2],mx[c][p*2+1]);
	};
	auto query=[&](auto &&self,ll c,ll p,ll l,ll r,ll ql,ll qr)->ll{
		if(ql<=l&&r<=qr)
			return mx[c][p];
		push(c,p);
		ll mid=(l+r)/2,res=-INF;
		if(ql<=mid)
			res=max(res,self(self,c,p*2,l,mid,ql,qr));
		if(qr>mid)
			res=max(res,self(self,c,p*2+1,mid+1,r,ql,qr));
		return res;
	};
	upd(upd,0,1,0,m,0,0);
	upd(upd,1,1,0,m,0,0);

	for(ll i=0;i<n;i++){
		ll l=seg[i][0],r=seg[i][1],c=seg[i][2],d=c^1;
		ll best=query(query,d,1,0,m,0,l-1)+1;
		add(add,d,1,0,m,0,l-1,1);
		upd(upd,c,1,0,m,r,best);
	}
	cout<<max(mx[0][1],mx[1][1])<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
