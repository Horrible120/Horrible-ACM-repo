#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
const int MAXN = 100005;
int read()/*快读*/ 
{
    int x=0,flag=1;
    char c;
    while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*flag;
}
int n,m,tot,root=1,a[MAXN],f[MAXN],fa[MAXN],siz[MAXN],num[MAXN];
/* 节点数 指令数 根节点(默认为1) 每个节点的权值 父节点 子树大小 */ 
int Index,top[MAXN],c[MAXN],son[MAXN],dep[MAXN],tr[MAXN*4],lazy[MAXN*4];
/************************************************************************************/
struct edge//	.	.	.	.	.	.	.	前向星储存结构体 
{
    int v,next;//	.	.	.	.	.	.	目标节点 下一条边编号 
} e[2*MAXN];
/************************************************************************************/
void dfs1(int u,int par)//	.	.	.	.	.	处理 重子节点 子树大小 父节点 节点深度 
{
    fa[u]=par;//	.	.	.	.	.	.	.	定义 父节点 
    dep[u]=dep[par]+1;//	.	.	.	.	.	处理 节点深度 = 父节点深度 + 1 
    siz[u]=1;//	.	.	.	.	.	.	.	.	默认 子树大小 为 1 (自己)
	 
    for(int i=f[u]; i; i=e[i].next)//	.	.	遍历所有出边 
    {
        int v=e[i].v;//	.	.	.	.	.	.	目标节点 
        if(v==par) continue;//	.	.	.	.	排除父节点 
        dfs1(v,u);//	.	.	.	.	.	.	以 当前节点 为 父节点 , 目标节点 为 当前节点 进行下一步搜索 
        siz[u]+=siz[v];//	.	.	.	.	.	子树大小 += 儿子的子树大小 
        if(siz[v]>siz[son[u]])//	.	.	.	如果 当前子树大小 大于 当前重儿子子树大小
            son[u]=v;//	.	.	.	.	.	.	更新重儿子 
    }
}
/************************************************************************************/
void dfs2(int u,int tp)//	.	.	.	.	.	处理 节点所在链链顶 节点的DFS序(新编号) 
{
    num[u]=++Index;//	.	.	.	.	.	.	u的DFS序 = 当前遍历过的节点数+1 
    c[Index]=a[u];//	.	.	.	.	.	.	将 权值 搬运到新编号下 
    top[u]=tp;//	.	.	.	.	.	.	.	定义 当前节点所在链的链顶 
    if(son[u]) dfs2(son[u],tp);//	.	.	.	选重子节点传承这条链 
    for(int i=f[u]; i; i=e[i].next)//	.	.	遍历所有出边
        if(e[i].v^fa[u] && e[i].v^son[u])//	.	剔除 父亲 和 重子节点 
            dfs2(e[i].v,e[i].v);//	.	.	.	以 当前节点 为 父节点 , 目标节点 为 当前节点 进行下一步搜索
}
/************************************************************************************/
int Lca(int x,int y)//	.	.	.	.	.	.	树链剖分下 求 最近公共祖先 
{
    while(top[x]!=top[y])//	.	.	.	.	.	若两个点不在同一条树链上 
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]>dep[y]?y:x;
}
/************************************************************************************/
int Find(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        if(fa[top[x]]==y) return top[x];
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    return son[y];
}
/************************************************************************************/
void build(int i,int l,int r)
{
    if(l==r)
    {
        tr[i]=c[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    tr[i]=tr[i<<1]+tr[i<<1|1];
}
/************************************************************************************/
void down(int i,int l,int mid,int r)
{
    if(!lazy[i]) return ;
    int x=lazy[i],l1=mid-l+1,l2=r-mid;
    tr[i<<1]+=x*l1;
    tr[i<<1|1]+=x*l2;
    lazy[i<<1]+=x;
    lazy[i<<1|1]+=x;
    lazy[i]=0;
}
/************************************************************************************/
void updata(int i,int l,int r,int L,int R,int x)
{
    if(L<=l && r<=R)
    {
        int len=r-l+1;
        tr[i]+=len*x;
        lazy[i]+=x;
        return ;
    }
    if(r<L || R<l) return ;
    int mid=(l+r)>>1;
    down(i,l,mid,r);
    updata(i<<1,l,mid,L,R,x);
    updata(i<<1|1,mid+1,r,L,R,x);
    tr[i]=tr[i<<1]+tr[i<<1|1];
}
/************************************************************************************/
int query(int i,int l,int r,int L,int R)
{
    if(L<=l && r<=R)
        return tr[i];
    if(r<L || R<l)
        return 0;
    int mid=(l+r)>>1;
    down(i,l,mid,r);
    return query(i<<1,l,mid,L,R)+query(i<<1|1,mid+1,r,L,R);
}
/************************************************************************************/
void modify(int u,int v,int x)
{
    while(top[u]^top[v])
    {
        if(dep[top[u]]<=dep[top[v]]) swap(u,v);
        updata(1,1,n,num[top[u]],num[u],x);
        u=fa[top[u]];
    }
    if(dep[u]<=dep[v]) swap(u,v);
    updata(1,1,n,num[v],num[u],x);
}
/************************************************************************************/
int ask(int u,int v)
{
    int ans=0;
    while(top[u]^top[v])
    {
        if(dep[top[u]]<=dep[top[v]]) swap(u,v);
        ans+=query(1,1,n,num[top[u]],num[u]);
        u=fa[top[u]];
    }
    if(dep[u]<=dep[v]) swap(u,v);
    ans+=query(1,1,n,num[v],num[u]);
    return ans;
}
/**********************************************************************************/
signed main()
{
    n=read();
    for(int i=1; i<=n; i++)
        a[i]=read();//	.	.	.	.	.	.	.	.	.	读取权值 
    
    for(int i=2; i<=n; i++)
    {
        int j=read();
        e[++tot]=edge{i,f[j]},f[j]=tot;//	.	.	.	.	前向星储存边 
        e[++tot]=edge{j,f[i]},f[i]=tot;
    }
    
    dfs1(1,0);//	.	.	.	.	.	.	.	.	.	.	处理 重子节点 子树大小 父节点 节点深度 
    
    dfs2(1,1);
    
    build(1,1,n);
    
    m=read();
    
    while(m--)
    {
        int op=read(),u=read();
        if(op==1)
            root=u;
        if(op==2)
        {
            int v=read(),c=read();
            modify(u,v,c);
        }
        if(op==3)
        {
            int c=read(),lca=Lca(root,u);
            if(u==root)
            {
                updata(1,1,n,1,siz[1],c);
                continue ;
            }
            if(lca==u)
            {
                int v=Find(root,u);
                updata(1,1,n,1,n,c);
                updata(1,1,n,num[v],num[v]+siz[v]-1,-c);
            }
            else
                updata(1,1,n,num[u],num[u]+siz[u]-1,c);
        }
        if(op==4)
            printf("%lld\n",ask(u,read()));
        if(op==5)
        {
            if(u==root)
            {
                printf("%lld\n",query(1,1,n,1,siz[1]));
                continue ;
            }
            int lca=Lca(root,u),ans;
            if(lca==u)
            {
                int v=Find(root,u);
                ans=query(1,1,n,1,n)-query(1,1,n,num[v],num[v]+siz[v]-1);
            }
            else
                ans=query(1,1,n,num[u],num[u]+siz[u]-1);
            printf("%lld\n",ans);
        }
    }
}

