#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <graphics.h>
#include <conio.h>
#include <process.h>

#define up 0
#define down 1
#define left 2
#define right 3

#define empty 0
#define food 1
#define smartApple 2
#define mine 3
#define poison 4
#define wall 5
#define snake 6
#define mapWidth 32
#define mapHeight 20

typedef enum _maps {
	pure
}maps;

typedef enum _feature {
	none, addone, cutone, cuthalf
}animationFeature;

typedef struct _TAinput {
	int x[20], y[20], from[20], to[20],index;
	animationFeature feature;
}TAinput;

typedef struct _MAinput {
	int x[20], y[20], direction[20],index;
	animationFeature feature;
}MAinput;

typedef struct _AAinput {
	int x, y, direction;
}AAinput;

typedef struct _COAinput {
	int x[20], y[20], direction[20], index;
}COAinput;

typedef struct _CHAinput {
	int x[20], y[20], direction[20], index;
}CHAinput;

typedef enum _effectMusic{
	probe_Ready0,probe_Ready1,probe_Yes0,probe_Yes1,probe_Yes2,probe_Yes3,probe_Explode0,probe_Explode1,probe_Explode2
}effectMusics;


IMAGE probe1, probe2, probe3, probe4, probe5, probe6, probe7, probe8, probe9, probe10, probe11, probe12, probe13, probe14, probe15, probe16, probe17, probe18, probe19, probe20, probe21, probe22, probe23, probe24, probe25, probe26, probe27, probe28, probe29, probe30, probe31;
IMAGE probe1_1, probe1_2, probe1_3, probe1_4, probe1_5, probe1_6, probe1_7, probe1_8, probe1_9, probe8_1, probe8_2, probe8_3, probe8_4, probe8_5, probe8_6, probe8_7, probe8_8, probe8_9, probe16_1, probe16_2, probe16_3, probe16_4, probe16_5, probe16_6, probe16_7, probe16_8, probe16_9, probe25_1, probe25_2, probe25_3, probe25_4, probe25_5, probe25_6, probe25_7, probe25_8, probe25_9, noneIMG;

IMAGE map_pure;
IMAGE food_normal,mineIMG,poisonIMG,appleIMG;

void drawItems(), drawMap();
void turnOnce(int x, int y, int from, int to, int time);
void moveOnce(int x, int y, int direction, int time);
void snakeMoveAnimation(MAinput input);
void snakeAddAnimation(AAinput input);
void snakeCutOneAnimation(COAinput input);
void snakeCutHalfAnimation(CHAinput input);
void effectMusic(void *input);

int grassCount = 0;

extern int map[mapWidth][mapHeight];
extern maps snakeMaps;
extern void cleanPoison();

