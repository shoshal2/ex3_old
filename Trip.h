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
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class Trip {


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & tripNumber;
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
    int startDrivingTime;
    double tarriff;
    bool hasADriver;
    int totalCurrent;
    GridPoint* startPoint;
    GridPoint* endPoint;
    GridPoint* currentPoint;
    stack<GridPoint*> stk;
    bfs b;
    Grid * grid;

public:
    Trip(int id, int xStart, int yStart, int xEnd,int yEnd ,int passenger, double tarriff, int time, Grid * g);
    Trip();
    ~Trip();
    GridPoint * move(int meters);
    int GetTripNumber();
    int getTripId();
    double getTarriff();
    int getPassengers();
    int getTotalMeters();
    int getTime();
    int getStartingTripTime();
    int getStartTripDrivingTime();
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