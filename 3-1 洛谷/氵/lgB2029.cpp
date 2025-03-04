#include<cstdio>
#include<cmath>
using namespace std;

float h,r,m=3.14;
int ans;

int main()
{
	scanf("%f%f",&h,&r);
	
	ans=ceil(20000/(h*r*r*m));
	
	printf("%d",ans);
	
	return 0;
}
