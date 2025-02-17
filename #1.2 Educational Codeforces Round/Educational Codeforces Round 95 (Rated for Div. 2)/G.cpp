#include<iostream>
#include<map>
#include<vector>
#include<random>
#include<ctime>
using namespace std;

long long n,ans;
const uint64_t M=917354628531972864;
uint64_t hs[500010];
mt19937_64 rnd(42);

uint64_t kxor(uint64_t a,uint64_t b,int k)
{
	uint64_t res=0,p=1;
	while(a||b)
	{
		res+=((a+b)%M)%k*p;
		a/=k,b/=k;
		p*=k;
	}
	return res;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n;
	vector<int> v(n+1); 
	for(int i=1;i<=n;i++)
		cin>>v[i];
	
	
	
	vector<uint64_t> pr(n+1);
	map<uint64_t,int> cnt;
	int vct[500010]={};
	
	
	for(int i=1;i<=n;i++)
		hs[i]=rnd()%M;
	
	
	
	int l=0;
	pr[0]=0;
	cnt[0]=1;
	for(int i=1;i<=n;i++)
	{
		pr[i]=kxor(hs[v[i]],pr[i-1],3);
		vct[v[i]]++;
		
		while(vct[v[i]]>4)
		{
			if(l) vct[v[l]]--;
			cnt[pr[l]]--;
			l++;
			//cout<<'K'<<endl;
		}
		
		ans+=cnt[pr[i]];
		//cout<<i<<' '<<v[i]<<' '<<cnt[pr[i]]<<' '<<l<<' '<<pr[i]<<endl;
		cnt[pr[i]]++;
		
	}
	cout<<ans<<endl;
	
	
	
	return 0;
}
