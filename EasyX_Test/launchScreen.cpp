#include"stdafx.h"

/*
void launchScreen() {
	initgraph(1600,900);
	
	loadimage(NULL,_T("D://bg.jpg"),1600,900,true);
	IMAGE startIMG;
	loadimage(&startIMG, _T("game-logo-sc2.bmp"), 680, 419, true);
	/*RECT PressRect = {700,800,900,850};
	LOGFONT pressFont;
	gettextstyle(&pressFont);
	_tcscpy_s(pressFont.lfFaceName, _T("微软雅黑"));
	pressFont.lfHeight = 30;
	pressFont.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&pressFont);
	*/
/*
	while (!_kbhit())
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		
		BeginBatchDraw();
		putimage(700, 800, &startIMG, SRCCOPY);
		Sleep(200);
		EndBatchDraw();
		/*
		if ((int)time.wSecond % 2 == 0)
		{
			//clearrectangle(700, 800, 900, 850);
			FlushBatchDraw();
			putimage(700,800,&startIMG, SRCAND);
			//drawtext(_T("按任意键进入游戏"), &PressRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else
		{
			//clearrectangle(700, 800, 900, 850);
			FlushBatchDraw();
			//drawtext(_T("                            "), &PressRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	
	//EndBatchDraw();
	
	closegraph();

	//TODO:launch true screen

}*/