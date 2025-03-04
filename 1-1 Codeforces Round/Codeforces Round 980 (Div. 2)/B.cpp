#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<algorithm>
using namespace std;

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	int n,k;
	long long sum;
	
	while(t--)
	{
		long long mx=0,mn=1e9;
		cin>>n>>k;
		sum=0;
		vector<long long> v(n+1);
		for(int i=1;i<=n;i++)
			cin>>v[i];
		sort(v.begin(),v.end());
		int lst=0;
		for(int i=1;i<=n;i++,sum++)
		{
			if((v[i]-lst)*(n-i+1)>=k)
			{
				cout<<sum+k<<endl;
				break;
			}
			else
			{
				sum+=(v[i]-lst)*(n-i+1);
				k-=(v[i]-lst)*(n-i+1);
				lst=v[i];
			}
			while(i<n&&v[i]==v[i+1])
			{
				i++;
				sum++;
			}
					
		}
	}
	
	return 0;
}
