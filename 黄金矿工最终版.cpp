#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include<time.h>
#define pi 3.14159265358979323846264338327950288
double hookdirection(double t1,double t)
	//输出钩子的方向，以x轴正方向为0

{ 
	double dt=t-t1;
	double a;
	while(dt>6000)
	{
		dt=dt-6000;
	}
	if(dt>3000)
	{
		a=(dt-3000)/3000;
		return pi-pi*a;
	}
	if(dt<=3000)
	{
		a=dt/3000;
		return pi*a;
	}
}

int hookxgo(double t1,double t2,double x,double y,double v, double vg,double hookdirectial)
	//获得单一金块信息，输出钩子在之后一段时间的位置 t2出钩 
{
	double a;
	a=cos(hookdirectial);
	return vg*a*(t2-t1)+275;
}
int hookxback(double t1,double t2,double x,double y,double v, double vg,double hookdirectial)
	//获得单一金块信息，输出钩子在之后一段时间的位置 t2出钩 
{
	double a,b,c;
	a=tan(hookdirectial);
	b=cos(hookdirectial);
	c=sin(hookdirectial);
	return (y-90)/a+275-v*b*(t2-t1-(y-90)/(c*vg));
}

int hookygo(double t1,double t2,double x,double y,double v, double vg,double hookdirectial)
	//获得单一金块信息，输出钩子在之后一段时间的位置 
{
	double a;
	a=sin(hookdirectial);
	return vg*a*(t2-t1)+90;
}
int hookyback(double t1,double t2,double x,double y,double v, double vg,double hookdirectial)
	//获得单一金块信息，输出钩子在之后一段时间的位置 
{
	double a;
	a=sin(hookdirectial);
	return y-a*v*(t2-t1-(y-90)/(a*vg));
}
void CharToTchar (const char * _char, TCHAR * tchar)
	//  将CHAR类型转换为TCHAR
{  
    int iLength ;  
    iLength = MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, NULL, 0) ;  
    MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, tchar, iLength) ;  
}
int judge(double x,double y,float r,double fi)
	//判断是否可以勾到金子
{
	 if(fi<pi/2)
	 {
	 if(fi<=atan((y-90)/(x-275))+asin(r/pow((x-275)*(x-275)+(y-90)*(y-90),0.5))\
		 &&fi>=(atan((y-90)/(x-275)))-(asin(r/pow((x-275)*(x-275)+(y-90)*(y-90),0.5)))) 
		 return 1;
	 else return 0;
	 }
	 if(fi>=pi/2)
	 {
	 	fi=fi-pi;
	 	if(fi<=atan((y-90)/(x-275))+asin(r/pow((x-275)*(x-275)+(y-90)*(y-90),0.5))\
			&&fi>=(atan((y-90)/(x-275)))-(asin(r/pow((x-275)*(x-275)+(y-90)*(y-90),0.5))))
			return 1;
	 else return 0;
	 }
}
int nonehookx(double t1,double t2,double x,double y,double v, double vg,double hookdirectial)
	//获得单一金块信息，输出钩子在之后一段时间的位置 t2出钩 
{
	double a;
	a=cos(hookdirectial);
	if(t2-t1<=468/vg)
	{
		return vg*a*(t2-t1)+275;
	}
	//出勾情况下
	else if(t2-t1>468/vg&&t2-t1<936/vg)
	{
		return (468-vg*(t2-t1-468/vg))*a+275;
	}
	//回勾情况
}
int nonehooky(double t1,double t2,double x,double y,double v, double vg,double hookdirectial)
	//获得单一金块信息，输出钩子在之后一段时间的位置 
{
	double a;
	a=sin(hookdirectial);
	if(t2-t1<=468/vg)
	{
		return vg*a*(t2-t1)+90;
	}
	//出勾情况下
	else if(t2-t1>270/468/vg&&t2-t1<2*468/vg)
	{
		return (468-vg*(t2-t1-468/vg))*a+90;
	}
	//回勾情况
}
///////////////////////////////////
///////////////////////////---------------------------------------主函数入口

