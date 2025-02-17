int logn[100010];

void Preprocessing()
{
	logn[1]=0;
	for(int i=2;i<=100000;i++)
		logn[i]=logn[i>>1]+1;
		
	for(int i=1;i<=logn[N];i++)
		for(int j=1;j+(1<<i)-1<=N;j++)
			ST[j][i]=max(ST[j][i-1],ST[j+(1<<(i-1))][i-1]);
	return;
}

int solve(int x,int y)
{
	int lg=logn[y-x+1];
	return max(ST[x][lg],ST[y-(1<<lg)+1][lg]);
}

int main()
{
	scanf("%d%d",&N,&M);
	
	for(int i=1;i<=N;i++)
		scanf("%d",&ST[i][0]);
	
	Preprocessing();
		
	for(int i=1;i<=M;i++)
		scanf("%d%d",&ask[i][0],&ask[i][1]);
		
	for(int i=1;i<=M;i++)	
		printf("%d\n",solve(ask[i][0],ask[i][1]));
	
	return 0;
}
