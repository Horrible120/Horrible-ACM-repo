#include<cstdio>
#include<cmath> 
#include<iostream>
using namespace std;

long fib(long long n)
{
     double z = sqrt(5.0);
     double x = (1 + z)/2;
     double y = (1 - z)/2;
     return floor((pow(x, n) - pow(y, n))/z + 0.5) %1000000009;
}


int main()
{
	long long n;
	scanf("%lld",&n);
	
	cout<<fib(n);
	
	return 0;
}
