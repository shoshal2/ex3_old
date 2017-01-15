//
// Created by leerosset on 14/12/16.
//

#include "GridPoint.h"
#include "GridPoint.h"
#include <iostream>
#include "Point.h"
#include <string>

/**
 * the method returns the distance of the point from another point
 * (this helps in cases of bfs, whe the distance is needed)
 * @return distance
 */
int GridPoint::getDistance() {
    return this->distance;
}

/**
 * the method sets the distance.
 * @param num
 */
void GridPoint::setDistance(int num) {
    this->distance = num + 1;
}


string GridPoint::toString(){
    string xx;
    stringstream ss1;
    ss1 << x;

    string yy;
    stringstream ss2;
    ss2 << y;

    return "(" + ss1.str() + "," + ss2.str() + ")";
}


/**
 * @return true if the point was visited before.
 */
bool GridPoint::isVisited() {
    return this->visited;
}

/**
 * the method marks the point as visited.
 */
void GridPoint::setToVisitedPoint() {
    this->visited = true;
}

/**
 * the method sets the point's parent to the given point
 * @param gp
 */
void GridPoint::setParent(GridPoint *gp) {
    this->parent = gp;
}

/**
 * the method sets the point's neighbor1
 * @param gp
 */
void GridPoint::setNeighbor1(GridPoint *gp){
    this->neighbor1 = gp;
}

/**
 * the method sets the point's neighbor2
 * @param gp
 */
void GridPoint::setNeighbor2(GridPoint *gp){
    this->neighbor2 = gp;
}

/**
 * the method sets the point's neighbor3
 * @param gp
 */
void GridPoint::setNeighbor3(GridPoint *gp){
    this->neighbor3 = gp;
}

/**
 * the method sets the point's neighbor4
 * @param gp
 */
void GridPoint::setNeighbor4(GridPoint *gp){
    this->neighbor4 = gp;
}

/**
 * the method checks if the point is equals to a given point
 * @param other
 * @return
 */
bool GridPoint::equalsTO(GridPoint * other){
    if(other->getX() != getX()){
        return false;
    }
    if(other->getY() != getY()){
        return false;
    }
    return true;
}

/**
 * an override to the == operator.
 * @param gp
 * @return true if the point is equal to the given point
 */
bool GridPoint::operator==(const GridPoint &gp) const{
    if(this->x == gp.x && this->y == gp.y) {
        return true;
    }
    return false;
}

/**
 * an override to the < operator.
 * the comparing goes like this:
 * GridPoint gp1 < gp2 if:
 * gp1.x < gp2.x || (gp1.x == gp2.x && gp1.y < gp2.y)
 * @param gp
 * @return true if the point < than the given point
 */
bool GridPoint::operator<(const GridPoint &gp) const{
    if((this->x < gp.x) || (this->x == gp.x && this->y < gp.y)) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * an override to the > operator.
 * the comparing goes like this:
 * GridPoint gp1 > gp2 if:
 * gp1.x > gp2.x || (gp1.x == gp2.x && gp1.y > gp2.y)
 * @param gp
 * @return true if the point > than the given point
 */
bool GridPoint::operator>(const GridPoint &gp) const{
    if((this->x > gp.x) || (this->x == gp.x && this->y > gp.y)) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * destroy the gridpoint
 */
GridPoint::~GridPoint(){
    if(this->parent != NULL) {
        this->parent = NULL;
    }
    if(this->neighbor1 != NULL){
        this->neighbor1 = NULL;
    }
    if(this->neighbor2 != NULL){
        this->neighbor2 = NULL;
    }
    if(this->neighbor3 != NULL){
        this->neighbor3 = NULL;
    }
    if(this->neighbor4 != NULL){
        this->neighbor4 = NULL;
    }
}