void loadImages() {
	loadimage(&probe1, _T("./supports/probe/probe1.bmp"));
	loadimage(&probe2, _T("./supports/probe/probe2.bmp"));
	loadimage(&probe3, _T("./supports/probe/probe3.bmp"));
	loadimage(&probe4, _T("./supports/probe/probe4.bmp"));
	loadimage(&probe5, _T("./supports/probe/probe5.bmp"));
	loadimage(&probe6, _T("./supports/probe/probe6.bmp"));
	loadimage(&probe7, _T("./supports/probe/probe7.bmp"));
	loadimage(&probe8, _T("./supports/probe/probe8.bmp"));
	loadimage(&probe9, _T("./supports/probe/probe9.bmp"));
	loadimage(&probe10, _T("./supports/probe/probe10.bmp"));
	loadimage(&probe11, _T("./supports/probe/probe11.bmp"));
	loadimage(&probe12, _T("./supports/probe/probe12.bmp"));
	loadimage(&probe13, _T("./supports/probe/probe13.bmp"));
	loadimage(&probe14, _T("./supports/probe/probe14.bmp"));
	loadimage(&probe15, _T("./supports/probe/probe15.bmp"));
	loadimage(&probe16, _T("./supports/probe/probe16.bmp"));
	loadimage(&probe17, _T("./supports/probe/probe17.bmp"));
	loadimage(&probe18, _T("./supports/probe/probe18.bmp"));
	loadimage(&probe19, _T("./supports/probe/probe19.bmp"));
	loadimage(&probe20, _T("./supports/probe/probe20.bmp"));
	loadimage(&probe21, _T("./supports/probe/probe21.bmp"));
	loadimage(&probe22, _T("./supports/probe/probe22.bmp"));
	loadimage(&probe23, _T("./supports/probe/probe23.bmp"));
	loadimage(&probe24, _T("./supports/probe/probe24.bmp"));
	loadimage(&probe25, _T("./supports/probe/probe25.bmp"));
	loadimage(&probe26, _T("./supports/probe/probe26.bmp"));
	loadimage(&probe27, _T("./supports/probe/probe27.bmp"));
	loadimage(&probe28, _T("./supports/probe/probe28.bmp"));
	loadimage(&probe29, _T("./supports/probe/probe29.bmp"));
	loadimage(&probe30, _T("./supports/probe/probe30.bmp"));
	loadimage(&probe31, _T("./supports/probe/probe31.bmp"));
	loadimage(&map_pure, _T("./supports/maps/pureMap.bmp"));
	loadimage(&food_normal, _T("./supports/items/food_normal.bmp"));
	loadimage(&probe1_1,_T("./supports/probe/extension/probe1_1.bmp"));
	loadimage(&probe1_2, _T("./supports/probe/extension/probe1_2.bmp"));
	loadimage(&probe1_3, _T("./supports/probe/extension/probe1_3.bmp"));
	loadimage(&probe1_4, _T("./supports/probe/extension/probe1_4.bmp"));
	loadimage(&probe1_5, _T("./supports/probe/extension/probe1_5.bmp"));
	loadimage(&probe1_6, _T("./supports/probe/extension/probe1_6.bmp"));
	loadimage(&probe1_7, _T("./supports/probe/extension/probe1_7.bmp"));
	loadimage(&probe1_8, _T("./supports/probe/extension/probe1_8.bmp"));
	loadimage(&probe1_9, _T("./supports/probe/extension/probe1_9.bmp"));
	loadimage(&probe8_1, _T("./supports/probe/extension/probe8_1.bmp"));
	loadimage(&probe8_2, _T("./supports/probe/extension/probe8_2.bmp"));
	loadimage(&probe8_3, _T("./supports/probe/extension/probe8_3.bmp"));
	loadimage(&probe8_4, _T("./supports/probe/extension/probe8_4.bmp"));
	loadimage(&probe8_5, _T("./supports/probe/extension/probe8_5.bmp"));
	loadimage(&probe8_6, _T("./supports/probe/extension/probe8_6.bmp"));
	loadimage(&probe8_7, _T("./supports/probe/extension/probe8_7.bmp"));
	loadimage(&probe8_8, _T("./supports/probe/extension/probe8_8.bmp"));
	loadimage(&probe8_9, _T("./supports/probe/extension/probe8_9.bmp"));
	loadimage(&probe16_1, _T("./supports/probe/extension/probe16_1.bmp"));
	loadimage(&probe16_2, _T("./supports/probe/extension/probe16_2.bmp"));
	loadimage(&probe16_3, _T("./supports/probe/extension/probe16_3.bmp"));
	loadimage(&probe16_4, _T("./supports/probe/extension/probe16_4.bmp"));
	loadimage(&probe16_5, _T("./supports/probe/extension/probe16_5.bmp"));
	loadimage(&probe16_6, _T("./supports/probe/extension/probe16_6.bmp"));
	loadimage(&probe16_7, _T("./supports/probe/extension/probe16_7.bmp"));
	loadimage(&probe16_8, _T("./supports/probe/extension/probe16_8.bmp"));
	loadimage(&probe16_9, _T("./supports/probe/extension/probe16_9.bmp"));
	loadimage(&probe25_1, _T("./supports/probe/extension/probe25_1.bmp"));
	loadimage(&probe25_2, _T("./supports/probe/extension/probe25_2.bmp"));
	loadimage(&probe25_3, _T("./supports/probe/extension/probe25_3.bmp"));
	loadimage(&probe25_4, _T("./supports/probe/extension/probe25_4.bmp"));
	loadimage(&probe25_5, _T("./supports/probe/extension/probe25_5.bmp"));
	loadimage(&probe25_6, _T("./supports/probe/extension/probe25_6.bmp"));
	loadimage(&probe25_7, _T("./supports/probe/extension/probe25_7.bmp"));
	loadimage(&probe25_8, _T("./supports/probe/extension/probe25_8.bmp"));
	loadimage(&probe25_9, _T("./supports/probe/extension/probe25_9.bmp"));
	loadimage(&noneIMG,_T("./supports/probe/extension/none.bmp"));
	loadimage(&mineIMG, _T("./supports/items/mine.bmp"));
	loadimage(&poisonIMG, _T("./supports/items/baneling.bmp"));
	loadimage(&appleIMG, _T("./supports/items/food_typical.bmp"));
}

