#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
using namespace std;

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	int n,k;
	while(t--)
	{
		cin>>n>>k;
		
		map<long long,long long> mp;
		set<long long> st;
		
		long long x,cc;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(mp[x])
			{
				cc=mp[x]+1;
				mp.erase(x);
				mp[x]=cc;
			}
			else
			{
				mp[x]=1;
				st.insert(x);
			}	
		}
			
			
		long long sum=0,ans=0,len=0;
		
		vector<long long> v;
		
		for(auto &i:st)
			v.push_back(i);
		
		sum=mp[v[0]];
		ans=mp[v[0]];
		len=1;
		
		//for(int i=0;i<v.size();i++)
		//	cout<<v[i]<<' '<<mp[v[i]]<<endl;
		
		for(int i=1;i<v.size();i++)
		{
			//cout<<v[i]<<endl;
			if(v[i]-v[i-1]<=1)
			{
				if(len==k)
				{
					ans=max(ans,sum);
					sum=sum+mp[v[i]]-mp[v[i-k]];
				}
				else
				{
					sum+=mp[v[i]];
					len++;
				}
			}
			else
			{
				ans=max(ans,sum);
				len=1;
				sum=mp[v[i]];
			}
		}
		ans=max(ans,sum);
		cout<<ans<<endl;
	}
	
	return 0;
}
