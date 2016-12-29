//
// Created by leerosset on 14/12/16.
//

#include "Passenger.h"
#include <stdlib.h>


Passenger::Passenger(int xStart, int yStart, int xEnd,int yEnd) {
    sourcePoint = new GridPoint(xStart, yStart);
    destinationPoint = new GridPoint(xEnd, yEnd);
}

/**
 * the method returns the passenger's destination point
 * @return
 */
GridPoint* Passenger::getDestination() {
    return destinationPoint;
}

/**he method returns the passenger's source point
 *
 * @return
 */
GridPoint* Passenger::getSource() {
    return sourcePoint;
}

/**
 * the method returns the passenger's score
 * @return
 */
int Passenger::produceScore() {
    int range = 6;
    return rand() % range ;
}

/**
 * an override to the == operator.
 * @param other
 * @return true if the Passenger is equal to the given Passenger
 */
bool Passenger::operator == (const Passenger& other) const{
    return true;
}

/**
 * an override to the != operator.
 * @param other
 * @return true if the Passenger is not equal to the given Passenger
 */
bool Passenger::operator != (const Passenger& other) const{
    return false;
}