void snakeTurnAnimation(TAinput input) {
	grassCount++;
	BeginBatchDraw();
	for (int time = 0; time <= 9 ; time++)
	{
		drawMap();
		drawItems();
		for (int tempIndex = 0; tempIndex <= input.index; tempIndex++) {
			turnOnce(input.x[tempIndex],input.y[tempIndex],input.from[tempIndex],input.to[tempIndex],time);
		}
		FlushBatchDraw();
		Sleep(17);
	}
	EndBatchDraw();

	MAinput output;
	for (int tempIndex = 0; tempIndex <= input.index; tempIndex++){
		output.x[tempIndex] = input.x[tempIndex];
		output.y[tempIndex] = input.y[tempIndex];
		output.direction[tempIndex] = input.to[tempIndex];
	}
	output.index = input.index;
	output.feature = input.feature;
	snakeMoveAnimation(output);

	if (grassCount == 40) {
		cleanPoison();
	}
}

void snakeMoveAnimation(MAinput input) {
	BeginBatchDraw();
	for (int time = 0; time < 10; time++) {
		drawMap();
		drawItems();
		for (int tempIndex = 0; tempIndex <= input.index; tempIndex++)
		{
			moveOnce(input.x[tempIndex], input.y[tempIndex], input.direction[tempIndex],time);
		}
		FlushBatchDraw();
		Sleep(17);
	}
	EndBatchDraw();

	if (input.feature == addone){
		AAinput output;
		output.x = input.x[0];
		output.y = input.y[0];
		output.direction = input.direction[0];
		snakeAddAnimation(output);
	}
	else if (input.feature == cutone) {
		COAinput output;
		for (int tempIndex = 0; tempIndex <= input.index; tempIndex++){
			output.x[tempIndex] = input.x[tempIndex];
			output.y[tempIndex] = input.y[tempIndex];
			output.direction[tempIndex] = input.direction[tempIndex];
		}
		output.index = input.index;
		snakeCutOneAnimation(output);
	}
	else if (input.feature == cuthalf) {
		CHAinput output;
		for (int tempIndex = 0; tempIndex <= input.index; tempIndex++) {
			output.x[tempIndex] = input.x[tempIndex];
			output.y[tempIndex] = input.y[tempIndex];
			output.direction[tempIndex] = input.direction[tempIndex];
		}
		output.index = input.index;
		snakeCutHalfAnimation(output);
	}
}

