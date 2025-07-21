#include<cstdio>
#include<cmath>
using namespace std;

double a,b,c,p,ans;

int main()
{
	scanf("%lf%lf%lf",&a,&b,&c);
	
	p=(a+b+c)/2;
	
	ans=sqrt(p*(p-a)*(p-b)*(p-c));
	
	printf("%.1lf",ans);
	
	return 0;
	
}
