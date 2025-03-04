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
		long long n;
		int cur=0;
		cin>>n;
		long long cost=n*(n+1)/2;
		vector<int> v(n+1);
		string s;
		cin>>s;
		for(int i=1;i<=n;i++)
			v[i]=(s[i-1]=='1'?1:0);
		set<int> st;
		for(int i=n;i>=1;i--)
		{
			if(v[i]==1)
			{
				if(i-cur>=2)
				{
					cost-=i;
					cur++;
				}
				else
					cur=max(cur-1,0);	
			}
			else
			{
				cur=max(cur-1,0);
			}
		}
		//cout<<">>";
		cout<<cost<<endl;
	}

	return 0;
}

