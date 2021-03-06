// EasyX_Test.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <process.h>
//using namespace std;


bool gameRuning;
extern void init();
extern int readHeadAngle();
extern int readHeadX();
extern int readHeadY();
extern void writeHeadAngle(int ang);
extern void drawAll();
extern void frameAction();
#define Pi 3.1415926535
IMAGE background, probe1, probe2, probe3, probe4, probe5, probe6, probe7, probe8, probe9, probe10, probe11, probe12, probe13, probe14, probe15, probe16, probe17, probe18, probe19, probe20, probe21, probe22, probe23, probe24, probe25, probe26, probe27, probe28, probe29, probe30, probe31;

void readImage() {

	loadimage(&background, _T("D://1.jpg"));
	loadimage(&probe1, _T("probe1.bmp"));
	loadimage(&probe2, _T("probe2.bmp"));
	loadimage(&probe3, _T("probe3.bmp"));
	loadimage(&probe4, _T("probe4.bmp"));
	loadimage(&probe5, _T("probe5.bmp"));
	loadimage(&probe6, _T("probe6.bmp"));
	loadimage(&probe7, _T("probe7.bmp"));
	loadimage(&probe8, _T("probe8.bmp"));
	loadimage(&probe9, _T("probe9.bmp"));
	loadimage(&probe10, _T("probe10.bmp"));
	loadimage(&probe11, _T("probe11.bmp"));
	loadimage(&probe12, _T("probe12.bmp"));
	loadimage(&probe13, _T("probe13.bmp"));
	loadimage(&probe14, _T("probe14.bmp"));
	loadimage(&probe15, _T("probe15.bmp"));
	loadimage(&probe16, _T("probe16.bmp"));
	loadimage(&probe17, _T("probe17.bmp"));
	loadimage(&probe18, _T("probe18.bmp"));
	loadimage(&probe19, _T("probe19.bmp"));
	loadimage(&probe20, _T("probe20.bmp"));
	loadimage(&probe21, _T("probe21.bmp"));
	loadimage(&probe22, _T("probe22.bmp"));
	loadimage(&probe23, _T("probe23.bmp"));
	loadimage(&probe24, _T("probe24.bmp"));
	loadimage(&probe25, _T("probe25.bmp"));
	loadimage(&probe26, _T("probe26.bmp"));
	loadimage(&probe27, _T("probe27.bmp"));
	loadimage(&probe28, _T("probe28.bmp"));
	loadimage(&probe29, _T("probe29.bmp"));
	loadimage(&probe30, _T("probe30.bmp"));
	loadimage(&probe31, _T("probe31.bmp"));
}

void chooseProbe(int x , int y ,int angle) {

	

	if (angle >= -6 && angle <6)
	{
		putimage(x, y, &probe25, SRCAND);
	}
	else if (angle >= 6 && angle <18) {
		putimage(x, y, &probe24, SRCAND);
	}
	else if (angle >= 18 && angle <30) {
		putimage(x, y, &probe23, SRCAND);
	}
	else if (angle >= 30 && angle <42) {
		putimage(x, y, &probe22, SRCAND);
	}
	else if (angle >= 42 && angle <52) {
		putimage(x, y, &probe21, SRCAND);
	}
	else if (angle >= 52 && angle <62) {
		putimage(x, y, &probe20, SRCAND);
	}
	else if (angle >= 62 && angle <72) {
		putimage(x, y, &probe19, SRCAND);
	}
	else if (angle >= 72 && angle <82) {
		putimage(x, y, &probe18, SRCAND);
	}
	else if (angle >= 82 && angle <90) {
		putimage(x, y, &probe17, SRCAND);
	}
	else if (angle >= 90 && angle <102) {
		putimage(x, y, &probe16, SRCAND);
	}
	else if (angle >= 102 && angle <114) {
		putimage(x, y, &probe15, SRCAND);
	}
	else if (angle >= 114 && angle <126) {
		putimage(x, y, &probe13, SRCAND);
	}
	else if (angle >= 126 && angle <138) {
		putimage(x, y, &probe12, SRCAND);
	}
	else if (angle >= 138 && angle <150) {
		putimage(x, y, &probe11, SRCAND);
	}
	else if (angle >= 150 && angle <162) {
		putimage(x, y, &probe10, SRCAND);
	}
	else if (angle >= 162 && angle <174) {
		putimage(x, y, &probe9, SRCAND);
	}
	else if (angle >= 174 || angle <= -174) {
		putimage(x, y, &probe8, SRCAND);
	}
	else if (angle >-174 && angle <= -162) {
		putimage(x, y, &probe7, SRCAND);
	}
	else if (angle >-162 && angle <= -150) {
		putimage(x, y, &probe6, SRCAND);
	}
	else if (angle >-150 && angle <= -138) {
		putimage(x, y, &probe5, SRCAND);
	}
	else if (angle >-138 && angle <= -126) {
		putimage(x, y, &probe4, SRCAND);
	}
	else if (angle >-126 && angle <= -114) {
		putimage(x, y, &probe3, SRCAND);
	}
	else if (angle >-114 && angle <= -102) {
		putimage(x, y, &probe2, SRCAND);
	}
	else if (angle >-102 && angle <= -90) {
		putimage(x, y, &probe1, SRCAND);
	}
	else if (angle >-90 && angle <= -76) {
		putimage(x, y, &probe31, SRCAND);
	}
	else if (angle >-76 && angle <= -62) {
		putimage(x, y, &probe30, SRCAND);
	}
	else if (angle >-62 && angle <= -48) {
		putimage(x, y, &probe29, SRCAND);
	}
	else if (angle >-48 && angle <= -34) {
		putimage(x, y, &probe28, SRCAND);
	}
	else if (angle >-34 && angle <= -20) {
		putimage(x, y, &probe27, SRCAND);
	}
	else if (angle >-20 && angle < -6) {
		putimage(x, y, &probe26, SRCAND);
	}
}

