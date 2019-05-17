#include<stdio.h>
#include <windows.h>
int map[10][10]={
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};	/*��ʾ�Թ�������1��ʾΧǽ��0��ʾ�����ߵ�·*/ 
int location[10][10]={};	/*��ʾ�Ƿ��߹�ĳ��,2��ʾ������0��ʾδ����*/ 
int search(int starti,int startj);	/*Ѱ·����*/ 

int main()
{

	int starti=1,startj=1;	/*��ʾ�����������ʼλ��*/
	int i,j;
	
	SetConsoleOutputCP(437);	/*Ϊ����ʾ��չ��ascii�ַ��������ڵĴ���ҳ������ʾΪӢ��*/ 
	
	/*�жϳ����Ƿ���ںʹ�ӡ·��*/ 
	if(search(starti,startj)==0)
		printf("Path doesn't exist!");
	else{
		for(i=0;i<=9;i++){
			for(j=0;j<=9;j++){
				if(map[i][j]==1)
					printf("%c",178);
				else if(location[i][j]==0)
					printf("%c",255);
				else
					printf("%c",254);
			}
			printf("\n");
		}
	}
	
} 


int search(int starti,int startj)
{
	int endi=8,endj=8;	/*��ʾ�յ�λ��*/  
	int goal=0;	/*��ʾ�Ƿ񵽴��յ�*/
	
	if(starti==endi&&startj==endj)
		goal=1;	/*��ʾ�����յ�*/ 
		
	location[starti][startj]=2;	/*��Ǿ�����λ��*/ 
	
	
	if(goal==0&&map[starti][startj+1]==0&&location[starti][startj+1]==0)
		if(search(starti,startj+1)==1)
			return 1;
	if(goal==0&&map[starti+1][startj]==0&&location[starti+1][startj]==0)
		if(search(starti+1,startj)==1)
			return 1;
	if(goal==0&&map[starti][startj-1]==0&&location[starti][startj-1]==0)
		if(search(starti,startj-1)==1)
			return 1;
	if(goal==0&&map[starti-1][startj]==0&&location[starti-1][startj]==0) 
		if(search(starti-1,startj)==1)
			return 1;
	/*�����������ϵ�˳��̽·*/ 
				
	if(goal==0)
		location[starti][startj]=0;	/*�����涼�߲�ͨʱ���˻ط�֧λ��*/ 
		
	return goal;
	
}







