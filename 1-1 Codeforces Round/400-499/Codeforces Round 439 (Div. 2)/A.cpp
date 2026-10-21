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

	int n;
	cin>>n;
	vector<int> a(n+1),b(n+1),v(10000010);
	
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		v[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		v[b[i]]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(v[a[i]^b[j]])
				ans++;
	if(ans%2)
		cout<<"Koyomi"<<endl;
	else
		cout<<"Karen"<<endl;
	return 0;
}

