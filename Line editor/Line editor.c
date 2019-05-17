#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define M 100	/*ÿ���������M���ַ�*/ 
#define N 10	/*ÿҳ�����ʾN��*/ 
int cx = 4;/*��������*/
int cy = 0;/*���������*/ 
int line=1;/*��ǰ�Ѵ�������Ч��������*/
int lineloc=1;/*��ӡ������*/ 
int page=1;/*��ǰ�Ѵ�����ҳ��*/
int pageloc=1; 		/*ҳ��ͣ����ҳ��*/
typedef struct list
{
	char textline[M];
	struct list *next;
} list;

void SetColor(int color) /* �����ı������ɫ */ 
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutput, color);
}			

void gotopos(int x, int y)	/* ���ù��λ�� */ 
{
	COORD loc = {x, y};
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,loc);
}

void erase(int x, int y, int w)/* �����ı� */ 
{
	int k;
	gotopos(x, y);
	for( k=0; k<w; k++ ) printf(" ");
}

list *textsto(char *filename,list *head) /*���ı�text.txt��������*/ 
{
	list *p,*tail;
	FILE *fp;
	int i;
	
	p=(list*)malloc(sizeof(list));
	p->next=NULL;
	tail=head;
	
	if((fp=fopen(filename,"r+"))==NULL){
		gotopos(0,17);
		printf("Open failure!");
		gotopos(0,0);
		return head;
	}
	
	while(!feof(fp)){
		fgets(p->textline,M,fp);  /*���ж�������*/ 
		if(head==NULL)
			head=p;
		else
			tail->next=p;
		tail=p;
		p=(list*)malloc(sizeof(list));
		p->next=NULL;
		if(ferror(fp)){
			gotopos(0,17);
			printf("Read failure!");
			gotopos(0,0);
			return head;
		}
	}
	
	fclose(fp);
	strcat(tail->textline,"\n");
	return head;
}

void textprint(list *head) /*��ӡ�ı�*/ 
{
	list *p;
	
	system("CLS");
	gotopos(0,0);
	lineloc=1;
	
	gotopos(0,19);
	SetColor(4| FOREGROUND_INTENSITY );
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
	gotopos(0,20);
	SetColor(6| FOREGROUND_INTENSITY );
	printf("help:\n");
	printf("up:�� left:��  down:�� right:��\n");
	printf("last page:a    next page:s\n");
	printf("delete the pointed line:dd  or <x>dd to delete x lines  \n");
	printf("line move forward:l or <x>l to move x lines \n");
	printf("line move afterward:L or <x>L to move x lines  \n");
	printf("add chars before:i   after:f  correct chars:c  \n");
	printf("insert a line before:O  after:o  \n");
	printf("enter cmd: :  \n-->1.exchange two lines:m <line1> <line2>  2.open a file:o <filename>\n");
	printf("3.save to a file:w <filename>\n");
	SetColor(15| FOREGROUND_INTENSITY );
	gotopos(0,0);
	
	if(head==NULL)
		return;
	for(p=head;p!=NULL;p=p->next){
		SetColor(11| FOREGROUND_INTENSITY );
		printf("%d | ",lineloc++);
		SetColor(15);
		printf("%s",p->textline);
		if(lineloc==10){
			p=p->next;
			SetColor(11| FOREGROUND_INTENSITY );
			printf("%d| ",lineloc++);
			SetColor(15);
			printf("%s",p->textline);
			while(p->next!=NULL){   /*ȷ��������*/
				lineloc++;
				if(p->next!=NULL)
					p=p->next;
				else
					;
			}
			lineloc--;
			break;
		}
	}
	gotopos(cx,cy);
	return;
}


list* start() /*��ʼʱ����ʹ�ӡ�ı�*/
{
	list *head=(list *)malloc(sizeof(list));
	char filename[100];
	
	system("CLS");
	printf("Enter the filename(like a.txt):");
	scanf("%s",&filename);
	
	head=NULL;
	head=textsto(filename,head);
	textprint(head);
	line=lineloc;
	page=(line-1)/10 +1;
	
	gotopos(0,18);
	SetColor(49| FOREGROUND_INTENSITY|120 );
	printf("                                     Page:%d/%d",pageloc,page);
	SetColor(15| FOREGROUND_INTENSITY);
	gotopos(cx,cy);
	
	return head;
}