void snakeAddAnimation(AAinput input) {
	//TODO
	
	effectMusics outputMusic;
	int temp = rand() % 2;
	outputMusic = temp == 0 ? probe_Ready0:probe_Ready1;
	_beginthread(effectMusic, 0, (void *)&outputMusic);
	BeginBatchDraw();
	for (int time = 0; time < 10; time++){
		switch (input.direction)
		{
		case up:
			if (time == 0)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_9, SRCAND);
			if (time == 1)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_8, SRCAND);
			if (time == 2)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_7, SRCAND);
			if (time == 3)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_6, SRCAND);
			if (time == 4)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_5, SRCAND);
			if (time == 5)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_4, SRCAND);
			if (time == 6)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_3, SRCAND);
			if (time == 7)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_2, SRCAND);
			if (time == 8)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16_1, SRCAND);
			if (time == 9)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe16, SRCAND);
			break;
		case down:
			if (time == 0)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_9, SRCAND);
			if (time == 1)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_8, SRCAND);
			if (time == 2)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_7, SRCAND);
			if (time == 3)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_6, SRCAND);
			if (time == 4)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_5, SRCAND);
			if (time == 5)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_4, SRCAND);
			if (time == 6)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_3, SRCAND);
			if (time == 7)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_2, SRCAND);
			if (time == 8)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1_1, SRCAND);
			if (time == 9)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe1, SRCAND);
			break;
		case left:
			if (time == 0)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_9, SRCAND);
			if (time == 1)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_8, SRCAND);
			if (time == 2)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_7, SRCAND);
			if (time == 3)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_6, SRCAND);
			if (time == 4)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_5, SRCAND);
			if (time == 5)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_4, SRCAND);
			if (time == 6)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_3, SRCAND);
			if (time == 7)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_2, SRCAND);
			if (time == 8)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8_1, SRCAND);
			if (time == 9)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe8, SRCAND);
			break;
		case right:
			if (time == 0)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_9, SRCAND);
			if (time == 1)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_8, SRCAND);
			if (time == 2)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_7, SRCAND);
			if (time == 3)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_6, SRCAND);
			if (time == 4)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_5, SRCAND);
			if (time == 5)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_4, SRCAND);
			if (time == 6)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_3, SRCAND);
			if (time == 7)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_2, SRCAND);
			if (time == 8)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25_1, SRCAND);
			if (time == 9)
				putimage(45 * (input.x - 1), 45 * (input.y - 1), &probe25, SRCAND);
			break;
		}
		FlushBatchDraw();
		Sleep(17);
	}
	EndBatchDraw();
}

void snakeCutOneAnimation(COAinput input) {
	//TODO
	effectMusics outputMusic;
	int temp = rand() % 3;
	if (temp == 0)
		outputMusic = probe_Explode0;
	if (temp == 1)
		outputMusic = probe_Explode1;
	if (temp == 2)
		outputMusic = probe_Explode2;

	_beginthread(effectMusic, 0, (void *)&outputMusic);

	BeginBatchDraw();
	drawMap();
	drawItems();

	for (int tempIndex = 0; tempIndex < input.index; tempIndex++){
		switch (input.direction[tempIndex])
		{
		case up:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe16, SRCAND);
			break;
		case down:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe1, SRCAND);
			break;
		case left:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe8, SRCAND);
			break;
		case right:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe25, SRCAND);
			break;
		}
	}
	//TODO 消失动画
	FlushBatchDraw();
	EndBatchDraw();
}

void snakeCutHalfAnimation(CHAinput input) {

	for (int time = 0; time < input.index; time++){
		effectMusics outputMusic;
		int temp = rand() % 3;
		if (temp == 0)
			outputMusic = probe_Explode0;
		if (temp == 1)
			outputMusic = probe_Explode1;
		if (temp == 2)
			outputMusic = probe_Explode2;

		_beginthread(effectMusic, 0, (void *)&outputMusic);
		Sleep(17);
	}



	BeginBatchDraw();
	drawMap();
	drawItems();
	for (int tempIndex = 0; tempIndex < input.index / 2; tempIndex++) {
		switch (input.direction[tempIndex])
		{
		case up:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe16, SRCAND);
			break;
		case down:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe1, SRCAND);
			break;
		case left:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe8, SRCAND);
			break;
		case right:
			putimage(45 * (input.x[tempIndex] - 1), 45 * (input.y[tempIndex] - 1), &probe25, SRCAND);
			break;
		}
	}
	//TODO 消失动画
	FlushBatchDraw();
	EndBatchDraw();
}


