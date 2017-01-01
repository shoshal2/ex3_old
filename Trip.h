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


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & tripId;
        ar & startPoint;
        ar & endPoint;
        ar & passengers;
        ar & tarriff;

    }


private:
    int tripId;
    int tripNumber;
    int passengers;
    int startTime;
    int currentTime;
    double tarriff;
    bool hasADriver = false;
    int totalCurrent;
    GridPoint* startPoint;
    GridPoint* endPoint;
    GridPoint* currentPoint;
    stack<GridPoint*> stk;
    bfs b;
    Grid * grid;

public:
    Trip(int id, int xStart, int yStart, int xEnd,int yEnd ,int passenger, double tarriff, int time, Grid * g);
    ~Trip();
    GridPoint * move(int meters);
    int GetTripNumber();
    int getTripId();
    double getTarriff();
    int getPassengers();
    int getTotalMeters();
    int getTime();
    int getStartingTripTime();
    void updateTime();
    GridPoint* getStartPosition();
    GridPoint* getEndPosition();
    void setTripHasADriver();
    bool tripHasADriver();
    bool operator == (const Trip& other) const;
    bool operator != (const Trip& other) const;

    void getBFS(GridPoint* start, GridPoint* end, Grid * grid);

};

#endif //EX3_TRIP_H