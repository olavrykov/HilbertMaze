// UVMaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "UVMaze.h"
#include "PathFinder.h"

using namespace std;

void CheckResult(int v1, int v2) 
{
    if (v1 == v2)
        cout << "OK" << endl << endl;
    else
        cout << "ERROR, got " << v1 << " expected " << v2 << endl << endl;
}

int solution(int N, int A, int B, int C, int D) {
    PathFinder pf;
    pf.rang = N;
    pf.p1 = Point(2, 1);
    pf.p2 = Point(3, 4);
    pf.Resolve();
    return pf.result;
}

int main()
{
    std::cout << "Hilbert Maze Route\n\n";

    PathFinder pf;

    std::cout << "Solution " << pf.rang << " p1 " << pf.p1.x << " " << pf.p1.y << " p2 " << pf.p2.x << " " << pf.p2.y << endl;
    pf.rang = 1;
    pf.p1 = Point(2, 1);
    pf.p2 = Point(3, 4);
    pf.Resolve();
    std::cout << "Result " << pf.result << endl;
    CheckResult(pf.result, 8);

    std::cout << "Solution " << pf.rang << " p1 " << pf.p1.x << " " << pf.p1.y << " p2 " << pf.p2.x << " " << pf.p2.y << endl;
    pf.rang = 2;
    pf.p1 = Point(2, 5);
    pf.p2 = Point(6, 6);
    pf.Resolve();
    std::cout << "Result " << pf.result << endl;
    CheckResult(pf.result, 7);

    pf.rang = 3; 
    pf.p1 = Point(6, 6);
    pf.p2 = Point(10, 13);
    std::cout << "Solution " << pf.rang << " p1 " << pf.p1.x << " " << pf.p1.y << " p2 " << pf.p2.x << " " << pf.p2.y << endl;
    pf.Resolve();
    std::cout << "Result " << pf.result << endl;
    CheckResult(pf.result, 39);
}

UVPoint UVMaze::FromDecart(Point p)
{
    int p0 = p.x - cx;
    int p1 = p.y - cy;
    int m00 = matrix[rotation][0][0];
    int m01 = matrix[rotation][0][1];
    int m10 = matrix[rotation][1][0];
    int m11 = matrix[rotation][1][1];
    UVPoint r;
    r.u = p0 * m00 + p1 * m01;
    r.v = p0 * m10 + p1 * m11;
    return r;
}

Point UVMaze::ToDecart(UVPoint p)
{
    int p0 = p.u;
    int p1 = p.v;
    int m00 = matrix[(4 - rotation)%4][0][0];
    int m01 = matrix[(4 - rotation)%4][0][1];
    int m10 = matrix[(4 - rotation)%4][1][0];
    int m11 = matrix[(4 - rotation)%4][1][1];
    Point r;
    r.x = p0 * m00 + p1 * m01 + cx;
    r.y = p0 * m10 + p1 * m11 + cy;
    return r;
}

bool UVMaze::IsPointOnCenter(Point p)
{
    UVPoint r = FromDecart(p);
    return r.u == 0 || r.v == 0;
}

bool UVMaze::IsPointOnBorder(Point p)
{
    UVPoint r = FromDecart(p);
    return 
        r.u ==  d || r.v ==  d ||
        r.u == -d || r.v == -d;
}

int UVMaze::AddRotation(int v) 
{
    return (rotation + v) % 4; 
}

// 101 NE
// 112 SE
// 123 SW
// 130 NW
Quadrant UVMaze::GetQuadrant(Point p, int d)
{
    Quadrant q;
    UVPoint t;
    UVPoint r = FromDecart(p);
    if (r.u > 0 && r.v > 0) {
        q.drection = Direction_NE;
        t = UVPoint(d, d);
    }
    else if (r.u > 0 && r.v < 0) {
        q.drection = Direction_SE;
        t = UVPoint(d, -d);
    }
    else if (r.u < 0 && r.v < 0) {
        q.drection = Direction_SW;
        t = UVPoint(-d, -d);
    }
    else if (r.u < 0 && r.v > 0) {
        q.drection = Direction_NW;
        t = UVPoint(-d, d);
    }
    q.p = ToDecart(t);
    return q;
}

bool UVMaze::GetDistance(Point p1, Point p2, int* s) 
{
    if (!IsPointOnCenter(p1))
        return false;
    if (!IsPointOnCenter(p2))
        return false;

    UVPoint t1 = FromDecart(p1);
    UVPoint t2 = FromDecart(p2);
    *s = 0;
    if (t1.v > 1 && t2.v > 1) {
        *s = abs(t2.v - t1.v);
        return true;
    }
    if (t1.v < 1 && t2.v < 1) {
        if(t1.v == 0 && t2.v == 0)
            *s = abs(t2.u - t1.u);
        else
            *s = abs(t2.u) + abs(t1.u) - t1.v - t2.v;
        return true;
    }
    return false;
}

// coord on square perimeter ((0,0),(d,d))
// assume p is on board
int PerimeterCoord(int d, Point p) {
    if (p.y == 0)
        return p.x;
    if (p.x == d-1)
        return d + p.y;
    if (p.y == d-1)
        return 3 * (d-1) - p.x;
    if (p.x == 0)
        return 4 * (d-1) - p.y;

    throw runtime_error("perimiter invalid point");
}

int UVMaze::GetAroundDistance(Point p1, Point p2)
{
    int x1 = PerimeterCoord(d * 2 + 1, p1);
    int x2 = PerimeterCoord(d * 2 + 1, p2);
    if (x1 == x2)
        return 0;

    if (x1 < x2)
        return min(x2 - x1, x1 + 4 * d * 2 - x2);

    if (x2 < x1)
        return min(x1 - x2, x2 + 4 * d * 2 - x1);

}

Point UVMaze::GetOutOf(Point p)
{
    UVPoint t = FromDecart(p);

    // if on the board
    if (t.u == d || t.u == -d ||
        t.v == d || t.v == -d)
        return p;

    if (t.u == 0 || t.v == 0) {
        t.u = 0;
        t.v = t.v > 1 ? d : -d;
    }
    else 
        throw std::runtime_error("umaze error");

    return ToDecart(t);
}

// see get out
int UVMaze::GetOutCost(Point p) 
{
    UVPoint t = FromDecart(p);
    
    // if on the board
    if (t.u == d || t.u == -d ||
        t.v == d || t.v == -d)
        return 0;

    int result = 0;
    if (t.u == 0 || t.v == 0) {
        if (t.v > 1)
            result = d - t.v;
        else
            result = d + t.v + abs(t.u);
    }
    else
        throw std::runtime_error("umaze error");
    
    return result;
}


const int UVMaze::matrix[4][2][2] = { // _back
    { { 1, 0}, 
      { 0, 1} },

    { { 0,-1}, 
      { 1 ,0} },

    { {-1, 0}, 
      { 0,-1} },

    { { 0 ,1}, 
      {-1, 0} }
};
/*
const int UVMaze::matrix[4][2][2] = {
    { { 1, 0},
      { 0, 1} },

    { { 0 ,1},
      {-1, 0} },

    { {-1, 0},
      { 0,-1} },

    { { 0,-1},
      { 1 ,0} }
};
*/