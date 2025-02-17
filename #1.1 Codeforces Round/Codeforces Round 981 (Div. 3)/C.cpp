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
		vector<int> v(n+1);
		for(int i=1;i<=n;i++)
			cin>>v[i];
		
		int ans=0;
		int l,r;
		
		if(n%2)
		{
			ans=0;
			l=r=n/2+1;
		}
		else
		{
			ans=(v[n/2]==v[n/2+1]);
			l=n/2;
			r=n/2+1;
		}
		l--;r++;
		while(l>=1&&r<=n)
			ans+=min(((v[l]==v[l+1])+(v[r]==v[r-1])),((v[l]==v[r-1])+(v[r]==v[l+1]))),l--,r++;
		//cout<<"!!";
		cout<<ans<<endl;
	}

	return 0;
}

