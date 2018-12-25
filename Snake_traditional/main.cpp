#include <stdio.h>
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include <WinBase.h>
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <process.h>

#pragma comment(lib, "Winmm.lib")

typedef enum _gameStatus{
	stop,running,pause,fail,success,autorun
}status;

typedef enum _direction {
	up, down, left, right
}direction;

typedef enum _statuMusic {
	gamePause_normal,gameResume_normal, gamePause_nova, gameResume_nova, gamePause_dva, gameResume_dva,nexussBoost,energyNE_normal,energyNE_nova,energyNE_dva
}statuMusics;

status gameStatus = stop;
extern direction snakeDirection;
direction directionAnnocement;
int autoRunDirection[640] = {-1};
int autoRunSteps = 0;
void keyBoardHit(void *);
void backGroundMusic(void *);
void gameStatuMusic(void *input);
void gameRunningOrPause(void *);
void gameAutoRun(void *);

extern void loadImages();
extern void initMaps();
extern void init();
extern void recreateItem(int item);
extern void findWay();;

void isHitOther();

int main() {
	initgraph(1600,900);
	loadImages();
	init();//init snake
	initMaps();
	snakeDirection = right;
	
	//putimage(0, 0, &map_pure, SRCCOPY);//TEST
	//FILE *fp1;
	//fopen_s(&fp1,"1.txt","r");
	gameStatus = running;
	_beginthread(keyBoardHit,0,NULL);
	_beginthread(backGroundMusic,0,NULL);
	_beginthread(gameRunningOrPause, 0, NULL);
	//gameStatus = autorun;
	//_beginthread(gameAutoRun, 0, NULL);

	while (true)
	{

	}

	return 0;
}



void backGroundMusic(void *) {
	mciSendString(_T("open \"./supports/music/background/Valor My Shield.wav\" alias bg"), NULL, 0, NULL);
	mciSendString(_T("play bg"), NULL, 0, NULL);
	
}





void keyBoardHit(void *) {
	char input;
	while (gameStatus == running || gameStatus==pause){
		if (_kbhit()) {
			input = _getch();
			switch (input)
			{
			case 'w': case 'W':
				if (snakeDirection == down) {
					statuMusics outputMusic;
					outputMusic = gamePause_normal;
					_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					gameStatus = pause;
				}
				else {
					directionAnnocement = up;
					if (gameStatus == pause)
					{
						statuMusics outputMusic;
						outputMusic = gameResume_normal;
						_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					}
					gameStatus = running;
				}
				break;
			case 's': case 'S':
				if (snakeDirection == up) {
					statuMusics outputMusic;
					outputMusic = gamePause_normal;
					_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					gameStatus = pause;
				}
				else {
					directionAnnocement = down;
					if (gameStatus == pause)
					{
						statuMusics outputMusic;
						outputMusic = gameResume_normal;
						_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					}
					gameStatus = running;
				}
				break;
			case 'a':case 'A':
				if (snakeDirection == right) {
					statuMusics outputMusic;
					outputMusic = gamePause_normal;
					_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					gameStatus = pause;
				}
				else {
					directionAnnocement = left;
					if (gameStatus == pause)
					{
						statuMusics outputMusic;
						outputMusic = gameResume_normal;
						_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					}
					gameStatus = running;
				}
				break;
			case 'd':case 'D':
				if (snakeDirection == left) {
					statuMusics outputMusic;
					outputMusic = gamePause_normal;
					_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					gameStatus = pause;
				}
				else {
					directionAnnocement = right;
					if (gameStatus == pause)
					{
						statuMusics outputMusic;
						outputMusic = gameResume_normal;
						_beginthread(gameStatuMusic, 0, (void *)&outputMusic);
					}
					gameStatus = running;
				}
				break;
			default:
				break;
			}
		}
	}
	
}





void gameStatuMusic(void *input) {
	statuMusics *data = (statuMusics *)input;
	switch (*data)
	{
	case gamePause_normal:
		PlaySound(TEXT("./supports/music/effect/announcer/Alert_ProtossGamePaused_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case gameResume_normal:
		PlaySound(TEXT("./supports/music/effect/announcer/Alert_ProtossGameResumed_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case gamePause_dva:
		PlaySound(TEXT("./supports/music/effect/announcer/DVaA_GamePaused00_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case gameResume_dva:
		PlaySound(TEXT("./supports/music/effect/announcer/DVaA_GameResumed00_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case gamePause_nova:
		PlaySound(TEXT("./supports/music/effect/announcer/NovaA_GamePaused00_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case gameResume_nova:
		PlaySound(TEXT("./supports/music/effect/announcer/NovaA_GameResumed00_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case nexussBoost:
		PlaySound(TEXT("./supports/music/effect/announcer/Nexus_ChronoBoostImpact0_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case energyNE_normal:
		PlaySound(TEXT("./supports/music/effect/announcer/Alert_ProtossNotEnoughEnergy_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case energyNE_nova:
		PlaySound(TEXT("./supports/music/effect/announcer/HeroNovaMP1_Energy_Low01_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case energyNE_dva:
		PlaySound(TEXT("./supports/music/effect/announcer/DVaA_NotEnoughEnergy00_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	}
	_endthread();
}




void gameAutoRun(void *) {
	statuMusics outputMusic = nexussBoost;
	_beginthread(gameStatuMusic,0,(void *)&outputMusic);
	findWay();
	int undoSteps = autoRunSteps;
	int doneSteps = 0,allDoneSteps = 0;
	while (gameStatus == autorun)
	{
		direction undoDirections[640];
		for (int i = 0; i <= autoRunSteps; i++) {
			switch (autoRunDirection[i])
			{
			case 0:
				undoDirections[i] = down;
				break;
			case 1:
				undoDirections[i] = up;
				break;
			case 2:
				undoDirections[i] = right;
				break;
			case 3:
				undoDirections[i] = left;
				break;
			}
		}

		if (undoSteps > 0) {
			undoSteps--;
			snakeDirection = undoDirections[doneSteps];
			doneSteps++;
			allDoneSteps++;
			isHitOther();
			Sleep(500);
		}
		else {
			findWay();
			undoSteps = autoRunSteps;
			doneSteps = 0;
		}

		if (allDoneSteps > 40) {
			statuMusics outputMusic2 = energyNE_normal;
			_beginthread(gameStatuMusic, 0, (void *)&outputMusic2);
			gameStatus = running;
			recreateItem(2);
			directionAnnocement = snakeDirection;
			_beginthread(keyBoardHit, 0, NULL);
			_beginthread(gameRunningOrPause, 0, NULL);
			
		}
	}

	
}




void gameRunningOrPause(void *) {
	while (gameStatus == running || gameStatus == pause)
	{
		if (gameStatus == running) {
			snakeDirection = directionAnnocement;
			isHitOther();

		}
		Sleep(500);

	}
}

