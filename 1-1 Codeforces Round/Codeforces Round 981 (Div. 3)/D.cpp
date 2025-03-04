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

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>t;

	while(t--)
	{
		int n,ans=0;
		cin>>n;
		vector<long long> v(n+1),pre(n+1);
		for(int i=1;i<=n;i++)
			cin>>v[i];
		for(int i=1;i<=n;i++)
		{
			pre[i]=pre[i-1]+v[i];
			//cout<<pre[i]<<' ';
		}
			
		
		set<long long> s;
		s.insert(0);
		int cur=0;
		for(int i=1;i<=n;i++)
		{
			if(s.find(pre[i]-pre[cur])!=s.end())
			{
				ans++;
				s.clear();
				s.insert(0);
				//cout<<"!"<<i<<endl;
				cur=i;
			}
			else
				s.insert(pre[i]-pre[cur]);
		}
		//cout<<">>";
		cout<<ans<<endl;
	}

	return 0;
}

