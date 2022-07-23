#pragma once
#include "UVMaze.h"
#include <vector>

using namespace std;

class PathFinder
{
public:
	Point p1;
	Point p2;
	int rang;
	int result;

	PathFinder() {}
	void Resolve();
	void PrintPath(vector<UVMaze*>& v);
private:
	vector<UVMaze*> v1;
	vector<UVMaze*> v2;
	void Build(Point p, vector<UVMaze*>& v);
	void Find();
};

