//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_GRIDPOINT_H
#define EX3_GRIDPOINT_H


using namespace std;
#include "Point.h"
#include <cstddef>

class GridPoint: public Point
{
private:
    int distance;
    bool visited;
    int x;
    int y;
    int distanceFromStart[];


public:
    GridPoint *parent;
    GridPoint *neighbor1;
    GridPoint *neighbor2;
    GridPoint *neighbor3;
    GridPoint *neighbor4;
    GridPoint(int X, int Y) : Point(X, Y){
        x = X;
        y = Y;
        distance = 0;
        visited = false;
        parent = NULL;
        neighbor1 = NULL;
        neighbor2 = NULL;
        neighbor3 = NULL;
        neighbor4 = NULL;
    };
    int getDistance();
    void setDistance(int num);
    bool isVisited();
    void setToVisitedPoint();
    void setParent(GridPoint *gp);
    //neighbor to the 9 o'clock direction
    void setNeighbor1(GridPoint *gp);
    //neighbor to the 12 o'clock direction
    void setNeighbor2(GridPoint *gp);
    //neighbor to the 3 o'clock direction
    void setNeighbor3(GridPoint *gp);
    //neighbor to the 6 o'clock direction
    void setNeighbor4(GridPoint *gp);
    bool equalsTO(GridPoint * other);

    bool operator==(const GridPoint & gp) const;
    bool operator<(const GridPoint & gp) const;
    bool operator>(const GridPoint & gp) const;

    ~GridPoint();
};


#endif //EX3_GRIDPOINT_H
