#pragma once
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream

struct Point
{
	int x=0;
	int y=0;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
public:
	//string ToString()
	//{
	//	ostringstream oss;
	//	oss << "x "<< x << " y " << y;
	//	return oss.str();
	//}
};

struct UVPoint
{
	int u=0;
	int v=0;
	UVPoint() {}
	UVPoint(int u, int v) : u(u), v(v) {}
};

enum Direction {
	Direction_UNKNOWN,
	Direction_NE, Direction_SE, Direction_SW, Direction_NW,
	Direction_N, Direction_E, Direction_S, Direction_W };

struct Quadrant
{
	Direction drection;
	Point p;
};

// maze x: -d..+d y: -d..+d relavively from cx,cy
class UVMaze
{
public:
	int cx;
	int cy;
	int d; 
	int rotation; // 0 N, 1 E, 2 S, 3 W
	UVMaze(int _cx, int _cy, int _d, int _rotation) : cx(_cx), cy(_cy), d(_d), rotation(_rotation) {}
	UVPoint FromDecart(Point p);
	Point ToDecart(UVPoint p);
	bool IsPointOnCenter(Point p);
	bool IsPointOnBorder(Point p);
	Point GetOutOf(Point p);
	int GetOutCost(Point p);
	bool GetDistance(Point p1, Point p2, int* s);
	int GetAroundDistance(Point p1, Point p2);
	Quadrant GetQuadrant(Point p, int d);
	int AddRotation(int v);
private:
//	int rotation; // 0 N, 1 E, 2 S, 3 W
	static const int matrix[4][2][2];
};
/*
const int UVMaze::matrix[4][2][2] = {
	{ {0,1}, {2,3} },
	{ {1,1}, {1,1} },
	{ {0,1}, {2,3} },
	{ {1,1}, {1,1} }
};
*/
int main();
