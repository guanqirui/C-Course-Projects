/**@author ����� 
  *@version 1.99 build614
  *@name Tetris 
  *@project ZJU_XJC_C_DJ Project3
  *@group G14
  *@brief һ������˹����С��Ϸ 
  */ 
#include "graphics.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


#define DefaultFont 20,0,"΢���ź�"
#define MarkFont 29,0,"΢���ź�"
#define TITLE "G14 Aploium Tetris v1.99 build614"
#define RAWFPS 120
#define FTP_SALT "TtTPVg9rZUkh4t3m"
//#define IS_DEBUG


struct ScoreData{
		int mark,no;
		char name[50];
		char date[25];
	};

const int g_width = 400;
const int g_height = 520;

/*��¼7����״����4�ֱ仯�ı�*/
static int g_trs_map[8][4][4][4];
/*�仯��Ŀ��*/
static int g_map_mod[] = {1, 4, 4, 4, 2, 2, 2, 1, 0};
static float bk_HSL_H = 77.0;
	int nfps = RAWFPS;
    int m_base_x, m_base_y, m_base_w, m_base_h;
    int m_droptime;
    int m_curtime;
    int m_cursubtime;
    int m_movxtime;
    int m_curxtime;

    int m_gamepool_w, m_gamepool_h;
    int m_gamepool[30][30]; //��1Ϊ��ʼ�±꣬0���ڱ߽���ײ���
    int m_ctl_x, m_ctl_y, m_ctl_t, m_ctl_s; //��ǰ���ƿ�����
    float m_ctl_dx, m_ctl_dy;
    int m_next1_s, m_next2_s;
    int m_forbid_down;
    int m_colormap[10];

    int m_pause;
    int m_state; //��Ϸ��״̬
    int m_gray_y;
    int m_over_st;
    int m_Keys[8];
    int m_KeyFlag[8];
    int m_KeyState[8];
	int m_socre=0;

    PIMAGE m_pcb;
        int Trs_map[8][4][4][4] = /*������ʽ�洢��������*/
    {
        {{{0}}},{{
            {0,0,0,0},{1,1,1,0},{0,1,0,0},
        },{
            {0,1,0,0},{1,1,0,0},{0,1,0,0},
        },{
            {0,1,0,0},{1,1,1,0},
        },{
            {0,1,0,0},{0,1,1,0},{0,1,0,0},
        },},{{
            {2,2,0,0},{0,2,0,0},{0,2,0,0},
        },{
            {0,0,2,0},{2,2,2,0},
        },{
            {0,2,0,0},{0,2,0,0},{0,2,2,0},
        },{
            {0,0,0,0},{2,2,2,0},{2,0,0,0},
        },},{{
            {0,3,3,0},{0,3,0,0},{0,3,0,0},
        },{
            {0,0,0,0},{3,3,3,0},{0,0,3,0},
        },{
            {0,3,0,0},{0,3,0,0},{3,3,0,0},
        },{
            {3,0,0,0},{3,3,3,0},
        },},{{
            {4,4,0,0},{0,4,4,0},
        },{
            {0,0,4,0},{0,4,4,0},{0,4,0,0},
        },},{{
            {0,5,5,0},{5,5,0,0},
        },{
            {0,5,0,0},{0,5,5,0},{0,0,5,0},
        },},{{
            {0,0,0,0},{6,6,6,6},
        },{
            {0,0,6,0},{0,0,6,0},{0,0,6,0},{0,0,6,0},
        },},{{
            {0,0,0,0},{0,7,7,0},{0,7,7,0},
        },},
    };
    
    enum {/*״̬��*/
        ST_START, /*��Ϸ���¿�ʼ*/
        ST_NEXT,  /*׼����һ������*/
        ST_NORMAL,/*��ҿ��ƽ׶�*/
        ST_OVER   /*��Ϸ����*/
    };

