#include <iostream>
#include "PathFinder.h"

void CheckResult(int v1, int v2) 
{
    if (v1 == v2)
        cout << "OK" << endl << endl;
    else
        cout << "ERROR, got " << v1 << " expected " << v2 << endl << endl;
}

// the entry is for Codility testing 
int solution(int N, int A, int B, int C, int D) {
    PathFinder pf;
    pf.rang = N;
    pf.p1 = Point(2, 1);
    pf.p2 = Point(3, 4);
    pf.Resolve();
    return pf.result;
}

// local testing
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
