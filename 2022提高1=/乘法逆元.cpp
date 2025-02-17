#include<cstdio>
using namespace std;

int n,p;
long long inv[3000010];

int main()
{
	scanf("%d%d",&n,&p);
	
	inv[1]=1;
	printf("%lld\n",inv[1]);
	
	for(int i=2;i<=n;i++)
	{
		inv[i]=(p-p/i)*inv[p%i]%p;
		printf("%lld\n",inv[i]);
	}
			
	return 0;
}
