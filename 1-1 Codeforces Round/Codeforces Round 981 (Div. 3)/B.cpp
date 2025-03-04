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
		int n;
		cin>>n;
		int ans=0;
		int mn[1024]={};
		vector<vector<int>> v(n+1,vector<int>(n+1));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				cin>>v[i][j];
				if(v[i][j]<0)
					mn[n-i+j]=max(mn[n-i+j],-v[i][j]);
			}
		for(int i=1;i<2*n;i++)
			ans+=mn[i];
		//cout<<"!";
		cout<<ans<<endl;
		
	}

	return 0;
}