void initgr();/*ͼ�ν����ʼ��*/
void BkColorSwift();/*���Ʊ�������*/
int InitWelcome();/*���˵���ʼ�������ε���*/
int DotWithin(int x,int y,int n,int bz[][4]);/*�жϵ��Ƿ��������ڣ�����button*/
void InitGame(int w, int h, int bw, int bh);/*��Ϸ��������ʼ��*/
int deal();/*������Ϸ�������*/
bool isCrash();/*�Ƿ�ʧ��*/
void merge();/*deal�����ֹ���ģ��*/
void update();/*�߼����£������������*/
void drawedge(int x, int y, int w, int h, int color, int bdark );/*�����ͼ��*/
void drawtile(int x, int y, int w, int h, int d, int color);/*�����ͼ��*/
void drawframe(int x, int y, int w, int h, int d );/*�����ͼ��*/
void draw44(int bx, int by, int mat[4][4],float dx, float dy, int nc, int deep);/*�����ͼ��*/
void render();/*��Ϸ����ʱ���»��沢����buttons*/
int GameOverProcess();/*����GameOver*/
int QqsortScoreCmp(const void *a,const void *b);/*������*/
void DisplayScoreList(ScoreData	*sdata,int start,int total);/*��ʾ���а�*/
int ShowGlobalHighScore(char *seekname);/*�˵����ȡ����ʾ�������а�*/
void AboutAndThanks();/*About*/
void EmptyMsgQueue();/*������ͼ�����Ϣ����*/
int dealbit(int a, float dt);
int getchangcolor(int Color, float t);

/*��ʼ��ȫ�����ݼ�ͼ����ʾ*/
void initgr() {
//	setinitmode()
	setinitmode(0);
    initgraph(g_width, g_height);
    setcaption(TITLE);
    setfont(12, 6, "����");
    memcpy(g_trs_map, Trs_map, sizeof(Trs_map));
    setbkmode(TRANSPARENT);
}

void BkColorSwift(){
		bk_HSL_H = bk_HSL_H + 0.06;
		setbkcolor(hsl2rgb(bk_HSL_H,0.5,0.5));
}

int InitWelcome(){
		
		int bz[5][4]={/*ButtonZone*/
			{80,92,273,66},
			{10,200,400,80},
			{10,270,400,65},
			{10,340,400,73},
			{130,430,160,70}
		};
  static PIMAGE menu_tetris = newimage(bz[0][2],bz[0][3]),
				menu_start = newimage(bz[1][2],bz[1][3]),
				menu_score = newimage(bz[2][2],bz[2][3]),
				menu_about = newimage(bz[3][2],bz[3][3]),
				menu_exit = newimage(bz[4][2],bz[4][3]),				
				egg_avatar = newimage(128,128);
		static int firstrunflag = 1;
		int currentslect = 1,mousex,mousey,clickflag=0;
		mouse_msg ch;
		
		
		
		if(firstrunflag)
		{
			firstrunflag = 0;
			getimage(menu_tetris,"res\\Tetris.png");/*��ȡ�˵�ͼƬ*/
			getimage(menu_start,"res\\StartNewGame.png");
			getimage(menu_score,"res\\ViewGlobalHighSocre.png");
			getimage(menu_about,"res\\AboutAndThanks.png");
			getimage(menu_exit,"res\\Exit.png");
			getimage(egg_avatar,"res\\avatar.png");	
		}

		
		while(1)
		{
	
			if(mousemsg() && (ch=getmouse()).is_left() && (ch.is_up() || ch.is_down())  )
			{
				currentslect = DotWithin(ch.x,ch.y,5,bz);
				if(currentslect==4) exit(0);
				EmptyMsgQueue(); /*��������Ϣ����*/
				return currentslect;
			}
			else
			{
				mousepos(&mousex,&mousey);
				currentslect = DotWithin(mousex,mousey,5,bz);
			}
			
			BkColorSwift();
			
			cleardevice();
			if(currentslect>0)
				drawframe(bz[currentslect][0],
						bz[currentslect][1],
						bz[currentslect][2] - 20,
						bz[currentslect][3] - 20,
						hsl2rgb(bk_HSL_H+60,0.5,0.5)
						);
			if(currentslect==0)
				putimage(136,50,egg_avatar,SRCCOPY);
			else
				putimage(bz[0][0],bz[0][1],menu_tetris,MERGEPAINT);
			
			
			putimage(bz[1][0],bz[1][1],menu_start,SRCPAINT);
			putimage(bz[2][0],bz[2][1],menu_score,SRCPAINT);
			putimage(bz[3][0],bz[3][1],menu_about,SRCPAINT);
			putimage(bz[4][0],bz[4][1],menu_exit,SRCPAINT);

			delay_fps(nfps);
		}
	}

