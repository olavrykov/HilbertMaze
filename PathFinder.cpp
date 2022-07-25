#include <iostream>
#include "PathFinder.h"

using namespace std;

void PathFinder::Resolve()
{
	Build(p1, v1);
	Build(p2, v2);
	
	PrintPath(v1);
	PrintPath(v2);
	
	Find();
}

void PathFinder::PrintPath(vector<UVMaze*>& v)
{
	cout << "Path" << endl;
	for (auto m : v)
		cout << " cx " << m->cx << " cy " << m->cy << " d " << m->d << " rot " << m->rotation << endl;
}

int power2N(int N) {
	int result = 1;
	for (int i = 1; i < N; ++i)
		result *= 2;

	return result;
}

void PathFinder::Build(Point p, vector<UVMaze*>& v)
{
	UVMaze* m;

	v.clear();
	int r = rang;
	int rotation = 0;
	int d = power2N(rang + 1);
	int cx = d;
	int cy = d;
	m = new UVMaze(cx, cy, d, rotation);
	v.push_back(m);
	while (r > 1) {
		r--;
		d /= 2;
		if (m->IsPointOnCenter(p))
			break;

		if (m->IsPointOnBorder(p))
			break;

		Quadrant q = m->GetQuadrant(p, d);
		//cout << "Direction " << q.direction << " c " << q.p.x << " " << q.p.y << endl;
		switch (q.direction)
		{
		case Direction_NE:
			rotation = m->AddRotation(0);
			break;
		case Direction_SE:
			rotation = m->AddRotation(3);
			break;
		case Direction_SW:
			rotation = m->AddRotation(1);
			break;
		case Direction_NW:
			rotation = m->AddRotation(0);
			break;
		}
		m = new UVMaze(q.p.x, q.p.y, d, rotation);
		v.push_back(m);
	}
}

void PathFinder::Find()
{
	int i1 = (int)v1.size() - 1;
	int i2 = (int)v2.size() - 1;
	Point t1 = p1;
	Point t2 = p2;
	result = 0;
	int cost1 = 0;
	int cost2 = 0;
	cout << "Find " << endl;
	while (i1 >= 0 && i2 >= 0)
	{
		cout << " t1 " << t1.x << " " << t1.y << " t2 " << t2.x << " " << t2.y << endl;
		UVMaze m1 = *v1[i1];
		UVMaze m2 = *v2[i2];
		if (m1.d < m2.d) {
			cost1 += m1.GetOutCost(t1);
			t1 = m1.GetOutOf(t1);
			i1--;
			continue;
		}
		
		if (m1.d > m2.d) {
			cost2 += m2.GetOutCost(t2);
			t2 = m2.GetOutOf(t2);
			i2--;
			continue;
		}

		if (m1.cx == m2.cx && m1.cy == m2.cy) {
			int d12 = 0;
			if (m1.GetDistance(t1, t2, &d12)) {
				result = cost1 + cost2 + d12;
				break;
			}
		}
		cost1 += m1.GetOutCost(t1);
		t1 = m1.GetOutOf(t1);
		i1--;

		cost2 += m2.GetOutCost(t2);
		t2 = m2.GetOutOf(t2);
		i2--;
	}

	// not in maze
	if (result == 0) {
		int d12 = v1[0]->GetAroundDistance(t1, t2);
		result = cost1 + cost2 + d12;
	}
}
