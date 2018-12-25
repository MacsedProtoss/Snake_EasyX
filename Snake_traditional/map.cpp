#include <stdio.h>
#include <time.h>
#include <math.h>
#include<stdlib.h>
#include <math.h>
#include <process.h>

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

typedef enum _gameStatus {
	stop, running, pause,fail,success,autorun
}status;

/*
typedef struct _aStarPoint {
	int x, y;
	int stepsHaveDone, stepsWillGo, stepsAll;
	struct _aStarPoint* prev;
	int isClose, isOpen;
}aStarPoint;
*/

extern int readHeadX(), readHeadY(),readDirection(),countSnake();
extern void writeOntoMap(),addOne(),cutHalf(),cutOne(),freeAll(),moveSnake();
extern void findTheWay(int startX, int startY, int targetX, int targetY);
extern status gameStatus;
extern void gameAutoRun(void *);

void recreateItem(int item);
void findWay();

maps snakeMaps = pure;
int map[mapWidth][mapHeight] = { empty };


void initMaps() {
	switch (snakeMaps)
	{
	case pure:
		recreateItem(food);
		recreateItem(mine);
		recreateItem(poison);
		recreateItem(smartApple);
		break;
	default:
		break;
	}
}

void isHitOther() {
	int headX = readHeadX(), headY = readHeadY(), snakeDirection = readDirection();
	switch (snakeDirection)// 得到下一步位置
	{
	case 0:
		headY -= 1;
		if (headY <0)
			gameStatus = fail;
		break;
	case 1:
		headY += 1;
		if (headY >mapHeight)
			gameStatus = fail;
		break;
	case 2:
		headX -= 1;
		if (headX < 0)
			gameStatus = fail;
		break;
	case 3:
		headX += 1;
		if (headX > mapWidth)
			gameStatus = fail;
		break;
	}
	
	if(gameStatus != fail)
	switch (map[headX][headY])
	{
	case empty:
		moveSnake();
		break;
	case food:
		addOne();
		break;
	case smartApple:
		map[headX][headY] = empty;
		findWay();
		gameStatus = autorun;
		_beginthread(gameAutoRun, 0, NULL);
		break;
	case mine:
		if (countSnake()>3){
			cutHalf();
		}else {
			gameStatus = fail;
			freeAll();
		}
		break;
	case poison:
		if (countSnake()>1) {
			cutOne();
		}else {
			gameStatus = fail;
			freeAll();
		}
		break;
	case wall: case snake :
		gameStatus = fail;
		freeAll();
		break;
	}

	
}

void cleanPoison() {
	for (int x = 0; x < mapWidth; x++){
		for (int y = 0; y < mapHeight; y++){
			if (map[x][y] == poison){
				map[x][y] = empty;
			}
		}
	}
}

void recreateItem(int item) {
	srand(time_t());
	int rndX = rand() % mapWidth, rndY = rand() % mapHeight;
	int number = rand() % 5 + 3;
	switch (item){
	case food: case smartApple: case mine:
		while (map[rndX][rndY] != empty){
			rndX = rand() % mapWidth;
			rndY = rand() % mapHeight;
		}
		map[rndX][rndY] = item;
		break;
	case poison:
		for (int times = 0; times < number; times++){
			while (map[rndX][rndY] != empty) {
				rndX = rand() % mapWidth;
				rndY = rand() % mapHeight;
			}
			map[rndX][rndY] = item;
		}
		break;
	default:
		break;
	}
}





void findWay() {

	int startX = readHeadX(),startY = readHeadY();
	int targetX, targetY;
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			if (map[x][y] == food) {
				targetX = x;
				targetY = y;
			}
		}
	}

	findTheWay(startX,startY,targetX,targetY);

}

/*

aStarPoint calculateAStar(aStarPoint input,int targetX,int targetY) {
	aStarPoint output;
	output.x = input.x;
	output.y = input.y;
	output.stepsHaveDone = input.stepsHaveDone;
	output.stepsWillGo = abs(targetX - output.x) + abs(targetY - output.y);
	output.stepsAll = output.stepsHaveDone + output.stepsWillGo;
	return output;
}

aStarPoint chooseNextAStar(aStarPoint input, int targetX, int targetY) {
	aStarPoint output;
	aStarPoint temp1,temp2,temp3,temp4;
	if (input.x == 0){
		if (input.y == 0) {
			temp1 = input;
			temp2 = input;
			temp1.x = input.x + 1;
			temp2.y = input.y + 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
		}else if(input.y == mapHeight-1) {
			temp1 = input;
			temp2 = input;
			temp1.x = input.x + 1;
			temp2.y = input.y - 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
		}else {
			temp1 = input;
			temp2 = input;
			temp3 = input;
			temp1.x = input.x + 1;
			temp2.y = input.y + 1;
			temp3.y = input.y - 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			temp3 = calculateAStar(temp3, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
			output = output.stepsAll > temp3.stepsAll ? temp3 : output;
		}

	}
	else if (input.x == mapWidth-1) {
		if (input.y == 0) {
			temp1 = input;
			temp2 = input;
			temp1.x = input.x - 1;
			temp2.y = input.y + 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
		}
		else if (input.y == mapHeight-1) {
			temp1 = input;
			temp2 = input;
			temp1.x = input.x - 1;
			temp2.y = input.y - 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
		}
		else {
			temp1 = input;
			temp2 = input;
			temp3 = input;
			temp1.x = input.x - 1;
			temp2.y = input.y + 1;
			temp3.y = input.y - 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			temp3 = calculateAStar(temp3, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
			output = output.stepsAll > temp3.stepsAll ? temp3 : output;
		}
	}else {
		if (input.y == 0) {
			temp1 = input;
			temp2 = input;
			temp3 = input;
			temp1.x = input.x + 1;
			temp2.y = input.y + 1;
			temp3.x = input.x - 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			temp3 = calculateAStar(temp3, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
			output = output.stepsAll > temp3.stepsAll ? temp3 : output;
		}
		else if (input.y == mapHeight-1) {
			temp1 = input;
			temp2 = input;
			temp3 = input;
			temp1.x = input.x + 1;
			temp2.y = input.y - 1;
			temp3.x = input.x - 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			temp3 = calculateAStar(temp3,targetX,targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
			output = output.stepsAll > temp3.stepsAll ? temp3 : output;
		}
		else {
			temp1 = input;
			temp2 = input;
			temp3 = input;
			temp4 = input;
			temp1.x = input.x + 1;
			temp2.y = input.y + 1;
			temp3.y = input.y - 1;
			temp4.x = input.x - 1;
			temp1 = calculateAStar(temp1, targetX, targetY);
			temp2 = calculateAStar(temp2, targetX, targetY);
			temp3 = calculateAStar(temp3, targetX, targetY);
			temp4 = calculateAStar(temp4, targetX, targetY);
			output = temp1.stepsAll > temp2.stepsAll ? temp2 : temp1;
			output = output.stepsAll > temp3.stepsAll ? temp3 : output;
			output = output.stepsAll > temp4.stepsAll ? temp4 : output;
		}
	}

	return output;
}

void aStarMainFun(aStarPoint input,int targetX,int targetY) {
	aStarPoint nextPoint = chooseNextAStar(input, targetX, targetY);
	while (map[nextPoint.x][nextPoint.y]!=empty){
		nextPoint = chooseNextAStar(input, targetX, targetY);
	}
	
	aStarMainFun(nextPoint,targetX,targetY);//TODO
}

*/
