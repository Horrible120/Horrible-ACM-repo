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
		ll n,flag=1;
		string s,r;
		cin>>n;
		cin>>s>>r;
		ll a=0,b=0;
		
		for(int i=0;i<n;i++)
			if(s[i]=='1')
				a++;
			else
				b++;
		if(a==0||b==0)
			flag=0;
		for(int i=0;i<n-1;i++)
		{
			if(r[i]=='1')
				b--;
			else
				a--;
			if(i!=n-2&&(a==0||b==0))
			{
				flag=0;
			}
			if(i==n-2)
				if(a<0||b<0)
					flag=0;
		}
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
		
	}

	return 0;
}