void calculateAngle(int nowX,int nowY,int headX,int headY) {
	double a, c, Anglesin, changedAngle;
	a = sqrt(pow(nowX - headX, 2) + pow(nowY - headY, 2));
	c = fabs(nowY - headY);
	Anglesin = c / a;
	if (nowX > headX && nowY>headY) {
		changedAngle = -asin(Anglesin) * 180 / Pi;
	}
	else if (nowX > headX && nowY < headY) {
		changedAngle = asin(Anglesin) * 180 / Pi;
	}
	else if (nowX < headX && nowY>headY) {
		changedAngle = asin(Anglesin) * 180 / Pi - 180;
	}
	else {
		changedAngle = 180 - asin(Anglesin) * 180 / Pi;
	}
	writeHeadAngle((int)changedAngle);
}

void mouseMessageInput(void *) {

	MOUSEMSG mouse;
	
	BeginBatchDraw();

	while(true){
		mouse = GetMouseMsg();
		switch (mouse.uMsg) {
		case WM_MOUSEMOVE:
			int nowX, nowY, headX, headY;
			nowX = mouse.x;
			nowY = mouse.y;
			headX = readHeadX() + 45;
			headY = readHeadY() + 45;

			calculateAngle(nowX, nowY, headX, headY);
			putimage(0, 0, &background, SRCCOPY);
			chooseProbe(headX - 45, headY - 45, readHeadAngle());
			FlushBatchDraw();
			break;
		default:
			break;
		}
	}
	
	
	EndBatchDraw();
	//FlushMouseMsgBuffer();
	_endthread();
}

void snakeRun(void *) {
	BeginBatchDraw();
	while (true)
	{
		putimage(0, 0, &background, SRCCOPY);
		frameAction();
		FlushBatchDraw();
		Sleep(17);
	}
	EndBatchDraw();
	_endthread();
}







int main()
{
	init();
	initgraph(1440, 900);   // 创建绘图窗口，大小为 1440x900 像素
	
	
	readImage();
	
	//loadimage(&probe,_T("D://probe.bmp"));
	//loadimage(&probe_white, _T("D://probe_white.bmp"));
	putimage(0, 0, &background,SRCCOPY);
	//putimage(400, 465, &probe, SRCAND);
	gameRuning = true;

	
	BeginBatchDraw();

	_beginthread(mouseMessageInput, 0, NULL);
	_beginthread(snakeRun, 0, NULL);
	while (gameRuning){
		
		
		//FlushBatchDraw();
		
		
	}
	EndBatchDraw();

	_getch();    // 按任意键继续
	
	closegraph();// 关闭绘图窗口
}

