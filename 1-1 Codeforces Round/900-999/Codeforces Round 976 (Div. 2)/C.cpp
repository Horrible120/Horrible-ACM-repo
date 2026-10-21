#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;

int t;

int main()
{
	cin>>t;
	
	while(t--)
	{
		long long b,c,d,a=0;
		cin>>b>>c>>d;
		
		bool flag=1;
		long long cnt=0;
		
		while(b||c||d)
		{
			long long btb,btc,btd,bta=0;
			btb=b%2;
			btc=c%2;
			btd=d%2;
			if(btb!=btc&&btc==btd)
			{
				flag=0;
				break;
			}
			if(btb==0&&btc==0)
			{
				bta=btd;
				//cout<<"0&0"<<cnt<<' '<<bta<<endl;
			}
				
			if(btb==1&&btc==1)
			{
				bta=(btd+1)%2;
				//cout<<"1&1"<<cnt<<' '<<btd<<endl;
			}
			
			//cout<<btb<<btc<<btd<<endl;
				
			b>>=1;
			c>>=1;
			d>>=1;
			a+=bta<<cnt;
			//cout<<bta<<' '<<cnt<<endl;
			cnt++;
		}
		if((!flag)||d) cout<<-1<<endl;
		else cout<<a<<endl;
	}
	
	return 0;
} 
