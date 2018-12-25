#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <process.h>

typedef enum _feature {
	none,addone,cutone,cuthalf
}animationFeature;

typedef enum _direction{
	up, down, left, right
}direction;

typedef struct _snake {
	struct _snake *prev, *next;
	int x, y;
	direction displayDirection;
}snake;

typedef struct _TAinput {
	int x[20], y[20], from[20], to[20],index;
	animationFeature feature;
}TAinput;

typedef struct _MAinput {
	int x[20], y[20], direction[20],index;
	animationFeature feature;
}MAinput;

/*
typedef struct _AAinput {
	int x, y, direction;
}AAinput;

typedef struct _COAinput {
	int x, y, direction;
}COAinput;
*/


extern int map[32][20];
extern void recreateItem(int item);
extern void snakeTurnAnimation(TAinput input);// , snakeMoveAnimation(MAinput input), snakeAddAnimation(int x, int y, int direction), snakeCutOneAnimation(int x, int y, int direction);
int readHeadX(),readHeadY();
void writeOntoMap();
void snakeAllThread(void *input);
//void snakeTurnThread(void *input);
//void snakeMoveThread(void *input);
//void snakeAddThread(void *input);
//void snakeCutOneThread(void *input);

snake *HEAD, *END;
direction snakeDirection = up;

void init() {
	HEAD = (snake *)malloc(sizeof(snake));
	HEAD->x = 5;
	HEAD->y = 4;
	HEAD->displayDirection = up;
	HEAD->prev = NULL;
	HEAD->next = NULL;
	END = HEAD;
	writeOntoMap();
}

void addOne() {
	//动画处理
	snake *pointer = END;
	TAinput tainput;
	int index = 0;
	while (pointer->prev != NULL) {

		if (pointer->displayDirection != pointer->prev->displayDirection) {

			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->prev->displayDirection;
		}
		else {
			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->displayDirection;
		}
		pointer = pointer->prev;
		index++;
	}

	if (HEAD->displayDirection != snakeDirection) {
		tainput.x[index] = HEAD->x;
		tainput.y[index] = HEAD->y;
		tainput.from[index] = HEAD->displayDirection;
		tainput.to[index] = snakeDirection;
	}
	tainput.index = index;
	tainput.feature = addone;
	_beginthread(snakeAllThread, 0, (void *)&tainput);


	int headX = readHeadX(), headY = readHeadY();
	switch (snakeDirection)// 得到下一步位置
	{
	case up:
		headY -= 1;
		break;
	case down:
		headY += 1;
		break;
	case left:
		headX -= 1;
		break;
	case right:
		headX += 1;
		break;
	}
	pointer = (snake *)malloc(sizeof(snake));
	pointer->next = HEAD;
	pointer->prev = NULL;
	pointer->x = headX;
	pointer->y = headY;
	pointer->displayDirection = snakeDirection;
	HEAD->prev = pointer;
	HEAD = pointer;
	writeOntoMap();
	recreateItem(1);
}

void cutOne() {
	//动画处理
	snake *pointer = END;
	TAinput tainput;
	int index = 0;
	while (pointer->prev != NULL) {

		if (pointer->displayDirection != pointer->prev->displayDirection) {

			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->prev->displayDirection;
		}
		else {
			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->displayDirection;
		}
		pointer = pointer->prev;
		index++;
	}

	if (HEAD->displayDirection != snakeDirection) {
		tainput.x[index] = HEAD->x;
		tainput.y[index] = HEAD->y;
		tainput.from[index] = HEAD->displayDirection;
		tainput.to[index] = snakeDirection;
	}
	tainput.index = index;
	tainput.feature = cutone;
	_beginthread(snakeAllThread, 0, (void *)&tainput);

	//数据处理
	switch (snakeDirection)
	{
	case up:
		END->x = HEAD->x;
		END->y = HEAD->y - 1;
		break;
	case down:
		END->x = HEAD->x;
		END->y = HEAD->y + 1;
		break;
	case left:
		END->x = HEAD->x - 1;
		END->y = HEAD->y;
		break;
	case right:
		END->x = HEAD->x + 1;
		END->y = HEAD->y;
		break;
	}
	END->next = HEAD;
	HEAD = END;
	END = END->prev;
	HEAD->prev = NULL;
	HEAD->next->prev = HEAD;
	END->next = NULL;
	HEAD->displayDirection = snakeDirection;

	END = END->prev;
	free(END->next);
	END->next = NULL;

	writeOntoMap();
	recreateItem(4);
}

int countSnake() {
	int count = 0;
	snake * pointer = HEAD;
	do{
		count++;
		pointer = pointer->next;
	} while (pointer != NULL);
	return count;
}

