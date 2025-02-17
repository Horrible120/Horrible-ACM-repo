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
		int a=0,b=0,mxa=0,mxb=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a>>b;
			mxa=max(a,mxa);
			mxb=max(b,mxb);
		}
		cout<<(mxa+mxb)*2<<endl;
			 
	}

	return 0;
}

