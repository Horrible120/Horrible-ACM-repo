#include<cstdio>
using namespace std;

long long n,k,p;
long long ans,a;

int main()
{
	
	scanf("%lld%lld%lld",&n,&k,&p);
	
	a=n;
	ans=1;
	
	while(k)
	{
		if(k%2)
			ans=(ans*a)%p;
		a=(a*a)%p;
		k=k/2;
	}
	
	printf("%lld",ans);
	
	return 0;
}
