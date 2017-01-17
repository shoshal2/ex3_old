//
// Created by leerosset on 14/12/16.
//

#include "Obstacle.h"

Obstacle::Obstacle() {
    bool setIsEmpty = false;
}
/**
 * the method returns the obstacle set
 * @return obstacles.
 */
set <GridPoint> Obstacle::getObstacle() {
    return this->obstacles;
}

/**
 * the method adds an obstacle to the set
 * @param gp - the point that considered as obstacle
 */
void Obstacle::addObstacle(const GridPoint * gp){
    this->obstacles.insert(*gp);
}

/**
 * the method removes a given obstacle from the obstacles set.
 * @param gp
 */
void Obstacle::removeObstacle(GridPoint *gp) {
    this->obstacles.erase(*gp);
}


/**
  * the method returns:
  * 0 - meaning there is no obstacle
  * 1 - there is an obstacle at point
  * (meaning - if the point is in the obstacles' set).
  * @param gp
  * @return 1 if true. 0 otherwise.
  */
bool Obstacle::obstacleAtPoint(GridPoint &gp) {
    if(this->isEmpt()) {
        return false;
    }
    // Search for gp set using find member function (which returns an iterator)
    std::set<GridPoint>::iterator it = obstacles.find(gp);

    if(it != obstacles.end()) {
        return true;
    }
    else {
        return false;
    }
}

void Obstacle::setNotEmpty() {
    this->setIsEmpty = true;
}

bool Obstacle::isEmpt() {
    return this->setIsEmpty;
}
/**
 * the method destroys the set.
 */
Obstacle::~Obstacle(){
    obstacles.clear();
}