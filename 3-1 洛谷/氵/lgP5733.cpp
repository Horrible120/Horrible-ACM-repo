#include<cstdio>
#include<cstring>
#include<fstream>
#include<iostream>
using namespace std; 

char s[1100];

int main()
{
	scanf("%s",&s);
	
	for(int i=0;i<sizeof(s);i++)
		if(s[i]>=97&&s[i]<=122)
			s[i]-=32;
			
	puts(s);
		
	return 0;
}
