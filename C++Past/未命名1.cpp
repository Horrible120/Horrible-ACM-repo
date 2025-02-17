#include<cstdio>
#include<cstring>

#define N 10001

using namespace std;

int n,l,x;

char s[N],a[N];

int main()
{
    while(scanf("%s",s+1)!=EOF)
	{
        x=0;
        l=strlen(s+1);
        
		int siz=l+1;
        
        while(siz>=1)
		{
            siz--;
            
            while(siz>=1&&s[siz]!='[')
				siz--;
            for(int i=siz+1;s[i]!=']'&&i<=l;i++)
				if(s[i]&&s[i]!='[')
					a[++x]=s[i],s[i]=0;    
        }
        
        for(int i=1;i<=x;i++)
			printf("%c",a[i]);  
			  
        for(int i=1;i<=l;i++)	
			if(s[i]&&s[i]!='['&&s[i]!=']')
				printf("%c",s[i]);   
				
				         
        printf("\n");
    }
    return 0;
}
