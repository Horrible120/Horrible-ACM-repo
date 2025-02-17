#include<cstdio>
using namespace std;

long long l,r,k,ans;

int op(int x)
{
	int re=0;
	while(!x%10)
		x=x/10;
	while(x)
	{
		re=re*10+x%10;
		x=x/10;
	}
		
	return re;
}

int main()
{
	scanf("%d%d%d",&l,&r,&k);
	
	for(long long i=l;i<=r;i++)
	{
		if((i*i)%k==op(i))
			ans++;
	}
	
	printf("%d",ans);
	
	return 0;
}
