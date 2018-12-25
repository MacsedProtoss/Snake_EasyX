/*
#include "iostream"
#include "set"
#include "stdlib.h"
#include "vector"
#define mapWidth 32
#define mapHeight 20

using namespace std;
class Node {
public:
	int x;
	int y;
	int g;
	int h;
	int f;
	Node *parent;
	Node(int, int);
	Node() {}
	bool operator <(const Node &other)const {
		if (this->f != other.f) {
			return this->f<other.f;
		}
		else {
			return true;//������ͬ 
		}

	}
};
set<Node> full;
set<Node> openL;
set<Node> closeL;
vector<Node> resultL;



int mapMirror[mapHeight][mapWidth];
int mapNormal[mapWidth][mapHeight];
extern int map[mapWidth][mapHeight];
extern int autoRunDirection[640];
extern int autoRunSteps;

int col;
int row;
int line = 1;
int tilt = 2;

int isContains(int x, int y, set<Node> *pL) {
	set<Node>::iterator iter = pL->begin();
	for (int i = 0; iter != pL->end(); iter++, i++) {
		if (iter->x == x && iter->y == y)
			return i;
	}
	return -1;
}
int isContains(int x, int y, vector<Node> *pL) {
	vector<Node>::iterator iter = pL->begin();
	for (int i = 0; iter != pL->end(); iter++, i++) {
		if (iter->x == x && iter->y == y)
			return 1;
	}
	return 0;
}
int countH(int x, int y, int endX, int endY) {
	int xSub = abs(x - endX);
	int ySub = abs(y - endY);
	int minXY = xSub>ySub ? ySub : xSub;
	return minXY * tilt + abs(xSub - ySub)*line;
}

void check(int x, int y, int cost, Node *parent, int endX, int endY) {
	if (x<0 || x >= row || y<0 || y >= col) return;
	Node node(x, y);
	node.parent = parent;

	node.g = parent->g + cost;
	if (isContains(x, y, &closeL) != -1) return;
	if (mapMirror[x][y] == 1) {
		closeL.insert(node);
		return;
	}
	int index = isContains(x, y, &openL);
	if (index != -1) {
		set<Node>::iterator iter = openL.begin();
		for (int i = 0; i<index; i++)
			iter++;
		if (node.g<iter->g) {
			node.f = node.g + iter->h;
			node.h = iter->h;
			openL.erase(iter);
			openL.insert(node);
		}
	}
	else {
		node.h = countH(x, y, endX, endY);
		node.f = node.h + node.g;
		openL.insert(node);
	}
}
void getPath(Node *node) {
	while (node->parent == NULL) {
		resultL.push_back(*node);
		return;
	}
	getPath(node->parent);
	resultL.push_back(*node);
}

int start(int endX, int endY) {
	if (openL.empty()) return 0;
	set<Node>::iterator iter = openL.begin();

	Node n = *iter;
	if (n.x == endX && n.y == endY) {
		getPath(&n);
		return 1;
	}
	check(n.x, n.y - 1, line, &n, endX, endY); //�� 
	check(n.x, n.y + 1, line, &n, endX, endY); //�� 
	check(n.x - 1, n.y, line, &n, endX, endY); //��
	check(n.x + 1, n.y, line, &n, endX, endY); //��
	check(n.x - 1, n.y - 1, tilt, &n, endX, endY); //����
	check(n.x - 1, n.y + 1, tilt, &n, endX, endY); //���� 
	check(n.x + 1, n.y - 1, tilt, &n, endX, endY); //����
	check(n.x + 1, n.y + 1, tilt, &n, endX, endY); //���� 
	closeL.insert(n);
	openL.erase(iter);
	return start(endX, endY);
}

int search(int startX, int startY, int endX, int endY) {
	if (mapMirror[startX][startY] == 1 || mapMirror[endX][endY] == 1) return -1;
	Node *root = new Node(startX, startY);
	openL.insert(*root);
	return start(endX, endY);
}

void findTheWay(int startX,int startY,int targetX,int targetY) {
	col = mapHeight;
	row = mapWidth;

	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			if (map[x][y] != 0 && map[x][y] != 1)
				mapMirror[y][x] = 1;
			else
				mapMirror[y][x] = 0;
		}
	}

	int flag = search(startY, startX, targetY, targetX);//TODO ��ںͳ���

	


	int formerX = startY, formerY = startX,stepCount = 0;
	vector<Node> *pL = &resultL;
	vector<Node>::iterator iter = pL->begin();
	for (int i = 0; iter != pL->end(); iter++, i++) {
		if (formerX == iter->x) {
			if (formerY == iter->y + 1){
				autoRunDirection[stepCount] = 3;
				stepCount++;
			}else{
				autoRunDirection[stepCount] = 2;
				stepCount++;
			}
		}
		else if (formerX == iter->x + 1) {
			if (formerY == iter->y + 1){
				autoRunDirection[stepCount] = 1;
				stepCount++;
				autoRunDirection[stepCount] = 3;
				stepCount++;
			}else if (formerY == iter->y - 1){
				autoRunDirection[stepCount] = 1;
				stepCount++;
				autoRunDirection[stepCount] = 2;
				stepCount++;
			}
			else {
				autoRunDirection[stepCount] = 1;
				stepCount++;
			}

		}else if (formerX == iter->x - 1) {
			if (formerY == iter->y + 1) {
				autoRunDirection[stepCount] = 0;
				stepCount++;
				autoRunDirection[stepCount] = 3;
				stepCount++;
			}
			else if (formerY == iter->y - 1) {
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
		
	}
	
	autoRunSteps = stepCount;



}

Node::Node(int x, int y) {
	this->x = x;
	this->y = y;
	this->g = 0;
	this->h = 0;
	this->f = 0;
	this->parent = NULL;
}
*/

