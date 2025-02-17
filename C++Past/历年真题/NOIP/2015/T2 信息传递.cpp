#include <cstdio> 
#include <algorithm>
using namespace std;
const int MAXN=200000,INF=0x3f3f3f3f;
int dfs_clock,N,Ans=INF,T[MAXN+10],Clk[MAXN+10];
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        scanf("%d",&T[i]);
    for(int i=1,j;i<=N;i++)
        if(!Clk[i]) {
            int st=++dfs_clock;
            for(j=i;!Clk[j];j=T[j])
                Clk[j]=++dfs_clock;
            if(Clk[j]>=st) Ans=min(Ans,dfs_clock-Clk[j]+1);
        }
    printf("%d",Ans);
}
