//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_TRIP_H
#define EX3_TRIP_H

using namespace std;
#include <string>
#include "Point.h"
#include "GridPoint.h"
#include "Grid.h"
#include "bfs.h"

class Trip {
private:
    int tripNumber;
    int passengers;
    double tarriff;
    Grid * grid;
    int totalCurrent;
    GridPoint* startPoint;
    GridPoint* endPoint;
    GridPoint* currentPoint;
    stack<GridPoint*> stk;
    bfs b;

public:
    Trip(int id, int xStart, int yStart, int xEnd,int yEnd ,int passenger, double tarriff);
    ~Trip();
    GridPoint * move(int meters);
    int GetTripNumber();
    double getTarriff();
    int getPassengers();
    int getTotalMeters();

    GridPoint* getStartPosition();
    GridPoint* getEndPosition();

    bool operator == (const Trip& other) const;
    bool operator != (const Trip& other) const;

    void getBFS(GridPoint* start, GridPoint* end, Grid * grid);

};

#endif //EX3_TRIP_H