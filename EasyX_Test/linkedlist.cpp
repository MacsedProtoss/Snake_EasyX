
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <math.h>


typedef struct _snake {
	struct _snake *prev, *next;
	int x, y;
	int angle;
}snake;

snake *HEAD, *END;

void init() {
	HEAD = (snake *)malloc(sizeof(snake));
	HEAD->x = 500;
	HEAD->y = 400;
	HEAD->angle = 0;
	HEAD->prev = NULL;
	HEAD->next = NULL;
	END = HEAD;

}

void addOne() {
	snake *previous = END;
	END = (snake*)malloc(sizeof(snake));
	previous->next = END;
	END->prev = previous;
	END->x = 0;//TODO
	END->y = 0;//TODO
	END->angle = previous->angle;
	END->next = NULL;

}

void cutOne() {
	END = (END->prev);
	free(END->next);
	END->next = NULL;
}

void freeAll() {
	snake *pointer = HEAD;
	while (pointer->next != NULL) {
		free(pointer);
		pointer = pointer->next;
	}
	free(pointer);
}

void drawAll() {
	//TODO:获取实际句柄才能画
	extern void chooseProbe(int x, int y , int angle);
	
	snake *pointer = HEAD;

	while (pointer->next != NULL)
	{
		bool isHead = pointer == HEAD ? true : false;
		if (isHead) {
			chooseProbe(pointer->x,pointer->y,pointer->angle);
		}
		pointer = pointer->next;
	}
	bool isHead = pointer == HEAD ? true : false;
	if (isHead) {
		chooseProbe(pointer->x, pointer->y, pointer->angle);
	}
}


int readHeadAngle() {
	return HEAD->angle;
}

int readHeadX() {
	return HEAD->x;
}

int readHeadY() {
	return HEAD->y;
}

void refresh() {
	if (HEAD != END) {
		snake *pointer = HEAD->next;
		while (pointer->next != NULL) {
			pointer->angle = pointer->prev->angle;
			pointer = pointer->next;
		}
		pointer->angle = pointer->prev->angle;
	}

}

void writeHeadAngle(int ang) {
	HEAD->angle = ang;
}

void frameAction() {
	double angleToRadia;
	#define Pi 3.1415926535
	refresh();
	//for (int i = 0; i < 9; i++)
	//{
		snake *pointer = HEAD;
		while (pointer->next != NULL)
		{

			angleToRadia = (double)(pointer->angle) / 180 * Pi;
			pointer->x = pointer->x + (int)(4.5 * cos(angleToRadia));
			pointer->y = pointer->y - (int)(4.5 * sin(angleToRadia));
			pointer = pointer->next;
		}
		angleToRadia = (double)(pointer->angle) / 180 * Pi;
		pointer->x = pointer->x + (int)(4.5 * cos(angleToRadia));
		pointer->y = pointer->y - (int)(4.5 * sin(angleToRadia));
		pointer = pointer->next;
		//Sleep(10);
	//}

	drawAll();
	
}