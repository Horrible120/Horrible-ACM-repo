#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<windows.h>
#include<algorithm>
using namespace std;

struct Draws
{
	int year,month,day,hour,min,sec;
	int lv;
	string data;
}draws[10010];

int num;
float perd[25][17];
float perh[21][17];
float pert[17];

bool cmp1(Draws a,Draws b)
{
	return a.data<b.data;
}

void move(int X,int Y)
{
	SetCursorPos(X,Y);
}

void lc()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
}

void ld()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
}

void lu()
{
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
}

void rc()
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
}

void rd()
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
}

void ru()
{
	mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
}

void kc(int k)
{
	keybd_event(k,0,0,0);
	keybd_event(k,0,KEYEVENTF_KEYUP,0);
}

void kd(int k)
{
	keybd_event(k,0,0,0);
}

void ku(int k)
{
	keybd_event(k,0,KEYEVENTF_KEYUP,0);
}

int main()
{
	freopen("ark_draw_data.txt","r",stdin);
	freopen("ark_draw_result.txt","w",stdout);
	
	scanf("%d\n",&num);
	
	char s[40];
	
	for(int i=1;i<=num;i++)
	{
		gets(s);
		draws[i].data=s;
		draws[i].year=(s[0]-48)*1000+(s[1]-48)*100+(s[2]-48)*10+(s[3]-48);
		draws[i].month=(s[5]-48)*10+(s[6]-48);
		draws[i].day=(s[8]-48)*10+(s[9]-48);
		draws[i].hour=(s[11]-48)*10+(s[12]-48);
		draws[i].min=(s[14]-48)*10+(s[15]-48);
		draws[i].sec=(s[17]-48)*10+(s[18]-48);
		draws[i].lv=(s[20]-48);
		
		pert[0]++;
		pert[draws[i].lv]++;
		
		perd[draws[i].hour][0]++;
		perd[draws[i].hour][draws[i].lv]++;
		
		perh[draws[i].min/3][0]++;
		perh[draws[i].min/3][draws[i].lv]++;
	}
	
	sort(draws+1,draws+num+1,cmp1);
	
	for(int i=1;i<=num;i++)
		cout<<draws[i].data<<endl;
		
	printf("\n\n");
	
	for(int i=0;i<=23;i++)
	{
		float k1,k2,k3,k4;
		if(perd[i][3]) k1=perd[i][3]/perd[i][0];
			else k1=0.4;
		if(perd[i][4]) k2=perd[i][4]/perd[i][0];
			else k2=0.5;
		if(perd[i][5]) k3=perd[i][5]/perd[i][0];
			else k3=0.1;
		if(perd[i][6]) k4=perd[i][6]/perd[i][0];
			else k4=0.02;
			
		perd[i][13]=k1;
		perd[i][14]=k2;
		perd[i][15]=k3;
		perd[i][16]=k4;
		
		printf("%2d:00-%2d:59----%0.2f  %0.2f  %0.3f  %0.4f\n",i,i,k1,k2,k3,k4);
	}
	
	printf("\n\n");
	
	for(int i=0;i<=19;i++)
	{
		float k1,k2,k3,k4;
		if(perh[i][3]) k1=perh[i][3]/perh[i][0];
			else k1=0.4;
		if(perh[i][4]) k2=perh[i][4]/perh[i][0];
			else k2=0.5;
		if(perh[i][5]) k3=perh[i][5]/perh[i][0];
			else k3=0.1;
		if(perh[i][6]) k4=perh[i][6]/perh[i][0];
			else k4=0.02;
			
			
		perh[i][13]=k1;
		perh[i][14]=k2;
		perh[i][15]=k3;
		perh[i][16]=k4;
			
			
		printf(":%2d-:%2d----%0.2f  %0.2f  %0.3f  %0.4f\n",i*3,i*3+2,k1,k2,k3,k4);
	}
	
	printf("\n\n%0.4f  %0.4f  %0.4f  %0.4f\n",pert[3]/pert[0],pert[4]/pert[0],pert[5]/pert[0],pert[6]/pert[0]);		
	
	
	ShellExecute(NULL,"open","mspaint.exe",NULL,NULL,SW_SHOWNORMAL); 
	
	int x=5,y=162;
	
	Sleep(5000);
/*****************************************/	
	move(15,172);
	ld();Sleep(200);
	move(515,172);Sleep(200);
	move(515,392);Sleep(200);
	move(15,392);Sleep(200);
	move(15,172);Sleep(200);
	lu();Sleep(200);
/******************************************/	
	
	move(15,402);
	ld();Sleep(200);
	move(435,402);Sleep(200);
	move(435,622);Sleep(200);
	move(15,622);Sleep(200);
	move(15,402);Sleep(200);
	lu();Sleep(200);
	
/*****************************************/	
	kd(17);
	Sleep(200);
	kc(109);Sleep(200);
	kc(109);Sleep(200);
	ku(17);Sleep(200);
/**************************************/	
	move(15,382-0.5*200);
	ld();Sleep(200);
	move(515,382-0.5*200);
	lu();Sleep(200);
	
	move(15,382-0.4*200);
	ld();Sleep(200);
	move(515,382-0.4*200);
	lu();Sleep(200);
	
	move(15,382-0.1*200);
	ld();Sleep(200);
	move(515,382-0.1*200);
	lu();Sleep(200);
/*******************************************/	
	move(15,612-0.5*200);
	ld();Sleep(200);
	move(435,612-0.5*200);
	lu();Sleep(200);
	
	move(15,612-0.4*200);
	ld();Sleep(200);
	move(435,612-0.4*200);
	lu();Sleep(200);
	
	move(15,612-0.1*200);
	ld();Sleep(200);
	move(435,612-0.1*200);
	lu();Sleep(200);
/*********************************************/	
	kd(17);
	Sleep(200);
	kc(107);Sleep(200);
	ku(17);Sleep(200);
	
	for(int i=0;i<=22;i++)
	{
		move(903,64);
		lc();
		Sleep(50);
		
		move(35+i*20,382-perd[i][13]*200);
		ld();
		move(35+(i+1)*20,382-perd[i+1][13]*200);
		lu();
		
		
		
		move(948,64);
		lc();
		Sleep(50);
		
		move(35+i*20,382-perd[i][14]*200);
		ld();
		move(35+(i+1)*20,382-perd[i+1][14]*200);
		lu();
		
		
		
		move(860,86);
		lc();
		Sleep(50);
		
		move(35+i*20,382-perd[i][15]*200);
		ld();
		move(35+(i+1)*20,382-perd[i+1][15]*200);
		lu();
	}
	
	Sleep(3000);
	
	
	
	for(int i=0;i<=18;i++)
	{
		move(903,64);
		lc();
		Sleep(50);
		
		move(35+i*20,612-perh[i][13]*200);
		ld();
		move(35+(i+1)*20,612-perh[i+1][13]*200);
		lu();
		
		
		
		move(948,64);
		lc();
		Sleep(50);
		
		move(35+i*20,612-perh[i][14]*200);
		ld();
		move(35+(i+1)*20,612-perh[i+1][14]*200);
		lu();
		
		
		
		move(860,86);
		lc();
		Sleep(50);
		
		move(35+i*20,612-perh[i][15]*200);
		ld();
		move(35+(i+1)*20,612-perh[i+1][15]*200);
		lu();
	}
	
	return 0;
}
