#include<stdio.h>
#include<math.h>
#define MAX 2000
int binary(int num);//ʮ����ת���ɶ����Ƶĺ��� 
void devide(int a,int b,int c,int d);//�ַ��м䲿�ֵĽ��뺯��
void devidehead(int a,int b,int c,int d);//��ͷ���ֵĽ��뺯��
void devidetail(int a,int b,int c,int d);
void devidetail2(int a,int b,int c,int d);//���ֲ�ͬ��β��ʽ�Ľ��뺯�� 
int main()
{
	char base[64]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
	'R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l',
	'm','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6',
	'7','8','9','+','/'	};//����base64���룬�����±��Ӧ��Ӧ���ַ� 
	char a[MAX];
	int i,j,n=0;
	int num[MAX],b[MAX];
	for(i=0;i<MAX;i++){
		scanf("%c",&a[i]);
		n++;
		if(a[i]=='\n') break;
	}
	n=n-1;
	n=n-10;
	for(i=0;i<n;i++){
		a[i]=a[i+10];//��Ѹ�ױ�ʶͷȥ��
    }
    if(a[n-1]=='='){
    	n=n-4;
	}
	
    for(i=0;i<n;i++){
		for(j=0;j<64;j++){
			if(a[i]==base[j]){//���ַ�תΪ��Ӧ������,��תΪ������
				b[i]=binary(j);
			}
		}
	}
	int x,y,z,z0,z1=0;
	if(a[n+3]=='='){
		if(a[n+2]=='='){//�����������ȺŽ�β��������� 
	        devidehead(b[0],b[1],b[2],b[3]);//ȥ����ͷ�����ַ� 
	        for(i=4;i<n-4;i++,i++,i++,i++){
		        devide(b[i],b[i+1],b[i+2],b[i+3]);
        	}
        	devidetail2(b[n-4],b[n-3],b[n-2],b[n-1]);
		}
		else{
			devidehead(b[0],b[1],b[2],b[3]);//ȥ����ͷ�����ַ� 
	        for(i=4;i<n;i++,i++,i++,i++){
		        devide(b[i],b[i+1],b[i+2],b[i+3]);
        	}
		}
	}
	else{
		devidehead(b[0],b[1],b[2],b[3]);//ȥ����ͷ�����ַ� 
	    for(i=4;i<n-4;i++,i++,i++,i++){
		    devide(b[i],b[i+1],b[i+2],b[i+3]);
	    }
	    devidetail(b[n-4],b[n-3],b[n-2],b[n-1]);
	}	
}

int binary(int num)//���庯������ʮ����ת��Ϊ�����Ƶĺ���
{
    int a[8]={0};
    int i=-1,sum=0;
    while(num!=0&&i<=8){
        i++;
        a[i]=num%2;
        num/=2;
    }
    for(i=7;i>=0;i--){
    	sum=sum*10+a[i];
    }
    return sum;
}
void devide(int a,int b,int c,int d)//���庯������Ҫ������м䲿�ֲ�֣���������Ʋ�ֳ����� 
{
	char x,y,z;
	int i,e,f,g,e0,f0,g0,e1=0,g1=0,f1=0;
	g=c%100*1000000+d;
	f=b%10000*10000+c/100;
	e=a*100+b/10000;
	for(i=0;i<8;i++){
		e0=e%10;
		f0=f%10;
		g0=g%10;
		e1=e1+e0*pow(2,i);
		f1=f1+f0*pow(2,i);
		g1=g1+g0*pow(2,i);//������ת����ʮ����
		e=e/10;
		f=f/10;
		g=g/10;
	}
	printf("%c%c%c",e1,f1,g1);
}
void devidehead(int a,int b,int c,int d)//��Ҫ����Ŀ�ͷ���ֲ�֣�ɾ�������ַ�����������Ʋ�ֳ����� 
{
	int i,g,g0,g1=0;
	g=c%100*1000000+d;
	for(i=0;i<8;i++){
		g0=g%10;
		g1=g1+g0*pow(2,i);//������ת����ʮ���� 
		g=g/10;
	}
	printf("%c",g1);
}
void devidetail(int a,int b,int c,int d)//��ͨ��β��ʽ����Ҫ����Ľ�β���ֲ�֣�ɾ�������ַ�����������Ʋ�ֳ�����
{
	int i,e,e0,e1=0;
	e=a*100+b/10000;
	for(i=0;i<8;i++){
		e0=e%10;
		e1=e1+e0*pow(2,i);//������ת����ʮ���� 
		e=e/10;
	}
	printf("%c",e1);
}
void devidetail2(int a,int b,int c,int d)//�����β��ʽ�������������Ⱥţ���Ҫ����Ľ�β���ֲ�֣�ɾ�������ַ�����������Ʋ�ֳ�����
{
	int i,e,f,e0,f0,e1=0,f1=0;
	f=b%10000*10000+c/100;
	e=a*100+b/10000;
	for(i=0;i<8;i++){
		e0=e%10;
		f0=f%10;
		e1=e1+e0*pow(2,i);
		f1=f1+f0*pow(2,i);//������ת����ʮ���� 
		e=e/10;
		f=f/10;
	}
	printf("%c%c",e1,f1);
}
