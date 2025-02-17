#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;

int t;

long long sqt(long long n)
{
	long long l=1,r=1000000000;
	while(l<r-1)
		{
			long long mid=(l+r)>>1;
			
			if(mid*mid>n) r=mid;
			else l=mid;
		}
	if(n<r*r&&n>=l*l) return l;
	return r;
}

int main()
{
	cin>>t;
	
	while(t--)
	{
		long long k;
		cin>>k;
		
		long long q=sqt(k)+k;
		
		long long a=sqt(q),b=sqt(k);
		
		if(a>b) q++;
		
		
		cout<<q<<endl;
	}
	
	return 0;
} 

