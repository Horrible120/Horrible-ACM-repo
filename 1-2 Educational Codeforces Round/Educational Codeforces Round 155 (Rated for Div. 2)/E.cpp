#include<bits/stdc++.h>
using namespace std;
int n,DEP,K,rt[10001],dep[10001],col[10001];
vector<int> son[1001];
void dfs(int x,int fa){
	rt[x]=fa;//rt 记录所在大子树的根节点 
	DEP=max(DEP,dep[x]);//记录数的高度 
	for(auto y:son[x]){
		dep[y]=dep[x]+1;
		dfs(y,fa);
	}
}
bool check(){
	if(DEP==1)return 0;//只有两层for循环进不去 
	for(int i=2;i<=n;++i)
		if(son[i].size()==1){//单子节点 
			if((~col[rt[i]])&&col[rt[i]]!=(dep[i]&1))return 0;//矛盾了 
			col[rt[i]]=dep[i]&1;//根据层数奇偶性 
		}
	return 1;
}
void color_2(int x){//染两种颜色 
	if(col[x]==-1)col[x]=0;
	for(auto y:son[x]){
		if(x!=1)col[y]=col[x]^1;
		color_2(y);
	}
	if(col[x]==0)col[x]=2;
}
void color_3(int x){//染三种颜色 
	if(x!=1)col[x]=dep[x]%3;
	for(auto y:son[x])color_3(y);
}
int main(){
	cin>>n;
	for(int i=2;i<=n;++i){
		int par;
		scanf("%d",&par);
		son[par].push_back(i);
	}
	for(auto y:son[1])dep[y]=1,dfs(y,y);
	memset(col,0xff,sizeof(col));
	if(check()){
		K=2;
		cout<<"2\n";
		color_2(1);
	}
	else{
		K=min(3,DEP);//注意特判 
		cout<<K<<"\n";
		color_3(1);
	}
	for(int i=2;i<=n;++i)
		cout<<(col[i]+2)%3+1<<" ";
	cout<<endl;
	while(1){
		int sta,ec[4]={0,0,0,0}; 
		scanf("%d",&sta);
		if(sta==1||sta==-1)return 0;
		for(int i=1;i<=K;++i){
			int tmp;
			scanf("%d",&tmp);
			if(tmp==1)ec[i]=1;//标注为 1 
		}
		if(ec[1]&&!ec[3])cout<<"1";
		else if(ec[2])cout<<"2";
		else cout<<"3";
		cout<<endl;
	}
}