int main()
{
	double t1,t,t2;
	//t1为起始时间，t为现在时间 ,t2出钩 
	int i=0,j=0;
	int score=0;
	int y[8]={200,160,300,140,230,200,300,250};
	int x[8]={100,500,450,100,520,200,350,300};
	int value[8]={0};
	//金价值 
	float r[8]={0};
	double v[8]={0};
	//金拉上速度 
	double vg=0.1;
	//出钩速度
	int xg=275,yg=90;
	//钩现在位置，且为原点
	char s1[10]={0};
	char s2[10]={0};
	TCHAR S1[10]={NULL},S2[10]={NULL};
	IMAGE MAN,HOOK,HOOK1,img[10],IMG[8];
    initgraph(600,360);
	//初始化图像
	setbkcolor(BLACK);
	//设置背景为黑色
	getimage(&img[9],0,0,50,50);
	loadimage(&MAN,_T("IMAGE"),_T("MAN"));
	loadimage(&HOOK,_T("IMAGE"),_T("HOOK"),20,20,1);
	//加载图片
	putimage(250,25,&MAN);
    while(i<8)
	{
		switch (i)
		{
			case 0:
				r[i]=30;
				value[i]=500;
				v[i]=0.03;
				loadimage(&IMG[0],_T("IMAGE"),_T("QUESTION"));
				putimage(x[i],y[i],&IMG[0]);
				break;
			case 1:
				r[i]=20;
				value[i]=100;
				v[i]=0.08;
				loadimage(&IMG[1],_T("IMAGE"),_T("GOLD"));
				putimage(x[i],y[i],&IMG[1]);
				break;
			case 2:
				r[i]=30;
				value[i]=20;
				v[i]=0.03;
				loadimage(&IMG[2],_T("IMAGE"),_T("ROCK"));
				putimage(x[i],y[i],&IMG[2]);
				break;
			case 3:
				r[i]=20;
				value[i]=100;
				v[i]=0.1;
				loadimage(&IMG[3],_T("IMAGE"),_T("GOLD"));
				putimage(x[i],y[i],&IMG[3]);
				break;
			case 4:
				r[i]=30;
				value[i]=20;
				v[i]=0.03;
				loadimage(&IMG[4],_T("IMAGE"),_T("ROCK"));
				putimage(x[i],y[i],&IMG[4]);
				break;
			case 5:
				r[i]=30;
				value[i]=20;
				v[i]=0.03;
				loadimage(&IMG[5],_T("IMAGE"),_T("ROCK"));
				putimage(x[i],y[i],&IMG[5]);
				break;	
		    case 6:
				r[i]=30;
				value[i]=50;
				v[i]=0.1;
				loadimage(&IMG[6],_T("IMAGE"),_T("QUESTION"));
			    putimage(x[i],y[i],&IMG[6]);
				break;
            case 7:
				r[i]=20;
				value[i]=100;
				v[i]=0.1;
				loadimage(&IMG[7],_T("IMAGE"),_T("GOLD"));
				putimage(x[i],y[i],&IMG[7]);
				break;
		
	}
		i++;
	}//产生金块
	t1=clock();
	t=clock();
	i=0;
	while(t<t1+60000)
	{//定时一分钟 
    t=clock();
	//记录时间
	if(kbhit())
	{
		    t2=clock();
			//记录出钩时间 
			if(kbhit());
			while(i<8)
			{
				if(judge(x[i],y[i],r[i],hookdirection(t1,t)))
				{
					break;
				}
				if(kbhit());
				i++;
			}
			//判断是否能勾到金子
			t=clock();
			if(kbhit());
			//防止误触
			if(i!=8)
				//能勾上物体
			{
				t=clock();
				while(t<=t2+(y[i]-90)/(sin(hookdirection(t1,t2))*vg)\
					+(y[i]-90)/(sin(hookdirection(t1,t2))*v[i])&&t<t1+60000)
					//放钩
				{
					t=clock();
					if(kbhit());
					if(t-t2<=(y[i]-90)/(sin(hookdirection(t1,t2))*vg))
					{
					putimage(xg,yg,&img[3]);
					xg=hookxgo(t2,t,x[i],y[i],v[i],vg,hookdirection(t1,t2));
				     yg=hookygo(t2,t,x[i],y[i],v[i],vg,hookdirection(t1,t2));
					 getimage(&img[3],xg,yg,20,20);
					rotateimage(&HOOK1, &HOOK,pi/2-hookdirection(t1,t2));
					//钩子的旋转
					 putimage(xg,yg,&HOOK1);
					 setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
					 setlinecolor(WHITE);
					 line(275,90,xg,yg);
					 //设置275.90为原点
					 Sleep(100);
					 //延时
					}
					else if((t-t2)>(y[i]-90)/(sin(hookdirection(t1,t2))*vg)&&\
						(t-t2)<(y[i]-90)/(sin(hookdirection(t1,t2))*vg)+\
						(y[i]-90)/(sin(hookdirection(t1,t2))*v[i]))
						//收钩
					{
					
				    putimage(xg,yg,&img[2]);
					getimage(&img[4],0,0,2*r[i],2*r[i]);
					putimage(x[i],y[i],&img[4]);
					putimage(xg,yg,&img[4]);
				    xg=hookxback(t2,t,x[i],y[i],v[i],vg,hookdirection(t1,t2));
				    yg=hookyback(t2,t,x[i],y[i],v[i],vg,hookdirection(t1,t2));
					 getimage(&img[2],xg,yg,20,20);
					rotateimage(&HOOK1, &HOOK,pi/2-hookdirection(t1,t2));
					//钩子的旋转
					 putimage(xg,yg,&HOOK1);
					 putimage(xg,yg+10,&IMG[i]);
                     setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
					 setlinecolor(WHITE);
					 line(275,90,xg,yg);
					 Sleep(100);
					 setlinecolor(BLACK);
					 //直线覆盖
					 line(275,90,xg,yg);
					for(j=0;j<8;j++)
					{
						 if(j!=i&&x[j]!=0)
						 {
							 putimage(x[j],y[j],&IMG[j]);
						 }

					}
					//恢复被覆盖而未被勾上的金块
						
			    sprintf(s1,"时间:%.1lf",(t1+60000-t)/1000);
				//计时
				CharToTchar(s1,S1);
	            outtextxy(400,10,S1);
				}
			}
				putimage(275,100,&img[9]);
				//使金块消失
				x[i]=0;
				y[i]=0;
				//删除已被勾上的金块
				score+=value[i];	
				sprintf(s2,"分数:%d",score);
				//计分
				CharToTchar(s2,S2);
				outtextxy(400,40,S2);
			}
			else if(i==8)
			{
				t=clock(); 
				while(t<t2+936/vg&&t<t1+60000)
				{
				if(kbhit());
				//防误触
				t=clock();
				putimage(xg,yg,&img[1]);
			    xg=nonehookx(t2,t,x[i],y[i],v[i],vg,hookdirection(t1,t2));
				yg=nonehooky(t2,t,x[i],y[i],v[i],vg,hookdirection(t1,t2));
				//获取钩子的位置
				getimage(&img[1],xg,yg,20,20);
			    rotateimage(&HOOK1, &HOOK,pi/2-hookdirection(t1,t2));
			     putimage(xg,yg,&HOOK1);
				 setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
				 setlinecolor(WHITE);
				line(275,90,xg,yg);
				 Sleep(100);
				 setlinecolor(BLACK);
				 //覆盖直线
			    line(275,90,xg,yg);
				sprintf(s1,"时间:%.1lf",(t1+60000-t)/1000);
				//计时
				CharToTchar(s1,S1);
	            outtextxy(400,10,S1);
				sprintf(s2,"分数:%d",score);
				//计分
	            CharToTchar(s2,S2);
	            outtextxy(400,40,S2);
				}
			}
			i=0;
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			//清空缓存区
		}
	if(!kbhit())
		//无操作钩子摆动的情况
{
    putimage(xg,yg,&img[0]); 
	t=clock();
	//当前时间
	rotateimage(&HOOK1, &HOOK,pi/2-hookdirection(t1,t));
	xg=275+15*cos(hookdirection(t1,t));
	yg=90+15*sin(hookdirection(t1,t));
	getimage(&img[0],xg,yg,20,20);
	putimage(xg,yg,&HOOK1);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	setlinecolor(WHITE);
	line(275,90,xg,yg);
	//画一条直线
	Sleep(100);
	//延时
	setlinecolor(BLACK);
    line(275,90,xg,yg);
	//消除原来的痕迹
	sprintf(s1,"时间:%.1lf",(t1+60000-t)/1000);
	//计时
	CharToTchar(s1,S1);
	outtextxy(400,10,S1);
	sprintf(s2,"分数:%d",score);
	//计分
	CharToTchar(s2,S2);
	outtextxy(400,40,S2);
	if(kbhit())
		{
			putimage(xg,yg,&img[0]);
	}
	//删除停滞的图像
	}
}
	getch();
	return 0;
	}
