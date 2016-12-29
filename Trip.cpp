//
// Created by leerosset on 14/12/16.
//

#include "Trip.h"
#include "GridPoint.h"
Trip::Trip(int id, int xStart, int yStart, int xEnd,int yEnd ,int passenger, double tarriff, int time) {
    this->time = time;
    this->tripNumber = id;
    this->startPoint = new GridPoint(xStart, yStart);
    this->endPoint = new GridPoint(xEnd, yEnd);
    this->currentPoint = startPoint;
    this->passengers = passenger;
    this->tarriff = tarriff;
    totalCurrent = 0;
}


Trip::~Trip() {
    delete startPoint;
    delete endPoint;
}

/**
 * the method that "moves" the trip
 * @param meters
 */
GridPoint * Trip::move(int meters)
{
    GridPoint *gp;
    int i = 0;
    while(i < meters || !stk.empty()){
        gp = stk.top();
        stk.pop();
    }
    totalCurrent += meters;
    return gp;
}

/**
 * the method returns the trip number
 * @return tripNumber
 */
int Trip::GetTripNumber()
{
    return tripNumber;
}


int Trip::getTime()
{
    return time;
}


/**
 * the mthod return the trips tariff
 * @return tarriff
 */
double Trip::getTarriff()
{
    return tarriff;
}

/**
 * the method returns the number of passengers
 * @return
 */
int Trip::getPassengers()
{
    return passengers;
}

/**
 * the method returns the total meters passed
 * @return totalCurrent
 */
int Trip::getTotalMeters()
{
    return totalCurrent;
}

/**
 * the method returns the trip's start position
 * @return startPoint
 */
GridPoint* Trip::getStartPosition()
{
    return startPoint;
}

/**
 * the method returns the trip's end position
 * @return endPoint
 */
GridPoint* Trip::getEndPosition()
{
    return endPoint;
}

/**
 * the method finds the path of the trip, using the bfs algorithm.
 * @param start
 * @param end
 * @param grid
 */
void Trip::getBFS(GridPoint *start, GridPoint *end, Grid *grid) {

    b.bfsAlgorithm(start, end, grid);

    GridPoint * current = end;

    while(!(current->equalsTO(start))){

        stk.push(current);

        GridPoint *gp = grid->getParentFromGrid(current);

        current = gp;
    }
}

/**
 * an override to the == operator.
 * @param point
 * @return true if the trip is equal to the given trip
 */
bool Trip::operator == (const Trip& other) const
{
    return tripNumber == other.tripNumber;
}

/**
 * an override to the != operator.
 * @param point
 * @return true if the trip is not equal to the given trip
 */
bool Trip::operator != (const Trip& other) const
{
    return tripNumber != other.tripNumber;
}