void drawItems() {
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			switch (map[x][y])
			{
			case food:
				putimage(45 * (x - 1), 45 * (y - 1), &food_normal, SRCAND);
				break;
			case smartApple:
				putimage(45 * (x - 1), 45 * (y - 1), &appleIMG, SRCAND);
				break;
			case mine:
				putimage(45 * (x - 1), 45 * (y - 1), &mineIMG, SRCAND);
				break;
			case poison:
				if(grassCount % 4 < 2)
					putimage(45 * (x - 1), 45 * (y - 1), &poisonIMG, SRCAND);//TODO
				break;
			default:
				break;
			}
		}
	}
}

void drawMap() {
	switch (snakeMaps)
	{
	case pure:
		putimage(0, 0, &map_pure, SRCCOPY);
		break;
	default:
		break;
	}
}

void snakeCutOneAnimation(int x, int y, int direction) {
	//TODO
	switch (direction)
	{
	case up:
		drawMap();
		drawItems();
		//putimage(45 * (x - 1), 45 * (y - 1), &probe16, SRCAND);
		FlushBatchDraw();
		break;
	case down:
		drawMap();
		drawItems();
		//putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);
		FlushBatchDraw();
		break;
	case left:
		drawMap();
		drawItems();
		//putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);
		FlushBatchDraw();
		break;
	case right:
		drawMap();
		drawItems();
		//putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);
		FlushBatchDraw();
		break;
	}
}

void turnOnce(int x, int y, int from, int to, int time) {
	switch (from)
	{
	case up:
		if (to == left) {
			
			if(time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe16, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe15, SRCAND);
			
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe14, SRCAND);
			
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe13, SRCAND);
			
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe12, SRCAND);
			
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe11, SRCAND);
			
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe10, SRCAND);
			
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe9, SRCAND);
			
			
			if (time == 8)
			putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);

			if (time == 9)
				putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);
			
		}
		else if (to == right) {
			
			if (time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe16, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe17, SRCAND);
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe18, SRCAND);
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe19, SRCAND);
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe20, SRCAND);
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe21, SRCAND);
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe22, SRCAND);
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe23, SRCAND);
			
			if (time == 8)
			putimage(45 * (x - 1), 45 * (y - 1), &probe24, SRCAND);
			
			if (time == 9)
			putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);
			
		}
		else {
			putimage(45 * (x - 1), 45 * (y - 1), &probe16, SRCAND);
		}
		break;
	case down:
		if (to == left) {
			
			if (time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe2, SRCAND);
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe3, SRCAND);
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe4, SRCAND);
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe5, SRCAND);
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe6, SRCAND);
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe7, SRCAND);
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);

			if (time == 8)
				putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);

			if (time == 9)
				putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);
			
		}
		else if (to == right){
			
			if (time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe31, SRCAND);
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe30, SRCAND);
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe29, SRCAND);
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe28, SRCAND);
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe27, SRCAND);
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe26, SRCAND);
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);
			
			if (time == 8)
				putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);

			if (time == 9)
				putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);
		}
		else {
				putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);
		}

		break;
	case left:
		if (to == up)
		{
			if (time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe9, SRCAND);
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe10, SRCAND);
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe11, SRCAND);
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe12, SRCAND);
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe13, SRCAND);
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe14, SRCAND);
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe15, SRCAND);
			
			if (time == 8)
			putimage(45 * (x - 1), 45 * (y - 1), &probe16, SRCAND);

			if (time == 9)
			putimage(45 * (x - 1), 45 * (y - 1), &probe16, SRCAND);
			
		}
		else if (to == right) {
			
			if (time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe7, SRCAND);
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe6, SRCAND);
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe5, SRCAND);
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe4, SRCAND);
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe3, SRCAND);
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe2, SRCAND);
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);

			if (time == 8)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);

			if (time == 9)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);
			
		}
		else {
			putimage(45 * (x - 1), 45 * (y - 1), &probe8, SRCAND);
		}
		break;
	case right:
		if (to == up) {
			
			if (time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe24, SRCAND);
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe23, SRCAND);
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe22, SRCAND);
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe21, SRCAND);
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe20, SRCAND);
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe19, SRCAND);
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe18, SRCAND);
			
			if (time == 8)
			putimage(45 * (x - 1), 45 * (y - 1), &probe17, SRCAND);
			
			if (time == 9)
			putimage(45 * (x - 1), 45 * (y - 1), &probe16, SRCAND);
			
		}
		else if (to == down){
			
			if (time == 0)
			putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);
			
			if (time == 1)
			putimage(45 * (x - 1), 45 * (y - 1), &probe26, SRCAND);
			
			if (time == 2)
			putimage(45 * (x - 1), 45 * (y - 1), &probe27, SRCAND);
			
			if (time == 3)
			putimage(45 * (x - 1), 45 * (y - 1), &probe28, SRCAND);
			
			if (time == 4)
			putimage(45 * (x - 1), 45 * (y - 1), &probe29, SRCAND);
			
			if (time == 5)
			putimage(45 * (x - 1), 45 * (y - 1), &probe30, SRCAND);
			
			if (time == 6)
			putimage(45 * (x - 1), 45 * (y - 1), &probe31, SRCAND);
			
			if (time == 7)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);

			if (time == 8)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);

			if (time == 9)
			putimage(45 * (x - 1), 45 * (y - 1), &probe1, SRCAND);
			
		}
		else {
			putimage(45 * (x - 1), 45 * (y - 1), &probe25, SRCAND);
		}
		break;
	}
}