void cutHalf() {

	//动画处理
	snake *pointer = END;
	TAinput tainput;
	int index = 0;
	while (pointer->prev != NULL) {

		if (pointer->displayDirection != pointer->prev->displayDirection) {

			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->prev->displayDirection;
		}
		else {
			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->displayDirection;
		}
		pointer = pointer->prev;
		index++;
	}

	if (HEAD->displayDirection != snakeDirection) {
		tainput.x[index] = HEAD->x;
		tainput.y[index] = HEAD->y;
		tainput.from[index] = HEAD->displayDirection;
		tainput.to[index] = snakeDirection;
	}
	tainput.index = index;
	tainput.feature = cuthalf;
	_beginthread(snakeAllThread, 0, (void *)&tainput);


	//数据处理
	switch (snakeDirection)
	{
	case up:
		END->x = HEAD->x;
		END->y = HEAD->y - 1;
		break;
	case down:
		END->x = HEAD->x;
		END->y = HEAD->y + 1;
		break;
	case left:
		END->x = HEAD->x - 1;
		END->y = HEAD->y;
		break;
	case right:
		END->x = HEAD->x + 1;
		END->y = HEAD->y;
		break;
	}
	END->next = HEAD;
	HEAD = END;
	END = END->prev;
	HEAD->prev = NULL;
	HEAD->next->prev = HEAD;
	END->next = NULL;
	HEAD->displayDirection = snakeDirection;

	int count = countSnake() / 2;
	int temp = 0;
	pointer = END;
	while (temp < count) {
		pointer = pointer->prev;
		free(END);
		END = pointer;
		END->next = NULL;
		temp++;
	}
	writeOntoMap();
	recreateItem(3);
}

void freeAll() {
	snake *pointer = HEAD;
	do{
		snake *temp = pointer->next;
		free(pointer);
		pointer = temp;
	} while (pointer != NULL);
	
}

int readHeadX() {
	return HEAD->x;
}

int readHeadY() {
	return HEAD->y;
}

int readDirection() {
	return snakeDirection;
}


void moveSnake() {
	//动画处理
	snake *pointer = END;
	TAinput tainput;
	int index = 0;
	while (pointer->prev != NULL) {

		if (pointer->displayDirection != pointer->prev->displayDirection) {
			
			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->prev->displayDirection;
		}
		else {
			tainput.x[index] = pointer->x;
			tainput.y[index] = pointer->y;
			tainput.from[index] = pointer->displayDirection;
			tainput.to[index] = pointer->displayDirection;
		}
		pointer = pointer->prev;
		index++;
	}

	//if (HEAD->displayDirection != snakeDirection){
		tainput.x[index] = HEAD->x;
		tainput.y[index] = HEAD->y;
		tainput.from[index] = HEAD->displayDirection;
		tainput.to[index] = snakeDirection;
	//}
	tainput.index = index;
	
	

	//数据处理

	//HEAD与END对调
	if (HEAD != END){
	switch (snakeDirection)
	{
	case up:
		END->x = HEAD->x;
		END->y = HEAD->y - 1;
		break;
	case down:
		END->x = HEAD->x;
		END->y = HEAD->y + 1;
		break;
	case left:
		END->x = HEAD->x - 1;
		END->y = HEAD->y;
		break;
	case right:
		END->x = HEAD->x + 1;
		END->y = HEAD->y;
		break;
	}
	END->next = HEAD;
	HEAD = END;
	END = END->prev;
	HEAD->prev = NULL;
	HEAD->next->prev = HEAD;
	END->next = NULL;
	HEAD->displayDirection = snakeDirection;
	}else {
		switch (snakeDirection)
		{
		case up:
			HEAD->y = HEAD->y - 1;
			break;
		case down:
			HEAD->y = HEAD->y + 1;
			break;
		case left:
			HEAD->x = HEAD->x - 1;
			break;
		case right:
			HEAD->x = HEAD->x + 1;
			break;
		}
		HEAD->displayDirection = snakeDirection;
	}
	writeOntoMap();
	_beginthread(snakeAllThread, 0, (void *)&tainput);
}


void writeOntoMap() {

	for (int mapX = 0; mapX < 32; mapX++){
		for (int mapY = 0; mapY < 20; mapY++){
			map[mapX][mapY] = map[mapX][mapY] == 6 ? 0 : map[mapX][mapY];//清除地图上所有snake
		}

	}

	snake *pointer = HEAD;
	
	while (pointer != NULL){
		map[pointer->x][pointer->y] = 6;
		pointer = pointer->next;
	}

}

void snakeAllThread(void *input) {
	TAinput *data = (TAinput *)input;
	snakeTurnAnimation(*data);
	_endthread();
}



/*

void snakeTurnThread(void *input){
	TAinput *data = (TAinput *)input;
	snakeTurnAnimation(data->x,data->y,data->from,data->to);
	_endthread();
}

void snakeMoveThread(void *input) {
	MAinput *data = (MAinput *)input;
	snakeMoveAnimation(data->x,data->y,data->direction);
	_endthread();
}

void snakeAddThread(void *input) {
	AAinput *data = (AAinput *)input;
	snakeAddAnimation(data->x,data->y,data->direction);
	_endthread();
}

void snakeCutOneThread(void *input) {
	COAinput *data = (COAinput *)input;
	snakeAddAnimation(data->x, data->y, data->direction);
	_endthread();
}

*/