list* findynode(int y,list *head)	/*���ҵ�y��*/
{
	list *p;
	int i=1;
	
	p=head;
	while(p!=NULL&&i<y){
		p=p->next;
		i++;
	} 
	if(i==y)
		return p;
	else{
			gotopos(0,17);
			printf("Delete failure!");
			gotopos(cx,cy);
			return NULL;
	}
} 

void pageprint(list* head){   /*�����Ĵ�ӡ�����������һЩBug���������*/
	list *p;
	int endofpage; 
	
	system("CLS");
	gotopos(0,18);
	SetColor(49| FOREGROUND_INTENSITY|120 );
	printf("                                     Page:%d/%d",pageloc,page);
	gotopos(0,19);
	SetColor(4| FOREGROUND_INTENSITY );
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
	gotopos(0,20);
	SetColor(6| FOREGROUND_INTENSITY );
	printf("help:\n");
	printf("up:�� left:��  down:�� right:��\n");
	printf("last page:a    next page:s\n");
	printf("delete the pointed line:dd  or <x>dd to delete x lines  \n");
	printf("line move forward:p or <x>p to move x lines \n");
	printf("line move afterward:P or <x>P to move x lines  \n");
	printf("add chars before:i   after:f  correct chars:c  \n");
	printf("insert a line before:O  after:o  \n");
	printf("enter cmd: :  \n-->1.exchange two lines:m <line1> <line2>  2.open a file:o <filename>\n");
	printf("3.save to a file:w <filename>\n");
	SetColor(15| FOREGROUND_INTENSITY );
	gotopos(0,0);
	
	lineloc=(pageloc-1)*10+1;
	endofpage=(pageloc-1)*10+10;
	p=findynode((pageloc-1)*10+1,head);
	
	if(p==NULL)
		return;
	for(p;p!=NULL;p=p->next){
		if(lineloc>line||lineloc>endofpage)
			break;
			
		SetColor(11| FOREGROUND_INTENSITY );
		if(lineloc==10)		/*Ϊ����ʾ�ĶԳ�����*/
			printf("%d| ",lineloc++ );
		else
			printf("%d | ",lineloc++ );
		SetColor(15);
		printf("%s",p->textline);
	} 
	
	gotopos(cx,cy);
	return;
}

list* deleteline(int y,list *head)	/*ɾ����y��,��Ӧ��������Ϊdd*/ 
{
	list *p,*s;
	p=s=head;
	
	if(head==NULL){
		gotopos(0,17);
		printf("No line exist!");
		gotopos(cx,cy);
		return NULL;
	}
	if(y==1){
		s=head;
		head=head->next;
		free(s);
	}
	else{
		if(y<=line&&y>0)
			p=findynode(y-1,head);
		else{
			gotopos(0,17);
			printf("Delete failure!");
			gotopos(cx,cy);
		}
		s=p->next;
		p->next=s->next;
		free(s);
	}
	line--;
	page=(line-1)/10 +1;
	
	pageprint(head); 
	
	return head;
}

list* addline(int y,list* head)	/*�ڵ�y��ǰ�����һ���У���Ӧ��������Ϊo��ǰ����O����*/
{
	list *p,*s,*c; 
	p=s=head;
/**/ 
	if(y>line)
		return head;
	if(head==NULL){
		p=(list*)malloc(sizeof(list));
		p->next=NULL;
		head->next=p;
	} 
	else if(y==0){
		p=(list*)malloc(sizeof(list));
		strcpy(p->textline,"\n");
		p->next=head;
		head=p;
	}
	else{
		p=findynode(y,head);
		s=(list*)malloc(sizeof(list));
		strcpy(s->textline,"\n");
		s->next=p->next;
		p->next=s;
	}
	line++;
	page=(line-1)/10 +1;
	
	pageprint(head);
	
	return head;
}

void leftpage(list *head)	/*����ҳ*/
{
	pageloc--;
	pageprint(head);
	
	return;
}
void rightpage(list *head) /*���ҷ�ҳ*/ 
{
	pageloc++;
	pageprint(head);
	
	return;
}