int DotWithin(int x,int y,int n,int bz[][4]){
	n--;
	for( ;n>=0;n--){
		if(x>=bz[n][0] && x<=bz[n][0]+bz[n][2]
		&& y>=bz[n][1] && y<=bz[n][1]+bz[n][3])
			return n;
	}
	return -1;
}
    
    

   void InitGame(int w, int h, int bw, int bh) {
        int colormap[10] = {0, 0xA00000, 0xA05000, 0xA0A000, 0xC000,
            0x00A0A0, 0x4040C0, 0xA000A0, 0x808080, 0xFFFFFF};
        memcpy(m_colormap, colormap, sizeof(m_colormap));

        int Keys[8] = {VK_F2,VK_LEFT,VK_RIGHT,VK_DOWN,VK_UP,VK_NUMPAD0,VK_SPACE};
        memcpy(m_Keys, Keys, sizeof(Keys));

        memset(m_KeyState, 0, sizeof(m_KeyState));
        m_gamepool_w = w;
        m_gamepool_h = h;
        m_base_w = bw;
        m_base_h = bh;
        m_socre = 0;
		m_pause = 0;
		nfps = RAWFPS;
		
        randomize();
        m_ctl_t = -1;
        m_pcb = newimage();
        for (int i=0; i<10; ++i) {
            drawtile(bw * i, 0, bw, bh, 5, colormap[i]);
        }
        getimage(m_pcb, 0, 0, bw*10, bh);
        m_state = ST_START;
    }
    /*״̬ת������*/
    int deal () {
        int nRet = 0;
        if ( m_state == ST_START ) { //��ʼ�� 
            m_next1_s = random(7) + 1;
            m_next2_s = random(7) + 1;
            m_pause = 0;
            memset(m_gamepool, 255, sizeof(m_gamepool));
            for (int y = 1; y <= m_gamepool_h; ++y) {
                for (int x = 1; x <= m_gamepool_w; ++x)
                    m_gamepool[y][x] = 0;
            }
            m_forbid_down = 0;
            m_ctl_t = -1;
            nRet = 1;
            m_state = ST_NEXT;
        } else if ( m_state == ST_NEXT ) {
            m_ctl_x = (m_gamepool_w - 4) / 2 + 1;
            m_ctl_y = 1;
            m_ctl_t = 0;
            m_ctl_s = m_next1_s;
            m_ctl_dy = 0;
            m_next1_s = m_next2_s;
            m_next2_s = random(7) + 1;
            m_curtime = m_droptime;
            m_curxtime = 0;
            nRet = 1;
            if ( isCrash() ) {
                m_gray_y = m_gamepool_h * 2;
                m_over_st = 0;
                m_state = ST_OVER;
            } else {
                m_state = ST_NORMAL;
            }
        } else if (m_state == ST_NORMAL) {
            /*������������*/
            int i, j;
            if ( m_KeyState[3] == 0 || m_forbid_down) {
                --m_curtime, m_cursubtime = 1;
            }
            if ( m_curxtime ) {
                if (m_curxtime<0)
                    m_curxtime++;
                else
                    m_curxtime--;
            }
            /*��������*/
            for (i = 1, j = 1; i<=2; ++i, j-=2) {
                for ( ; m_KeyFlag[i] > 0; --m_KeyFlag[i]) {
                    m_ctl_x -= j;
                    if ( isCrash() )
                        m_ctl_x += j;
                    else
                        m_curxtime = m_movxtime * j;
                }
            }
            m_ctl_dx = float(double(m_curxtime) / m_movxtime); //����x����ƽ��
            for (i = 4, j = 1; i<=5; ++i, j-=2) {
                for (int t ; m_KeyFlag[i] > 0; --m_KeyFlag[i]) {
                    m_ctl_t=((t=m_ctl_t)+g_map_mod[m_ctl_s]+j)%g_map_mod[m_ctl_s];
                    if ( isCrash() ) m_ctl_t = t;
                }
            }
            if ( m_forbid_down == 0 && (m_KeyState[3] ) ) {
                    m_curtime -= m_cursubtime++;
            }
            if (m_curtime<0) {
                ++m_ctl_y;
                if ( isCrash() ) {
                    --m_ctl_y;
                    merge();
                    m_ctl_dy = 0; m_ctl_dx = 0; m_ctl_t = -1;
                    if ( m_KeyState[3] )
                        m_forbid_down = 1;
                    m_state = ST_NEXT;
                } else {
                    m_curtime += m_droptime;
                }
            }
            if (m_state == ST_NORMAL) {
                m_ctl_dy = float(double(m_curtime) / m_droptime);//����y����ƽ��
            }
        } else if (m_state == ST_OVER) {
            if ( m_gray_y>0 && (m_gray_y % 2) == 0)
                for (int x = 1; x <= m_gamepool_w; ++x)
                    if ( m_gamepool[m_gray_y>>1][x] )
                        m_gamepool[m_gray_y>>1][x] = 8;
            m_gray_y--;
            ++m_over_st;
         //   if ( m_KeyFlag[0] > 0 )
        //        m_state = ST_START;
        }
        memset(m_KeyFlag, 0, sizeof(m_KeyFlag));
        return nRet;
    }
    /*��ײ���*/
    bool isCrash() {
        for (int y=0; y<4; ++y) {
            for (int x=0; x<4; ++x)
                if ( g_trs_map[m_ctl_s][m_ctl_t][y][x] ) {
                    if ( m_ctl_y + y < 0 || m_ctl_x + x < 0
                        || m_gamepool[m_ctl_y + y][m_ctl_x + x])
                        return true;
                }
        }
        return false;
    }
    void merge() {
        int y, x, cy = m_gamepool_h;
        int accu;
        accu = 0;
        /*�ϲ�����*/
        for (y=0; y<4; ++y) {
            for (x=0; x<4; ++x)
                if ( g_trs_map[m_ctl_s][m_ctl_t][y][x] )
                    m_gamepool[m_ctl_y + y][m_ctl_x + x]
                        = g_trs_map[m_ctl_s][m_ctl_t][y][x];
        }
        /*���м���*/
        for (y = m_gamepool_h; y >= 1; --y) {
            for (x = 1; x <= m_gamepool_w; ++x) {
                if ( m_gamepool[y][x] == 0 )
                    break;
            }
            if ( x <= m_gamepool_w ) {
                if ( cy != y ) {
                    for (x = 1; x <= m_gamepool_w; ++x)
                        m_gamepool[cy][x] = m_gamepool[y][x];
                }
                --cy;
                
            }
             
        }
        for (y = cy; y >= 1; --y) {
            for (x = 1; x <= m_gamepool_w; ++x)
                m_gamepool[y][x] = 0;
            accu = !accu ? 1 : 2*accu + 1;
        }
        if(accu) m_socre += (int)(100.0*accu*nfps/RAWFPS);
    }
    /*�߼�����������*/
    void update() {
    	if(m_pause) return; 
        key_msg key;
        int k = kbmsg();
        while ( k ) {
            key = getkey();
            for (int i=0; i<8; ++i) {
                if (key.key == m_Keys[i]) {
                    if (key.msg == key_msg_down) {
                        m_KeyFlag[i]++;
                        m_KeyState[i] = 1;
                    } else if (key.msg == key_msg_up) {
                        m_KeyFlag[i] = 0;
                        m_KeyState[i] = 0;
                        if ( i == 3 )
                            m_forbid_down = 0;
                    }
                }
            }
            k = kbmsg();
        }
        
        
        
        while ( deal() );
    }
    void drawedge(int x, int y, int w, int h, int color, int bdark = 1) {
        setcolor(getchangcolor(color, 1.5f));
        line(x, y+h, x, y);
        lineto(x+w, y);
        if ( bdark )
            setcolor(getchangcolor(color, 0.7f));
        lineto(x+w, y+h);
        lineto(x, y+h);
    }
    void drawtile(int x, int y, int w, int h, int d, int color) {
        w--, h--;
        setfillcolor(color);
        bar(x+1, y+1, x+w, y+h);
        drawedge(x, y, w, h, color);
        drawedge(x+1, y+1, w-2, h-2, color);
    }
    void drawframe(int x, int y, int w, int h, int d = 0) {
        int coll[] = {0x400040, 0x600060, 0xA000A0, 0xFF00FF,
            0xA000A0, 0x600060, 0x400040};
        setfillcolor(!d ? 0x010101 : d);
        bar(x, y, x + w--, y + h--);
        for (int i=0; i<7; ++i) {
            --x, --y, w += 2, h += 2;
            drawedge(x, y, w, h, coll[i], 0);
        }
    }
    void draw44(int bx, int by, int mat[4][4],
        float dx=0, float dy=0, int nc=0, int deep=5) {
        for (int y = 3; y >= 0; --y) {
            for (int x = 0, c; x < 4; ++x) {
                if ( c = mat[y][x] ) {
                    if ( nc ) c = nc;
                    drawtile(int(bx + (x + dx) * m_base_w + 1000.5) - 1000,
                            int(by + (y - dy) * m_base_h + 1000.5) - 1000,
                            m_base_w, m_base_h, deep,
                            m_colormap[c]);
                }
            }
        }
    }
    /*ͼ�θ���������*/
    void render() {
        int x, y, c, bx, by ,currentslect;
        int mousex,mousey; 
		mouse_msg ch;
		int bz[4][4] = {
						{m_base_x-3, m_base_y + 18*m_base_h, 4*m_base_w +5, m_base_h},/*���ز˵�*/
						{m_base_x-3, m_base_y + 16*m_base_h, 4*m_base_w +5, m_base_h},/*��ͣ����*/
						{m_base_x-3, m_base_y + 14*m_base_h, 2*m_base_w -5  , m_base_h},/*1.2x ����*/
						{m_base_x*3+15, m_base_y + 14*m_base_h, 2*m_base_w   , m_base_h} /*0.8x ����*/				
						};
		
        
        cleardevice();
        
        /*����ť��������ť���¼�����ť������ǵ�һ�����Ļ��᲻����˸��ԭ��δ֪*/
        mousepos(&mousex,&mousey);
        currentslect = DotWithin(mousex,mousey,4,bz);
        if( mousemsg() 
			&& ( ch = getmouse()).is_left()  
			&& ch.is_up() )
			{
				switch(currentslect){
					case 0: m_state = ST_OVER; break;
					case 1: m_pause = !m_pause; break;
					case 2: if(!m_pause) nfps = 1.2 * nfps;break;
					case 3: if(!m_pause) nfps = 0.833333 * nfps;break;
				}
				
				
			}

		/*����ť��*/
  		drawframe(bz[0][0],bz[0][1],bz[0][2],bz[0][3],
		  	currentslect==0 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
        outtextxy(bz[0][0]+3 , bz[0][1],"��ֹ�����ز˵�");
        
  		drawframe(bz[1][0],bz[1][1],bz[1][2],bz[1][3],
		  	currentslect==1 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
        outtextxy(bz[1][0]+3 , bz[1][1],m_pause?"������Ϸ":"��ͣ��Ϸ"); 
        
        if(!m_pause){
        	drawframe(bz[2][0],bz[2][1],bz[2][2],bz[2][3],
			  	currentslect==2 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
	        outtextxy(bz[2][0]+3 , bz[2][1],"����");
	        
	        drawframe(bz[3][0],bz[3][1],bz[3][2],bz[3][3],
			  	currentslect==3 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
	        outtextxy(bz[3][0]+3 , bz[2][1],"����");
	    	
        }
	   	    
        xyprintf(bz[2][0]+3 , bz[2][1] -30,"��ǰ�ٶ� %.3fx",(float)nfps/RAWFPS);
        
        
        /*��������*/
        drawframe(  m_base_x + 5 * m_base_w,
                    m_base_y,
                    m_gamepool_w * m_base_w,
                    m_gamepool_h * m_base_h);
        drawframe(m_base_x, m_base_y,              4*m_base_w, 4*m_base_h);
        drawframe(m_base_x, m_base_y + 5*m_base_h, 4*m_base_w, 4*m_base_h);
        

        /*������Ϸ��*/
        bx = m_base_x + 4 * m_base_w;
        by = m_base_y - 1 * m_base_h;
        for (y = m_gamepool_h; y >= 1; --y) {
            for (x = 1; x <= m_gamepool_w; ++x) {
                if ( c = m_gamepool[y][x] )
                        putimage(bx + x * m_base_w, by + y * m_base_h,
                            m_base_w, m_base_h, m_pcb,
                            c * m_base_w, 0);
            }
        }
        /*�����ƿ�*/
        if ( m_ctl_t >=0 ) {
            bx = m_base_x + (m_ctl_x + 4) * m_base_w;
            by = m_base_y + (m_ctl_y - 1) * m_base_h;
            draw44(bx, by, g_trs_map[m_ctl_s][m_ctl_t], m_ctl_dx, m_ctl_dy);
        }
        /*����һ����¶���*/
        bx = m_base_x;
        by = m_base_y;
        draw44(bx, by, g_trs_map[m_next1_s][0]);
        bx = m_base_x;
        by = m_base_y + 5 * m_base_h;
        draw44(bx, by, g_trs_map[m_next2_s][0], 0, 0, 8);
        

        
        /*����ǰ����*/
        setfont(MarkFont);
        setcolor(WHITE);
        xyprintf(148,25,"���� %d",m_socre);
        setfont(DefaultFont);
        

	//	EmptyMsgQueue();/*��������Ϣ����*/
        setcolor(0xFFFFFF);
    }
    int dealbit(int a, float dt) {
        a = int(a * dt);
        if ( a>255 )    a = 255;
        else if ( a<0 ) a = 0;
        return a;
    }
     int getchangcolor(int Color, float t) {
        int r = EGEGET_R(Color), g = EGEGET_G(Color), b = EGEGET_B(Color);
        r = dealbit(r, t);
        g = dealbit(g, t);
        b = dealbit(b, t);
        return EGERGB(r, g, b);
    }



int QqsortScoreCmp(const void *a,const void *b){
	int temp; 
	temp = ((ScoreData *)b)->mark - ((ScoreData *)a)->mark; /*���Ȱ��շ�������*/
	if(temp) 
		return temp;
	else /*������ʱ���ɽ���*/
		return strcmp(((ScoreData *)b)->date , ((ScoreData *)a)->date);
}

int ShowGlobalHighScore(char *seekname = NULL){
	FILE *fp;
	int bz[5][4]={ /*��ť����*/
		{15,450,70,25}, /*��һҳ*/
		{100,450,70,25}, /*��һҳ*/
		{185,450,70,25}, /*���ص�һҳ*/
		{270,450,100,25}, /*��������*/
		{143,487,100,25} /*���ز˵�*/
	};
	int trycount=2500,n,i=0,j,currentpage=0;
	int mousex,mousey,currentslect,lastselect=-2,searchFlag=0;
	mouse_msg ch;
	ScoreData *sdata,*ssearch;
	char cmdbuff[255];
	
	setfont(30,0,"����");
	setcolor(BLACK);
	sprintf(cmdbuff,"start TetrisNet.exe 0 %s",FTP_SALT);
#ifdef IS_DEBUG
	printf("%s\n",cmdbuff);
#endif
	system(cmdbuff);
	while(trycount--){
		cleardevice();
		outtextxy(25,trycount/6.25,"������������ӻ�����Ҫʮ����");
		outtextxy(25,400-trycount/6.25,"���ڴӷ�������ȡ����");
		delay_fps(120);
		BkColorSwift();
		if(trycount % 50 != 0) continue;
		if(fp = fopen("doing.txt","r"))
			{
				fclose(fp);
			}
		else break;
	}
	fclose(fp);
	if(!trycount) return 1;
#ifdef IS_DEBUG
	printf("trycount = %d\n",trycount);
#endif

	
	if((fp = fopen("ScoreOnline.txt","r"))==NULL)
		return 1; 
	cleardevice();
	fscanf(fp,"%d",&n);
	if(n<=0) return 1;
#ifdef IS_DEBUG
	printf("n = %d\n",n);
//	system("pause");
#endif
	
	sdata = (ScoreData *)malloc(sizeof(ScoreData)*(n+10));
	memset((void *)sdata,0,n+10);
	
	while(!feof(fp)){  /*��ȡ��¼�ļ�*/
		fscanf(fp,"%d %s %s",&(sdata[i].mark),&(sdata[i].name),&(sdata[i].date));
//#ifdef IS_DEBUG
//	printf("%d  %s %s",(sdata[i].mark),(sdata[i]).name,(sdata[i]).date);
//	system("pause");
//#endif
		i++;
	}
	system("start TetrisNet.exe 1");
	setfont(20,0,"����");
//	xyprintf(5,500,"���ݶ�ȡ�ɹ����� %d ����¼",i);
//	delay_fps(5);
	
	fclose(fp);
	qsort((void *)sdata,i,sizeof(ScoreData),&QqsortScoreCmp);
	for(j=0;j<i;j++)
		sdata[j].no = j+1;

	EmptyMsgQueue();
	while(1){/*ע��:����һ��˶���while*/
		mousepos(&mousex,&mousey);
		currentslect = DotWithin(mousex,mousey,5,bz);
	 	if( seekname || mousemsg() 
			&& ( ch = getmouse()).is_left()  
			&& ch.is_up() )/*������������*/
				{
			 		lastselect = -2;/*ǿ���ػ�*/
					switch(currentslect){
						case 0: if(currentpage>=10)  currentpage -= 10;  break;
						case 1: if(currentpage<i-10)  currentpage += 10;  break;
						case 2: currentpage = 0; searchFlag = 0;break;
						case 3: if(!seekname) /*�����ⲿ��ѯ����������*/
									inputbox_getline("��������������","������ȫ���򲿷֣����ִ�Сд���س�ȷ�ϡ�\n(ֻ��ʾǰ10�����)",
										cmdbuff,20);
								searchFlag = 0;
								ssearch = (ScoreData *)malloc(sizeof(ScoreData)*20);/*�����10����ֹ���*/
								for(j=0;j<i && searchFlag<=10;j++){ /*����������*/
									if(strstr(sdata[j].name,cmdbuff))
										{
											memcpy(ssearch+searchFlag,sdata+j,sizeof(ScoreData));
											searchFlag++;
											#ifdef IS_DEBUG
											printf("No.%d  %d   %s   %s\n",sdata[i].no,sdata[i].mark,sdata[i].name,sdata[i].date);
											#endif	
										}
								}
							/*searchFlag=
							 *		   -1: ��ѯ�����ʾ�ڼ䡣
							 *				 ��ʱhover��ť��ˢ��(Ҳû����Ч)
					 		 *				 ���ڵ����ť��ˢ�� 
							 *			0: ������������ 
							 *		   >0: ��ʾ�������Ľ������Ҳ���ڱ��ˢ��һ��
							 **/
							if(searchFlag == 0)
							{
								 xyprintf(57,400,"����""%s""û�з��ֽ��:(",cmdbuff);
								 delay_ms(2000);
							}
							seekname = NULL;
							break;
						case 4:return 0;
				}/*EndOfSwitch*/
				EmptyMsgQueue();
				
			}
			
		/*---------���Ʋ˵�-------*/ 
		if(currentslect != lastselect && searchFlag!=-1)/*�����hover״̬û�з����ı����ػ�*/
		{
			cleardevice();
			lastselect = currentslect; 
			#ifdef IS_DEBUG
			printf("currentpage = %d\n",currentslect);
			#endif
			/*����ť��*/
			if(currentpage>=10 && !searchFlag) /*��ҳ���ѯҳ��������һҳ*/
			{
				drawframe(bz[0][0],bz[0][1],bz[0][2],bz[0][3],
				  	currentslect==0 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
		        outtextxy(bz[0][0]+3 , bz[0][1],"��һҳ");
			}
	
	        if(currentpage<i-10 && !searchFlag){ /*ĩҳ���ѯҳ��������һҳ*/
				drawframe(bz[1][0],bz[1][1],bz[1][2],bz[1][3],
				  	currentslect==1 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
		        outtextxy(bz[1][0]+3 , bz[1][1],"��һҳ");
	        }
	        
			drawframe(bz[2][0],bz[2][1],bz[2][2],bz[2][3],
	 			currentslect==2 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
	      	outtextxy(bz[2][0]+3 , bz[2][1],searchFlag?"�����а�":"�ص�һҳ");
	      	
	      	if(!searchFlag){ /*��ѯҳ����ʾ*/
			drawframe(bz[3][0],bz[3][1],bz[3][2],bz[3][3],
	 			currentslect==3 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
	      	outtextxy(bz[3][0]+3 , bz[3][1],"�����ֲ���");
	      	
	      	xyprintf(57,400,"һ���� %d ����¼:)",i);
	      	}
			
			drawframe(bz[4][0],bz[4][1],bz[4][2],bz[4][3],
	 			currentslect==4 ? hsl2rgb(bk_HSL_H+60,0.5,0.5) : getbkcolor());
	      	outtextxy(bz[4][0]+3 , bz[4][1],"������ҳ");
			
			if(!searchFlag)
				DisplayScoreList(sdata,currentpage,n);
			else
			{
				DisplayScoreList(ssearch,0,searchFlag);
				searchFlag = -1;/*�˺���ʱ����hover�ػ�*/
				free(ssearch);
			}
		}
		/*������������ʱ*/
		BkColorSwift();
		delay_fps(nfps);
	}
	
}



/*�����а�*/
void DisplayScoreList(ScoreData	*sdata,int start,int total){
	int x,y,i;

	setfont(23,0,"΢���ź�");
	outtextxy(20,20,"         ����        ����            ����");
	for(i=start;i<start+10 && i<total;i++){
		xyprintf(20,60+(i-start)*35,"No.%d %4d %9s%22s",sdata[i].no,sdata[i].mark,sdata[i].name,sdata[i].date);
#ifdef IS_DEBUG
	printf("No.%d  %d   %s   %s\n",sdata[i].no,sdata[i].mark,sdata[i].name,sdata[i].date);
#endif
	}
}

int GameOverProcess(){
	
	int trycount=1600;	
	if(m_socre == 0) return 0;
	cleardevice();
	char *name = (char *)malloc(50*sizeof(char));
	char *cmdbuff = (char *)malloc(255*sizeof(char));
	int i;
	do{
		inputbox_getline("���������Ĵ���!","���ķ����ᱻ��¼���ϴ�����������\n������20������\n�������пո�Tab�͸�̾��\n\n���س�ȷ��",
		name,20);
	}while(strchr(name,' ') || strchr(name,'\t') || strchr(name,'\n') || strchr(name,'!') );
	EmptyMsgQueue();
	FILE *fp;
	time_t tme=time(NULL);
	fp = fopen("score.txt","a+"); 
	fprintf(fp,"%d %s %s\n",m_socre,name,ctime(&tme));
	fclose(fp);
	
	sprintf(cmdbuff,"start TetrisNet.exe %d %s %s",m_socre,name,FTP_SALT);
	system(cmdbuff);
#ifdef IS_DEBUG
	printf("%s\n",cmdbuff);
#endif
	setfont(34,0,"����");
	while(trycount--){
		cleardevice();
		outtextxy(30,trycount/4,"�������Ӳ��ϴ�������¼");
		delay_fps(120);
		BkColorSwift();
	}
	EmptyMsgQueue();
	ShowGlobalHighScore();
	free(name);
	free(cmdbuff);
	return 1;
}

void AboutAndThanks(){
	
	cleardevice();
	setfont(35,0,"΢���ź�");
	drawframe(10,10,g_width-20,g_height-20,getbkcolor());
	outtextxy(20,20,"��������Aploium��д");
	outtextxy(20,80,"Logo��TETRISʹ����");
	outtextxy(20,110,"   dungeon����");
	outtextxy(20,140,"�˵�ʹ����Celestial����");
	outtextxy(20,170,"InputBox���ֵĴ�����Դ������");
	outtextxy(20,200,"����ʹ����AHK����,���Լ���д");
	outtextxy(20,230,"   �洢���ݵķ����������Լ���");
	outtextxy(20,260,"��������ѭGPLv2 license");
	outtextxy(20,290,"��л����ʹ��");
	outtextxy(20,330,"��ӭ�����ҵĸ�����վ:");
	setfont(45,0,"΢���ź�"); 
	outtextxy(50,390,"www.aploium.com");
	setfont(DefaultFont);
	EmptyMsgQueue();
	while(1){
		BkColorSwift();
		if(kbhit())  return;
		delay_fps(nfps);
	}
	
}

void EmptyMsgQueue(){
	while(mousemsg()) getmouse();
	//while(kbhit()) getch();
	while(kbmsg()) getkey();
}

//#ifdef IS_DEBUG
//int main(){
//#endif
#ifndef IS_DEBUG
int WinMain(){
#endif    
    int over_Flag=60;
    initgr();
    
   // fps ui_fps;
    setlocale(LC_ALL,"");
    m_base_x = 20;
    m_base_y = 20;
    m_droptime = nfps / 2;
    m_movxtime = 10;
    setrendermode(RENDER_MANUAL);
    InitGame(10, 20, 24, 24);
    while(1){
    	switch(InitWelcome()){
	    	case 1:    
				EmptyMsgQueue(); 
				for ( ; is_run(); delay_fps(nfps)) {

							
					        update();
					        render();
					        if(m_state == ST_OVER)	
						        {
						        	nfps = RAWFPS; 
						        	for(over_Flag=120;over_Flag>0;over_Flag--)
						        	{/*GameOverʱ����һ�*/
						        	update();
						        	render();
									delay_fps(nfps/2);        							
	        						}
						        	//delay_ms(1000);
						        	
									GameOverProcess(); 
	        						InitGame(10, 20, 24, 24);
	        						EmptyMsgQueue();
									break;	
	        					}
								//else
							//		over_Flag++;	        
					    }
			    break;
 			case 2: ShowGlobalHighScore();EmptyMsgQueue();break;
 			case 3: AboutAndThanks();EmptyMsgQueue();break; 
	    }

    }
    

    

    return 0;
}

