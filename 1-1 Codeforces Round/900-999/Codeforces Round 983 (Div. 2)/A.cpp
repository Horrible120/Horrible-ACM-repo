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
using namespace std;

long long tt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		int n,sum=0;
		cin>>n;
		vector<int> v(2*n+1);
		for(int i=1;i<=2*n;i++)
		{
			cin>>v[i];
			sum+=v[i];
		}
		int s=2*n-sum;
		//cout<<">>";
		cout<<(sum%2)<<' '<<min(min(s,sum),n)<<endl;
	}

	return 0;
}