list* backwordline(int y,list *head)	/*����y������ƶ�һ�У���Ӧ��������Ϊl��L*/
{
	list *p,*s,*q;
	p=s=head;
	
	if(y>line)
		return head;
	if(y==0){
		return head;
	}
	else if(y==1){
		p=head->next;
		head->next=p->next;
		p->next=head;
		head=p;
		pageprint(head);
	}
	else if(y==line){
		head=addline(y-1,head);
		pageprint(head);
		return head;
	}
	else{         //�����ڶ��д���BUG 
		p=findynode(y-1,head);
		s=p->next;
		q=s->next;
		s->next=q->next;
		p->next=q;
		q->next=s;
		pageprint(head);
	}
	
	return head;
}

list* movelines(list *head,int x1,int x2)	//����x1�к�x2�н�������Ӧ����Ϊm x1 x2 
{
	list *tail1,*tail2,*p1,*p2;
	int change;
	
	if(x1>x2){	//ʹx1<x2��д������� 
		change=x1;
		x1=x2;
		x2=change;
	}
	
	if(x2-x1==1){
		head=backwordline(x1,head);
		pageprint(head);
	}
/**/ 
	else if(x1==1){
		p1=head;
		tail2=findynode(x2-1,head);
		p2=findynode(x2,head);
		tail2->next=p2->next;
		p2->next=p1->next;
		head=p2;
		p1->next=tail2->next;
		tail2->next=p1;
		
		pageprint(head);
	}
	else{
		tail1=findynode(x1-1,head);
		tail2=findynode(x2-1,head);
		p1=findynode(x1,head);
		p2=findynode(x2,head);
		tail2->next=p2->next;
		tail1->next=p1->next;
		p2->next=tail1->next;
		tail1->next=p2;
		p1->next=tail2->next;
		tail2->next=p1;
		pageprint(head);
	}
	
	
	return head;
} 

list *addtext(int x,int y,list *head)	//��ʼ�����ı��������뵽��ǰλ�õ�����֮��ֱ����ESC����,��Ӧ����Ϊf��i 
{
	list *p;
	char ch;
	int i=0;
	
	while((ch=getch())!=27){  
		p=findynode(y,head);
		for(i;p->textline[i]!='\0';i++);
			i++;
		for(i;i>x;i--)
			p->textline[i]=p->textline[i-1];
		p->textline[x]=ch;
		pageprint(head);
		x++;
	}
	return head;
}

list *changetext(int x,int y,list *head)	//��ʼ���벢�޸Ķ�Ӧ���ı�(ֻ���޸��Ѵ��ڵ��ı�)��ֱ����ESC����,��Ӧ����Ϊc 
{
	list *p,*s;
	char ch;
	int i=0;
	
	while((ch=getch())!=27){
		p=findynode(y,head);
		if(p->textline[x]!='\n'){
			p->textline[x]=ch;
			pageprint(head);
			x++;
		} 
	}
	return head;
}

void textsave(list *p)		//�����ı��ļ� 
{
	char filename[100];
	FILE *fp;
	
	erase(0,16,20);
	erase(0,17,20);
	gotopos(0,16);
	printf("Enter the filename you want to save to(like a.txt):\n");
	scanf("%s",&filename);
	
	if((fp=fopen(filename,"w+"))==NULL){
		gotopos(0,17);
		printf("Open failure!");
		gotopos(0,0);
		return;
	}
	while(p){
		fwrite(p->textline,strlen(p->textline),1,fp);
		p=p->next;
	}
	
	fclose(fp);
	return;
}

