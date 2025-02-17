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
		int n,k;
		cin>>n>>k;
		
		if(n==1)
			cout<<1<<endl<<1<<endl;
		else if(k==1||k==n)
			cout<<-1<<endl;
		else if(k==2||k==n-1||((k-1)&1))
		{
			cout<<3<<endl;
			cout<<1<<' '<<k<<' '<<k+1<<endl;
		}
		else
		{
			cout<<5<<endl;
			cout<<1<<' '<<2<<' '<<k<<' '<<k+1<<' '<<n<<endl;
		}
		
		
	}

	return 0;
}


