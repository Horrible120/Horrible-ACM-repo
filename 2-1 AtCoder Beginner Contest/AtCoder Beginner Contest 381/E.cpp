#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt;



int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	ll n,q;
	string s;
	
	cin>>n>>q;
	cin>>s;
	
	vector<ll> pre(n+1),sub(n+1),left(n+1),right(n+1);
	vector<vector<ll>> len(n+1,vector<ll>());
	map<ll,ll> ans;
	
	for(ll i=0;i<n;i++){
		if(s[i]!='1')
			continue;
		ll cnt=0;
		while(i<n&&s[i]=='1')
			cnt++,i++;
		pre[i]=cnt;
		if(i>0)
			pre[i]=max(pre[i],pre[i-1]);
	}
	
	for(ll i=n-1;i>=0;i--){
		if(s[i]!='2')
			continue;
		ll cnt=0;
		while(i>=0&&s[i]=='2')
			cnt++,i--;
		if(i<0)
			break;
		sub[i]=cnt;
		sub[i]=max(sub[i],sub[i+1]);
	}
	
	ans[-1]=-1;
	
	if(s[0]=='/') len[0].emplace_back(0),ans[0]=1;
	else len[0].emplace_back(-1),ans[0]=0;
	for(ll i=1;i<n;i++){
		if(s[i]=='/'){
			len[i].emplace_back(i);
			ans[i]=1+2*min(pre[i],sub[i]);
		}
		else{
			len[i].emplace_back(-1);
			ans[i]=0;
		}
	}
	
	right[0]=ans[0]?0:-1;
	for(ll i=1;i<n;i++)
		if(ans[i]) right[i]=ans[i];
		else right[i]=right[i-1];
	left[n-1]=ans[n-1]?n-1:-1;
	for(ll i=n-2;i>=0;i--)
		if(ans[i]) left[i]=i;
		else left[i]=left[i+1];
	
	for(ll j=0;j<n;j++)
		cout<<ans[j]<<' ';
	cout<<endl;
	for(ll j=0;j<n;j++)
		cout<<left[j]<<' ';
	cout<<endl;
	for(ll j=0;j<n;j++)
		cout<<right[j]<<' ';
	cout<<endl;
	
	
	for(ll i=1;(1<<i)<=n;i++)
		for(ll j=0;j<n;j++)
				len[j].emplace_back(ans[len[j][i-1]]>ans[len[min(j+(1<<(i-1)),n-1)][i-1]]?
									len[j][i-1]:len[min(j+(1<<(i-1)),n-1)][i-1]);
	
	for(ll i=0;(1<<i)<=n;i++){
		for(ll j=0;j<n;j++)
			cout<<len[j][i]<<' ';
		cout<<endl;
	}
		
	
	ll l,r,m1,m2,m3,k;
	for(ll i=1;i<=q;i++){
		cin>>l>>r;
		l--,r--;
		m1=left[l]<=r?left[l]:-1;
		m2=right[r]>=l?right[r]:-1;
		if(m1!=-1&&m2!=-1&&m1<m2){
			k=log2(m2-m1-1);
			m3=ans[len[m1+1][k]]>ans[len[m2-(1<<k)][k]]?len[m1+1][k]:len[m2-(1<<k)][k];
		}
		else m3=-1;
		cout<<m1<<' '<<m2<<' '<<m3<<endl;
		ll l1=min(ans[m1],min(2*(m1-l)+1,2*(r-m1)+1)),
			l2=min(ans[m2],min(2*(m2-l)+1,2*(r-m2)+1)),
			l3=min(ans[m3],min(2*(m3-l)+1,2*(r-m3)+1));
		if(l1<=0&&l2<=0&&l3<=0){
			cout<<0<<endl;
			continue;
		}
		else
			cout<<max(max(l1,l2),l3)<<endl;
	}
	
//	for(ll i=0;i<n;i++)
//		cout<<len[i][0]<<' ';
	
	cout.flush();
	
	return 0;
}
