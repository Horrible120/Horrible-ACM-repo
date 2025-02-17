#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

mt19937_64 rnd(time(0));
uint64_t mp[300010],hs[300010],pre[600010],ans;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	for(int i=1;i<=300000;i++)
		mp[i]=rnd();
	for(int i=1;i<=300000;i++)
		hs[i]=hs[i-1]^mp[i];
	
	int n;
	
	//for(int i=1;i<=10;i++)
	//	cout<<hs[i]<<endl;
	
	cin>>n;
	
	vector<int> a(n+1);
	vector<uint64_t> v(n+1);
	
	for(int i=1;i<=n;i++)
		cin>>a[i],v[i]=mp[a[i]];
	for(int i=1;i<=n;i++)
		pre[i]=pre[i-1]^v[i];
	
	//for(int i=1;i<=10;i++)
	//	cout<<pre[i]<<endl;
	
	
	for(int i=1;i<=n;i++)
		if(a[i]==1)	ans++;
	for(int i=1;i<=n;i++)
	{
		int j=n+1-i;
		if(a[i]==1)
		{
			set<int> s;
			int cur=i+1;
			while(a[cur]!=1&&cur<=n)
			{
				s.insert(a[cur]);
				if(cur-*s.rbegin()>=0&&hs[*s.rbegin()]==(pre[cur]^pre[cur-*s.rbegin()]))
				{
					ans++;
					//cout<<"1! "<<i<<' '<<cur<<' '<<*s.rbegin()<<endl;
				}
					
				cur++;
			}
		}
		if(a[j]==1)
		{
			set<int> s;
			int cur=j-1;
			while(a[cur]!=1&&cur>=1)
			{
				s.insert(a[cur]);
				if((cur+*s.rbegin()-1<=n)&&hs[*s.rbegin()]==(pre[cur-1]^pre[cur+*s.rbegin()-1]))
				{
					ans++;
					//cout<<"2! "<<j<<' '<<cur<<' '<<*s.rbegin()<<endl;
					//cout<<hs[*s.rbegin()]<<' '<<(pre[cur-1]^pre[(cur+*s.rbegin())-1])<<endl;
				}
					
				cur--;
			}
		}
	}
	
	//int y=5;
	//cout<<(pre[4]^pre[y-1]==1)<<' '<<pre[4]<<endl;
	
	cout<<ans<<endl;
	return 0;
}