#include <math.h>
#include "Astar.h"

void Astar::InitAstar(std::vector<std::vector<int>> &_maze)
{
	maze = _maze;
}

int Astar::calcG(Point *temp_start, Point *point)
{
	int extraG = (abs(point->x - temp_start->x) + abs(point->y - temp_start->y)) == 1 ? kCost1 : kCost2;
	int parentG = point->parent == NULL ? 0 : point->parent->G; //����ǳ�ʼ�ڵ㣬���丸�ڵ��ǿ�
	return parentG + extraG;
}

int Astar::calcH(Point *point, Point *end)
{
	//�ü򵥵�ŷ����þ������H�����H�ļ����ǹؼ������кܶ��㷨��û�����о�^_^
	return sqrt((double)(end->x - point->x)*(double)(end->x - point->x) + (double)(end->y - point->y)*(double)(end->y - point->y))*kCost1;
}

int Astar::calcF(Point *point)
{
	return point->G + point->H;
}

Point *Astar::getLeastFpoint()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto &point : openList)
			if (point->F<resPoint->F)
				resPoint = point;
		return resPoint;
	}
	return NULL;
}

Point *Astar::findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner)
{
	openList.push_back(new Point(startPoint.x, startPoint.y)); //�������,��������һ���ڵ㣬�������
	while (!openList.empty())
	{
		auto curPoint = getLeastFpoint(); //�ҵ�Fֵ��С�ĵ�
		openList.remove(curPoint); //�ӿ����б���ɾ��
		closeList.push_back(curPoint); //�ŵ��ر��б�
									   //1,�ҵ���ǰ��Χ�˸����п���ͨ���ĸ���
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints)
		{
			//2,��ĳһ�����ӣ���������ڿ����б��У����뵽�����б����õ�ǰ��Ϊ�丸�ڵ㣬����F G H
			if (!isInList(openList, target))
			{
				target->parent = curPoint;

				target->G = calcG(curPoint, target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}
			//3����ĳһ�����ӣ����ڿ����б��У�����Gֵ, �����ԭ���Ĵ�, ��ʲô������, �����������ĸ��ڵ�Ϊ��ǰ��,������G��F
			else
			{
				int tempG = calcG(curPoint, target);
				if (tempG<target->G)
				{
					target->parent = curPoint;

					target->G = tempG;
					target->F = calcF(target);
				}
			}
			Point *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint; //�����б���Ľڵ�ָ�룬��Ҫ��ԭ�������endpointָ�룬��Ϊ���������
		}
	}

	return NULL;
}

std::list<Point *> Astar::GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner)
{
	Point *result = findPath(startPoint, endPoint, isIgnoreCorner);
	std::list<Point *> path;
	//����·�������û�ҵ�·�������ؿ�����
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}

	// �����ʱ�����б���ֹ�ظ�ִ��GetPath���½���쳣
	openList.clear();
	closeList.clear();

	return path;
}

Point *Astar::isInList(const std::list<Point *> &list, const Point *point) const
{
	//�ж�ĳ���ڵ��Ƿ����б��У����ﲻ�ܱȽ�ָ�룬��Ϊÿ�μ����б����¿��ٵĽڵ㣬ֻ�ܱȽ�����
	for (auto p : list)
		if (p->x == point->x&&p->y == point->y)
			return p;
	return NULL;
}

bool Astar::isCanreach(const Point *point, const Point *target, bool isIgnoreCorner) const
{
	if (target->x<0 || target->x>maze.size() - 1
		|| target->y<0 || target->y>maze[0].size() - 1
		|| maze[target->x][target->y] == 1
		|| target->x == point->x&&target->y == point->y
		|| isInList(closeList, target)) //������뵱ǰ�ڵ��غϡ�������ͼ�����ϰ�������ڹر��б��У�����false
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //��б�ǿ���
			return true;
		else
		{
			//б�Խ�Ҫ�ж��Ƿ��ס
			if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)
				return true;
			else
				return isIgnoreCorner;
		}
	}
}

std::vector<Point *> Astar::getSurroundPoints(const Point *point, bool isIgnoreCorner) const
{
	std::vector<Point *> surroundPoints;

	for (int x = point->x - 1; x <= point->x + 1; x++)
		for (int y = point->y - 1; y <= point->y + 1; y++)
			if (isCanreach(point, new Point(x, y), isIgnoreCorner))
				surroundPoints.push_back(new Point(x, y));

	return surroundPoints;
}
