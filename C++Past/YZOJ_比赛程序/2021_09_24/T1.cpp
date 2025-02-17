#include<bits/stdc++.h>
using namespace std;

int n,p1,p2;
int p[5000010];
int head[5000010],next[5000010][2];
int h,t,len;
 
int main() 
{
    scanf("%d%d%d",&n,&p1,&p2);
     
    for (int i=2;i<=n;++i)
        if (p[i]==0)
		{
            p[i]=i;
            for (int j=i*2;j<=n;j+=i)
                if(p[j]==0)p[j]=i;
    	}
           
    h=1;
	t=n;
	len=n;
	
    for (int i=1;i<=n;++i)
    {
     	head[i]=i;
     	next[i][0]=0;
     	next[i][1]=0;
	}
          
    while(len!=1) 
	{
        int m=len/p[len];	//ÕÛµş³¤¶È 
         
        if (len%2?p2==1:p1==1)	//´Ó×óÍùÓÒ 
		{
            for (int j=h+m-1,k=h+m;j>=h;--j,++k) 
			{
                next[head[k]][k%2]=head[j];
                next[head[j]][j%2]=head[k];
                head[k]=j;
            }
            h+=m;
        }
        else 					//´ÓÓÒÍù×ó 
		{
            for (int j=t-m+1,k=t-m;j<=t;++j,--k) 
			{
                next[head[k]][k%2]=head[j];
            	next[head[j]][j%2]=head[k];
                head[k]=j;
            }
            t-=m;
        }
        len-=m;
    }
     
    for (int i=head[h];i;i=next[i][head[h]%2]) 
        printf("%d\n",i);
    return 0;
}
