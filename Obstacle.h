//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_OBSTACLE_H
#define EX3_OBSTACLE_H

#include "GridPoint.h"
#include <set>

class Obstacle {
private:
    set <GridPoint> obstacles;

public:

    set <GridPoint> getObstacle();
    void addObstacle(const GridPoint * gp);
    void removeObstacle(GridPoint * gp);
    bool obstacleAtPoint(GridPoint & gp);
   ~Obstacle();

};

#endif //EX3_OBSTACLE_H