int main()
{
	list *head;
	int ch;  
	int i,k; /*����һЩ�ظ�����ʱ���ڼ���*/ 
	int x1,x2;	/*�������ƶ�ʱ���ñ���*/
	
	SetConsoleOutputCP(936);
	head=start();	/*�õ��洢��Ϻ������ͷ*/
	
	gotopos(0,19);
	SetColor(4| FOREGROUND_INTENSITY );
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
	SetColor(15| FOREGROUND_INTENSITY );
	gotopos(cx,cy);
	
	while((ch=getch())!='q'){
		switch(ch){
			case 72: //��
				if( cy>0 ) gotopos(cx, --cy);
				break;
			case 80: //��
				if( (pageloc<page&&cy<9)||(pageloc==page&&cy<line-10*(page-1)-1)) 
					gotopos(cx, ++cy);
				break;
			case 75: //��
				if( cx>4 ) gotopos(--cx, cy);
				break;
			case 77: //��
				if( cx<=M+4 ) gotopos(++cx, cy);
				break;
			case 'd':	//ɾ����ǰ�� 
				if((ch=getch())=='d'&&(pageloc<page&&cy<9)||(pageloc==page&&cy<line-10*(page-1)-1))
					head=deleteline(cy+1+10*(pageloc-1),head);
				break;
			case 'L':	//����ǰ�������ƶ�һ�� 
				head=backwordline(cy+1+10*(pageloc-1),head);
				break;
			case 'l':	//����ǰ����ǰ�ƶ�һ�� 
				head=backwordline(cy+10*(pageloc-1),head);
				break;
			case 'i':	//��ʼ�����ı��������뵽��ǰλ�õ�����֮ǰ��ֱ����ESC����
				head=addtext(cx-4,cy+1+10*(pageloc-1),head);
				break;
			case 'f':	//��ʼ�����ı��������뵽��ǰλ�õ�����֮��ֱ����ESC����
				head=addtext(cx-3,cy+1+10*(pageloc-1),head);
				break;
			case 'c':	//��ʼ���벢�޸Ķ�Ӧ���ı���ֱ����ESC���� 
				head=changetext(cx-4,cy+1+10*(pageloc-1),head);
				break;
			case 49:case 50:case 51:case 52:case 53:case 54:case 55:case 56:case 57:	//��ʾ1-9�⼸������
				k=ch-48; 	//����1-9������
				ch=getch();
				switch(ch){
					case 'd':	//ɾ���ӵ�ǰ�п�ʼ��k�� 
						if((ch=getch())=='d'&&cy<line-10*(page-1))
							for(i=1;i<=k;i++){
								head=deleteline(cy+1+10*(pageloc-1),head);
							}
						break;
					case 'L':	//����ǰ�������k�� 
						for(i=0;i<k;i++)
							head=backwordline(cy+1+10*(pageloc-1)+i,head);
						break;
					case 'l':	//����ǰ����ǰ��k��       //�ƶ����һ��ʱҲ����bug 
						for(i=0;i<k;i++)
							head=backwordline(cy+10*(pageloc-1)-i,head); 
						break;
				}
				break;
			case 'o':	/*�ڵ�ǰ�еĺ������һ������*/ 
				head=addline(cy+1+10*(pageloc-1),head);
				break;
			case 'O':	/*�ڵ�ǰ�е�ǰ�����һ������*/
				head=addline(cy+10*(pageloc-1),head);
				break;
			case 'a':	/*����ҳ*/
				if(pageloc>1)
					leftpage(head);
				break;
			case 's':	/*���ҷ�ҳ*/
				if(pageloc<page)
					rightpage(head);
				break;  				
			case ':':	/*������ģʽ*/
				gotopos(0,16);
				printf("Enter command:");
				gotopos(0,17); 
				while((ch=getche())!='q'){
					switch(ch){
						case 'm':	/*�����л�λ*/ 
							printf(" ");
							scanf("%d%d",&x1,&x2);
							if(x1==x2)
								;
							else if(x1<=line&&x2<=line&&x1>0&&x2>0)
								movelines(head,x1,x2);
							else
								printf("Selection error!");
							gotopos(0,16);
							printf("Enter command:");
							erase(0,17,20);
							gotopos(0,17);
							break;
						case 'o':	/*��ָ���ļ�*/ 
							head=start();
							gotopos(0,16);
							printf("Enter command:");
							erase(0,17,20);
							gotopos(0,17);
							break;
						case 'w':	/*�����е���Ϣ����ָ���ļ�*/ 
							textsave(head);
							erase(0,16,100);
							gotopos(0,16);
							printf("Enter command:");
							erase(0,17,20);
							gotopos(0,17);
							break;
						case '\b':	/*�������*/ 
							erase(0,17,20);
							gotopos(0,17);
							break;
					}
				}
				erase(0,16,20);
				erase(0,17,20);
				gotopos(cx,cy);
				break;
		}
	}
	gotopos(0,13);

	return 0;
}
