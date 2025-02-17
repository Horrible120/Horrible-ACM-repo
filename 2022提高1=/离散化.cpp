#include<cstdio>
#include<algorithm>
using namespace std;

int n,a[1000010];
int b[1000010];
int len;

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
		
	sort(a+1,a+n+1);
	
	len=unique(a+1,a+n+1)-a-1;
	
	for(int i=1;i<=n;i++)
		printf("%d ",lower_bound(a+1,a+len+1,b[i])-a);
	
	return 0;
}
