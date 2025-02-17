#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int n,q,ans,curl,curr;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>q;
	
	char h;
	int t;
	curl=1,curr=2;
	int disa=0,disb=0,disc=0;
	for(int i=1;i<=q;i++)
	{
		cin>>h>>t;
		disa=min(abs(curl-t),n-abs(curl-t));
		disb=min(abs(curr-t),n-abs(curr-t));
		disc=min(abs(curl-curr),n-abs(curl-curr));
		
		if(h=='L')
		{
			if(disc+disb==disa)
				ans+=n-disa;
			else
				ans+=disa;
			curl=t;
		}
		if(h=='R')
		{
			if(disc+disa==disb)
				ans+=n-disb;
			else
				ans+=disb;
			curr=t;
		}
		//cout<<disa<<' '<<disb<<' '<<disc<<endl;
	}
	
	cout<<ans<<endl;
	
	return 0;
}
