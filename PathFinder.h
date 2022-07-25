#pragma once
#include "UVMaze.h"
#include <vector>

using namespace std;

class PathFinder
{
public:
	Point p1{ 0,0 };
	Point p2{ 0,0 };
	int rang { 1 };
	int result{ -1 };

	PathFinder() {}
	void Resolve();
	void PrintPath(vector<UVMaze*>& v);
private:
	vector<UVMaze*> v1;
	vector<UVMaze*> v2;
	void Build(Point p, vector<UVMaze*>& v);
	void Find();
};

