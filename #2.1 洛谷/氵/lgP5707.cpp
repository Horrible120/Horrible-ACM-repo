#include<cstdio>
#include<cmath>
using namespace std;

int t,h,m;
float s,v;

int main()
{
	scanf("%f%f",&s,&v);
	
	t=ceil(s/v)+10;
	
	h=(31-t/60)%24;
	m=(60-t%60)%60;
	
	printf("%02d:%02d",h,m);
	
	
	return 0;
}
