#include <stdio.h>     
#include <stdlib.h> 
#include <conio.h>
#include <windows.h> 
char movement[2][100]={
{0,},{0,}						/*movement[0][0]�ǳ�ʼ��֮��һά��¼����wsad����ά��¼�Ƿ��������ӣ�������p,û����u*/
};
int map1[10][12]={            /*���װ�*/    /*0Ϊ�յأ�1Ϊǽ��3ΪĿ�ĵأ�4Ϊ���ӣ�6Ϊ��*/
				{0,0,0,0,0,0,0,0,0,0,0,0},                 
		    	{0,0,1,1,1,0,0,0,0,0,0,0},                 
		    	{0,0,1,3,1,0,0,0,0,0,0,0},
		    	{0,0,1,0,1,1,1,1,0,0,0,0},
		    	{1,1,1,4,0,4,3,1,0,0,0,0},
		    	{1,3,0,4,6,1,1,1,0,0,0,0},
		    	{1,1,1,1,4,1,0,0,0,0,0,0},
		    	{0,0,0,1,3,1,0,0,0,0,0,0},
		    	{0,0,0,1,1,1,0,0,0,0,0,0},
		    	{0,0,0,0,0,0,0,0,0,0,0,0}
			};
int map2[10][12]={            /*���װ�*/ 
		    	{0,0,0,0,0,0,0,0,0,0,0,0},
		    	{1,1,1,1,1,1,1,1,0,0,0,0},
		    	{1,1,6,0,1,1,1,1,0,0,0,0},
		    	{1,1,0,4,0,0,1,1,0,0,0,0},
		    	{1,1,1,0,1,0,0,1,0,0,0,0},
		    	{1,3,1,0,1,0,0,1,0,0,0,0},
		    	{1,3,4,0,0,1,0,1,0,0,0,0},
		    	{1,3,0,0,0,4,0,1,0,0,0,0},
		    	{1,1,1,1,1,1,1,1,0,0,0,0},
		    	{0,0,0,0,0,0,0,0,0,0,0,0}
		    	};
int map3[10][12]={              /*һ���*/ 
				{0,0,0,0,0,0,0,0,0,0,0,0},
		    	{0,1,1,1,1,1,1,1,0,0,0,0},
		    	{0,1,0,0,0,0,0,1,1,1,0,0},
		    	{1,1,6,1,1,1,0,4,0,1,0,0},
		    	{1,0,4,0,0,0,0,0,0,1,0,0},
		    	{1,0,3,3,1,0,4,0,1,1,0,0},
		    	{1,1,3,7,1,0,0,0,1,0,0,0},
		    	{0,1,1,1,1,1,1,1,1,0,0,0},
		    	{0,0,0,0,0,0,0,0,0,0,0,0},
		    	{0,0,0,0,0,0,0,0,0,0,0,0}
				};
int map4[10][12]={              /*���Ѱ�*/ 
				{0,0,0,0,0,0,0,0,0,0,0,0},
		    	{0,1,1,1,1,1,1,1,0,0,0,0},
		    	{1,1,0,0,0,0,0,1,0,0,0,0},
		    	{1,0,0,7,3,4,3,1,0,0,0,0},
		    	{1,0,0,7,3,1,3,1,1,1,0,0},
		    	{1,0,1,4,6,4,4,0,0,1,0,0},
		    	{1,0,0,0,1,1,0,1,0,1,0,0},
		    	{1,1,1,1,1,1,0,0,0,1,0,0},
		    	{0,0,0,0,0,1,1,1,1,1,0,0},
		    	{0,0,0,0,0,0,0,0,0,0,0,0}
				};