void moveOnce(int x,int y,int direction,int time) {
	switch (direction)
	{
	case up:
			putimage(45 * (x - 1), 45 * (y - 1) - time * 5, &probe16, SRCAND);
		break;
	case down:
			putimage(45 * (x - 1), 45 * (y - 1) + time * 5, &probe1, SRCAND);
		break;
	case left:
			putimage(45 * (x - 1) - time * 5, 45 * (y - 1), &probe8, SRCAND);
		break;
	case right:
			putimage(45 * (x - 1) + time * 5, 45 * (y - 1), &probe25, SRCAND);
		break;
	}
}





void effectMusic(void *input) {
	effectMusics *data = (effectMusics *)input;
	switch (*data)
	{
	case probe_Ready0:
		PlaySound(TEXT("./supports/music/effect/probe/Probe_Ready0_01.wav"), NULL, SND_FILENAME| SND_ASYNC);
		break;
	case probe_Ready1:
		PlaySound(TEXT("./supports/music/effect/probe/Probe_Ready1_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case probe_Yes0:
		PlaySound(TEXT("./supports/music/effect/probe/Probe_Yes0_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case probe_Yes1:
		PlaySound(TEXT("./supports/music/effect/probe/Probe_Yes1_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case probe_Yes2:
		PlaySound(TEXT("./supports/music/effect/probe/Probe_Yes2_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case probe_Yes3:
		PlaySound(TEXT("./supports/music/effect/probe/Probe_Yes3_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case probe_Explode0:
		PlaySound(TEXT("./supports/music/effect/probe/Protoss_ExplosionSmall0_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case probe_Explode1:
		PlaySound(TEXT("./supports/music/effect/probe/Protoss_ExplosionSmall1_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case probe_Explode2:
		PlaySound(TEXT("./supports/music/effect/probe/Protoss_ExplosionSmall2_01.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	}
	
}