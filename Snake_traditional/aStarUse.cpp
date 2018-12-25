#include <iostream>
#include "Astar.h"
using namespace std;

#define mapWidth 32
#define mapHeight 20

int mapMirror[mapHeight][mapWidth];
extern int map[mapWidth][mapHeight];
extern int autoRunDirection[640];
extern int autoRunSteps;

void findTheWay(int startX, int startY,int targetX, int targetY)
{
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			if (map[x][y] != 0 && map[x][y] != 1)
				mapMirror[y][x] = 1;
			else
				mapMirror[y][x] = 0;
		}
	}





	//初始化地图，用二维矩阵代表地图，1表示障碍物，0表示可通
	/*vector<vector<int>> maze = {
		{ 1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,2,1,0,1,0,0,0,0,1 },
	{ 1,0,0,2,1,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,1,0,0,1,1,1 },
	{ 1,1,1,0,0,0,0,0,1,1,0,1 },
	{ 1,1,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,1,0,0,0,0,1,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1 }
	};
	*/
	//vector<vector<int>> maze;

	vector <vector<int> >array;
	std::vector<int> v;
	for (int i = 0; i <mapHeight; i++) {
		for (int j = 0; j <mapWidth; j++) {
			v.push_back(mapMirror[i][j]);
		}
		array.push_back(v); //保存array的每个元素
		v.clear();
	}



	Astar astar;
	astar.InitAstar(array);

	//设置起始和结束点
	Point start(startY, startX);
	Point end(targetY, targetX);
	//A*算法找寻路径
	list<Point *> path = astar.GetPath(start, end, false);
	
	//打印
	int formerX = startY, formerY = startX, stepCount = -1;
	for (auto &p : path){
		if (stepCount == -1) {
			stepCount++;
		}
		else {
			if (formerX == p->x) {
				if (formerY == p->y + 1) {
					autoRunDirection[stepCount] = 3;
					stepCount++;
				}
				else {
					autoRunDirection[stepCount] = 2;
					stepCount++;
				}
			}
			else if (formerX == p->x + 1) {
				if (formerY == p->y + 1) {
					autoRunDirection[stepCount] = 1;
					stepCount++;
					autoRunDirection[stepCount] = 3;
					stepCount++;
				}
				else if (formerY == p->y - 1) {
					autoRunDirection[stepCount] = 1;
					stepCount++;
					autoRunDirection[stepCount] = 2;
					stepCount++;
				}
				else {
					autoRunDirection[stepCount] = 1;
					stepCount++;
				}

			}
			else if (formerX == p->x - 1) {
				if (formerY == p->y + 1) {
					autoRunDirection[stepCount] = 0;
					stepCount++;
					autoRunDirection[stepCount] = 3;
					stepCount++;
				}
				else if (formerY == p->y - 1) {
					autoRunDirection[stepCount] = 0;
					stepCount++;
					autoRunDirection[stepCount] = 2;
					stepCount++;
				}
				else {
					autoRunDirection[stepCount] = 0;
					stepCount++;
				}

			}
			formerX = p->x;
			formerY = p->y;
		}
		
	}
	autoRunSteps = stepCount;
		

	//system("pause");
	
}
