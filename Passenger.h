//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_PASSENGER_H
#define EX3_PASSENGER_H


#include <cstddef>
#include "GridPoint.h"
using namespace std;



class Passenger {

private:
    GridPoint* sourcePoint;
    GridPoint* destinationPoint;


public:
    Passenger(int xStart, int yStart, int xEnd,int yEnd);
    int produceScore();
    GridPoint* getSource();
    GridPoint* getDestination();

    bool operator == (const Passenger& other) const;
    bool operator != (const Passenger& other) const;
};


#endif //EX3_PASSENGER_H