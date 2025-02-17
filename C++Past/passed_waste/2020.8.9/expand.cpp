#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int p1,p2,p3;
string s;
int main()
{
	
	
	scanf("%d%d%d",&p1,&p2,&p3);
	scanf("%s",&s);
	printf("\n");
	for(int i=1;i<=s.size();i++)
	{
		if(s[i]!='-')
			printf("%c",s[i]);
		else if(s[i-1]<s[i+1])
		{
			if(s[i]<58&&s[i]>47)
			{
				
				if(p1=3)
					for(int j=s[i-1]+1;j<s[i+1];j++)
						for(int k=1;k<=p2;k++)
							printf("*");
				else
				{
					if(p3=1)
						for(int j=s[i-1]+1;j<s[i+1];j++)
							for(int k=1;k<=p2;k++)
								printf("%c",j);
					else if(p3=2)
						for(int j=s[i+1];j>s[i-1]+1;j--)
							for(int k=1;k<=p2;k++)
								printf("%c",j);
				}
			}
			
			if(s[i]<123&&s[i]>96)
			{
				if(p1=3)
					for(int j=s[i-1]+1;j<s[i+1];j++)
						for(int k=1;k<=p2;k++)
							printf("%c",'*');
				else if(p1=2)
					if(p3=1)
						for(int j=s[i-1]+1;j<s[i+1];j++)
							for(int k=1;k<=p2;k++)
								printf("%c",j);
					else if(p3=2)
						for(int j=s[i+1];j>s[i-1]+1;j--)
							for(int k=1;k<=p2;k++)
								printf("%c",j-32);
				else if(p1=1)
					if(p3=1)
						for(int j=s[i-1]+1;j<s[i+1];j++)
							for(int k=1;k<=p2;k++)
								printf("%c",j);
					else if(p3=2)
						for(int j=s[i+1];j>s[i-1]+1;j--)
							for(int k=1;k<=p2;k++)
								printf("%c",j);
			}
		}
			
	}
}