void boxmap(int map[10][12])
{
	int i,j;
	system("color 0E");
	SetConsoleOutputCP(936);
	printf("�� ------------------------------------��\n");
	printf("�� Up:w    Down:s    Left:a    Right:d ��\n");
	printf("�� return to last step:q     restart:r ��\n");
	printf("�� return to menu:m                    ��\n");
	printf("�� ------------------------------------��\n");
	SetConsoleOutputCP(437);
	for(i=0;i<10;i++)
	{
		for(j=0;j<12;j++)
		{
			switch(map[i][j])
			{
			case 0:
				printf("  "); /*�յ�*/
				break;
			case 1:
  				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  0| FOREGROUND_INTENSITY );  
				printf("%c",254); /*ǽ*/
				break;
			case 3:
  				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_INTENSITY );  
				printf("%c",233); /*Ŀ�ĵ�*/
				break;
			case 4:
  				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  3| FOREGROUND_INTENSITY    );  
				printf("%c",232); /*����*/
				break;
			case 7:
  				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  6| FOREGROUND_INTENSITY  );  
				printf("%c",178); /*���ӵ���Ŀ�ĵ�*/
				break;
			case 6:
  				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  7| FOREGROUND_INTENSITY  );  
				printf("%c",239); /*��*/
				break;
			case 9:
				printf("%c",239); /*�˵���Ŀ�ĵ�*/
				break;
			}            
		}
		printf("\n"); 
	}
  	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  14| FOREGROUND_INTENSITY  );  
}
void play(int map[10][12],int counti,int count){
		char input;
		int i,j;
		int times=0;
		int count0=count;/*��¼��ʼ��λ���������������¿�ʼ*/
		int map0[10][12];/*��¼��ʼ��ͼ���������¿�ʼ*/
		for(i=0;i<10;i++){
			for(j=0;j<12;j++){
				map0[i][j]=map[i][j];
			}
		}
		
		while(1)
		{
			system("CLS");/*�����ʾ������*/
		    boxmap(map);
		    printf("You score is  %d\n",count);/*��ʾ�ﵽĿ�ĵص����ӵĸ���*/
		    for (i=0;i<10;i++)
		    {
			    for (j=0;j<12;j++)
				{
				    if (map[i][j]==6||map[i][j]==9)
					    break;
			    }
			    if (map[i][j]==6||map[i][j]==9)
				    break;
		    }       
		    input = getch();/*���ü���WSAD���������������ƶ�����*/
		    switch (input)
		    {
		    	case 'm':	/*�ص�ѡ��˵�*/
		    		system("CLS");
		    		return; 
		    	case 'r':	/*���¿�ʼ*/
		    		for(i=0;i<10;i++){
		    			for(j=0;j<12;j++){
		    				map[i][j]=map0[i][j];
						}
					}
					count=count0;
		    		break; 
		        case 'w':	/*���������������������*/
		        
			    times++;
		        if(map[i-1][j]==1)
		        	movement[0][times]='e',movement[1][times]='u';
			    else{
				if(map[i-1][j]==0)/*��ǰ��Ϊ�յ�*/
				{
				    map[i-1][j]=6+0; /*����ǰ��һ������������������*/
				    if(map[i][j]==9)
					    map[i][j]=3; /*ǰһ����λ�øı�ΪĿ�ĵ�*/
				    else
					    map[i][j]=0;     
				    movement[1][times]='u';
			    }
			    else if((map[i-1][j]==3)||(map[i-1][j]==9))/*�˵�ǰ��ΪĿ�ĵأ�����ͬ��*/
				{
				    map[i-1][j]=6+3; 
				    if(map[i][j]==9) 
					    map[i][j]=3;
				    else
					    map[i][j]=0; 
				    movement[1][times]='u';
			    }
			    else if(map[i-1][j]==4)/*��ǰ�������ӣ�����ǰ���ǿյ�*/
				{
				    if (map[i-2][j]==0)
					{ 
					    map[i-2][j]=4; 
					    if(map[i-1][j]==7) /*����ԭ��ΪĿ�ĵ�*/
						    map[i-1][j]=9;
					    else
						    map[i-1][j]=6; 
					    if(map[i][j]==9)
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
				    else if (map[i-2][j]==3)/*��ǰ�����ӣ�����ǰΪĿ�ĵ�*/
					{ 
					    map[i-2][j]=7;/*����Ŀ�ĵ�*/
					    count++;
					    if(map[i-1][j]==7)
						    map[i-1][j]=9;
					    else
						    map[i-1][j]=6;
					    if(map[i][j]==9)
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				   }
				   movement[1][times]='p';
			    }
			    else if(map[i-1][j]==7)/*��ǰ�ǵ���Ŀ�ĵص�����*/
				{
				    if(map[i-2][j]==0)/*����ǰΪ�յ�*/
					{
					    count--;
					    map[i-2][j]=4; 
					    map[i-1][j]=9;  
					    if(map[i][j]==9) 
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
				    if(map[i-2][j]==3)/*��ǰ�ǵ���Ŀ�ĵص����ӣ�����ǰ����һĿ�ĵ�*/
					{
					    map[i-2][j]=7; 
					    map[i-1][j]=9; 
					    if(map[i][j]==9) 
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
				    movement[1][times]='p';
			    }
			    movement[0][times]='w';
				}
			  
			    break;
		        case 's':
			    times++;
				if(map[i+1][j]==1)
			    	movement[0][times]='e',movement[1][times]='u';
			    else{
				if(map[i+1][j]==0)
			    {
				    map[i+1][j]=6+0; 
				    if(map[i][j]==9) 
					    map[i][j]=3;
				    else
					    map[i][j]=0;    
				    movement[1][times]='u';
			    }
			    else if(map[i+1][j]==3)
			    {
				    map[i+1][j]=6+3;
				    if(map[i][j]==9)
					    map[i][j]=3;
				    else
					    map[i][j]=0;
				    movement[1][times]='u';
			    }
			    else if(map[i+1][j]==4)
			    {
				    if (map[i+2][j]==0)
				    { 
					    map[i+2][j]=4;
					    if(map[i+1][j]==7)
						    map[i+1][j]=9; 
					    else
						    map[i+1][j]=6;
						if(map[i][j]==9) 
							map[i][j]=3; 
						else
							map[i][j]=0; 
				    }
				    else if (map[i+2][j]==3)
				    { 
					    map[i+2][j]=7; 
					    count++;
					    if(map[i+1][j]==7)
						    map[i+1][j]=9;
					    else
						    map[i+1][j]=6;
					    if(map[i][j]==9)
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
				    movement[1][times]='p';
			    }
			    else if(map[i+1][j]==7)
			    {
				    if(map[i+2][j]==0)
				    {
					    count--;
					    map[i+2][j]=4; 
					    map[i+1][j]=9;  
					    if(map[i][j]==9) 
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
				    if(map[i+2][j]==3)
				    {
					    map[i+2][j]=7;  
					    map[i+1][j]=9;  
					    if(map[i][j]==9) 
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
				    movement[1][times]='p';
			    }
				movement[0][times]='s';
				}
			    break;
		        case 'a':
		        times++;
		        if(map[i][j-1]==1)
		        	movement[0][times]='e',movement[1][times]='u';
			    else{
			    if(map[i][j-1]==0)
			    {
				    map[i][j-1]=6+0;
				    if(map[i][j]==9)
					    map[i][j]=3; 
				    else
					    map[i][j]=0;      
					movement[1][times]='u';
			    }
			    else if(map[i][j-1]==3)
			    {
				    map[i][j-1]=6+3; 
				    if(map[i][j]==9) 
					    map[i][j]=3; 
				    else
					    map[i][j]=0;       
					movement[1][times]='u';
			    }
			    else if(map[i][j-1]==4)
			    {
				    if (map[i][j-2]==0)
				    { 
					    map[i][j-2]=4; 
					    if(map[i][j-1]==7) 
						    map[i][j-1]=9; 
					    else
						    map[i][j-1]=6; 
					    if(map[i][j]==9) 
						    map[i][j]=3; 
					    else
						    map[i][j]=0; 
				    }
				    else if (map[i][j-2]==3)
				    { 
					    count++;
					    map[i][j-2]=7;   
					    if(map[i][j-1]==7)
						    map[i][j-1]=9;
					    else
						    map[i][j-1]=6;
					    if(map[i][j]==9)
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }      
					movement[1][times]='p';
			    }
			    else if(map[i][j-1]==7)
			    {
				    if(map[i][j-2]==0)
				    {
					count--;
					map[i][j-2]=4;   
					map[i][j-1]=9;   
					if(map[i][j]==9) 
						map[i][j]=3;
					else
						map[i][j]=0;
				    }
				    if(map[i][j-2]==3)
				    {
					    map[i][j-2]=7;   
					    map[i][j-1]=9;  
					    if(map[i][j]==9) 
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }      
					movement[1][times]='p';
			    }
			    movement[0][times]='a';
				}
			    break;
		        case 'd':
		        times++;
		        if(map[i][j+1]==1)
		        	movement[0][times]='e',movement[1][times]='u';
		        else{
			    if(map[i][j+1]==0)
			    {
				    map[i][j+1]=6+0; 
				    if(map[i][j]==9) 
					    map[i][j]=3; 
				    else
					    map[i][j]=0;       
					movement[1][times]='u';
			    }
			    else if(map[i][j+1]==3)
			    {
				    map[i][j+1]=6+3; 
				if(map[i][j]==9) 
					map[i][j]=3; 
				else
					map[i][j]=0;
				movement[1][times]='u';
			    }
			    else if(map[i][j+1]==4)
			    {
				    if (map[i][j+2]==0)
				    { 
					    map[i][j+2]=4; 
					    if(map[i][j+1]==7)
						    map[i][j+1]=9; 
					    else
						    map[i][j+1]=6; 
					    if(map[i][j]==9) 
						    map[i][j]=3; 
					    else
						    map[i][j]=0; 
				    }
				    else if (map[i][j+2]==3)
				    { 
					    count++;
					    map[i][j+2]=7; 
					    if(map[i][j+1]==7)
						    map[i][j+1]=9;
					    else
						    map[i][j+1]=6;
					    if(map[i][j]==9)
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
					movement[1][times]='p';
			    }
			    else if(map[i][j+1]==7)
			    {
				    if(map[i][j+2]==0)
				    {
					    count--;
					    map[i][j+2]=4;  
					    map[i][j+1]=9;  
					    if(map[i][j]==9) 
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
				    if(map[i][j+2]==3)
				    {
					    map[i][j+2]=7;   
					    map[i][j+1]=9;   
					    if(map[i][j]==9) 
						    map[i][j]=3;
					    else
						    map[i][j]=0;
				    }
					movement[1][times]='p';
			    }
			    movement[0][times]='d';
				}
			    break;
			    case 'q':
			    	if(times==0)
			    		printf("No regret��"); 
			    	else if(movement[0][times]=='w'&&movement[1][times]=='p'){
			    		if(map[i+1][j]==0){ /*�˵��·��ǿյ�*/
							if(map[i-1][j]==4){	/*�˵��Ϸ�������*/
								if(map[i][j]==9)
									map[i][j]=7; 
								else
									map[i][j]=4; 
								map[i-1][j]=0;
								map[i+1][j]=6;
							} 
							else if(map[i-1][j]==7){	/*�˵��Ϸ��ǵ���Ŀ�ĵص�����*/
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i-1][j]=3;
								map[i+1][j]=6;
							}
			  			}
					    else if(map[i+1][j]==3)/*�˵��·���Ŀ�ĵ�*/ 
					    {
						    if(map[i-1][j]==4){	/*�˵��Ϸ�������*/
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4; 
								map[i-1][j]=0;
								map[i+1][j]=9;
							} 
							else if(map[i-1][j]==7){	/*�˵��Ϸ��ǵ���Ŀ�ĵص�����*/
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i-1][j]=3;
								map[i+1][j]=9;
							}
			    		}
			    		times--;
			    	}
			    	else if(movement[0][times]=='s'&&movement[1][times]=='p'){
			    		if(map[i-1][j]==0){ 
			    			if(map[i+1][j]==4){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4; 
								map[i+1][j]=0;
								map[i-1][j]=6;
							} 
							else if(map[i+1][j]==7){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i+1][j]=3;
								map[i-1][j]=6;
							}
			  			}
					    else if(map[i-1][j]==3)
					    {
						    if(map[i+1][j]==4){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4; 
								map[i+1][j]=0;
								map[i-1][j]=9;
							} 
							else if(map[i+1][j]==7){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i+1][j]=3;
								map[i-1][j]=9;
							}
			    		}
			    		times--;
			    	}
			    	else if(movement[0][times]=='a'&&movement[1][times]=='p'){
			    		if(map[i][j+1]==0){ 
			    			if(map[i][j-1]==4){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4; 
								map[i][j-1]=0;
								map[i][j+1]=6;
							} 
							else if(map[i][j-1]==7){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i][j-1]=3;
								map[i][j+1]=6;
							}
			  			}
					    else if(map[i][j+1]==3)
					    {
						    if(map[i][j-1]==4){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4; 
								map[i][j-1]=0;
								map[i][j+1]=9;
							} 
							else if(map[i][j-1]==7){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i][j-1]=3;
								map[i][j+1]=9;
							}
			    		}
			    		times--;
			    	}
			    	else if(movement[0][times]=='d'&&movement[1][times]=='p'){
			    		if(map[i][j-1]==0){ 
			    			if(map[i][j+1]==4){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4; 
								map[i][j+1]=0;
								map[i][j-1]=6;
							} 
							else if(map[i][j+1]==7){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i][j+1]=3;
								map[i][j-1]=6;
							}
			  			}
					    else if(map[i][j-1]==3)
					    {
						    if(map[i][j+1]==4){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4; 
								map[i][j+1]=0;
								map[i][j-1]=9;
							} 
							else if(map[i][j+1]==7){	
								if(map[i][j]==9)
									map[i][j]=7;
								else
									map[i][j]=4,count--; 
								map[i][j+1]=3;
								map[i][j-1]=9;
							}
			    		}
			    		times--;
			    	}
			    	else if(movement[0][times]=='e')
			    		times--;
			    	else if(movement[0][times]=='w'){
			    		if(map[i+1][j]==3)
							map[i+1][j]=9;
						else
							map[i+1][j]=6;
						if(map[i][j]==9)
							map[i][j]=3;
						else
							map[i][j]=0; 
						times--;
					}
			    	else if(movement[0][times]=='s'){
			    		if(map[i-1][j]==3)
							map[i-1][j]=9;
						else
							map[i-1][j]=6;
						if(map[i][j]==9)
							map[i][j]=3;
						else
							map[i][j]=0; 
						times--;
					}
			    	else if(movement[0][times]=='a'){
			    		if(map[i][j+1]==3)
							map[i][j+1]=9;
						else
							map[i][j+1]=6;
						if(map[i][j]==9)
							map[i][j]=3;
						else
							map[i][j]=0; 
						times--;
					}
			    	else if(movement[0][times]=='d'){
			    		if(map[i][j-1]==3)
							map[i][j-1]=9;
						else
							map[i][j-1]=6;
						if(map[i][j]==9)
							map[i][j]=3;
						else
							map[i][j]=0; 
						times--;
					}
			    	break;
			}    		
	 	       if(count==counti)/*ȫ���ﵽĿ�ĵ�*/  
			    {
				    system("CLS");
				    boxmap(map); 
				    break;  
			    }
		}
	printf("\n    You Win\n");
	return;

}
int main(void)
{
	int choice,count,counti;/*ǰ�߼�¼���յ���Ŀ�ĵص����Ӹ��������߼�¼��ǰ�ѵ���Ŀ�ĵ����Ӹ���*/
	int c;
	int level; /*�Ѷ�*/  
	int i,j;
	int mapx[10][12]; 
	system("color 0E");
	printf("*****************PUSHBOX GAME****************\n");
	printf("*               Press 1 to Play             *\n");	
	printf("*                                           *\n");
	printf("*        Press other any keys to Quit       *\n");
	printf("*********************************************\n");
	scanf("%d",&choice);
	if(choice==1){
		begin:
		system("CLS");
		printf("CHOOSE LEVEL:\n1:extremely easy \n2:easy \n3:normal \n4:hard \n\n");
		scanf("%d",&level);
		switch(level){
			case 1:for(i=0;i<10;i++){
				        for(j=0;j<12;j++){
					        mapx[i][j]=map1[i][j];
			         	}
		         	} 	
			        counti=4,count=0,play(mapx,counti,count);
			        printf("1:next level\n2:return to menu\nothers:quit\n\n");
					scanf("%d",&c);
					if(c==2)goto begin;
					if(c!=1)break;
		    case 2:for(i=0;i<10;i++){
				        for(j=0;j<12;j++){
					        mapx[i][j]=map2[i][j];
			         	}
		         	} 
			         counti=3,count=0,play(mapx,counti,count);
		    		 printf("1:next level\n2:return to menu\nothers:quit\n\n");
					 scanf("%d",&c);
					 if(c==2)goto begin;
				     if(c!=1)break;
			case 3:for(i=0;i<10;i++){
				        for(j=0;j<12;j++){
					        mapx[i][j]=map3[i][j];
			         	}
		         	} 
					 counti=4,count=1,play(mapx,counti,count);
					 printf("1:next level\n2:return to menu\nothers:quit\n\n");
					 scanf("%d",&c);
					 if(c==2)goto begin;
				   	 if(c!=1)break;
			case 4:for(i=0;i<10;i++){
				        for(j=0;j<12;j++){
					        mapx[i][j]=map4[i][j];
			         	}
		         	} 
					 counti=6,count=2,play(mapx,counti,count);
					 printf("1:next level\n2:return to menu\nothers:quit\n\n");
					 scanf("%d",&c);
					 if(c==2)goto begin;
					 if(c!=1)break;
		}
		
		system("pause");
	}
	else exit(0);
	return 0;
}
			
