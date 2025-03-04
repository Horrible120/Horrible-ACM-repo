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

typedef long long ll;
typedef uint64_t ull;

ll tt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		ll l,r,k;
		cin>>l>>r>>k;
		
		ll bd=0;
		
		if(l*k>r)
			cout<<0<<endl;
		else
		{
			bd=r/k;
			bd-=l-1;
			cout<<bd<<endl;
		}
		
	}

	return 0;
}


