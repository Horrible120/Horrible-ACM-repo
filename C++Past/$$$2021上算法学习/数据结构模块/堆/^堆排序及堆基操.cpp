#include<cstdio>
using namespace std;

int n,op,p;
int heap[100010];

void Max_heapify(int o)
{
	int largest=o;
	
	if(o*2<=p&&heap[largest]<heap[o*2])
		largest=o*2;
	if(o*2+1<=p&&heap[largest]<heap[o*2+1])
		largest=o*2+1;
	if(largest!=o)
	{
		int k=heap[largest];
		heap[largest]=heap[o];
		heap[o]=k;
		Max_heapify(largest);	
	}
	return; 
}

void Min_heapify(int o)
{
	int Min=o;
	
	if(o*2<=p&&heap[Min]>heap[o*2])
		Min=o*2;
	if(o*2+1<=p&&heap[Min]>heap[o*2+1])
		Min=o*2+1;
	if(Min!=o)
	{
		int k=heap[Min];
		heap[Min]=heap[o];
		heap[o]=k;
		Min_heapify(Min);	
	}
	return; 
}

void Build_Max_heap()
{
	for(int i=n/2;i>=1;i--)
		Max_heapify(i);
	return;
}

void Build_Min_heap()
{
	for(int i=n/2;i>=1;i--)
		Min_heapify(i);
	return;
}

int main()
{
	scanf("%d%d",&n,&op);
	p=n;
	
	for(int i=1;i<=n;i++)
		scanf("%d",&heap[i]);
	
	if(op==1)
		Build_Max_heap();
	else
		Build_Min_heap();
		
	
	for(int i=1;i<=n;i++)
	{
		printf("%d ",heap[1]);
		heap[1]=heap[p--];
		if(op==1)
			Max_heapify(1);
		else
			Min_heapify(1);
	}
	
	return 0;
}
