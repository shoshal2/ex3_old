//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_GRID_H
#define EX3_GRID_H

using namespace std;
#include "GridPoint.h"
#include "Point.h"
#include "Obstacle.h"
#include <iostream>
class Grid {
private:
public:
    Grid(int sizeX, int sizeY, Obstacle * obstacles);

    int inputSizeX;
    int inputSizeY;

    GridPoint ***grid;

    Obstacle * gridObstacles;

    void getNeighbors(GridPoint *gp);

    void addTOGrid(GridPoint *gp);

    bool checkIfInGrid(GridPoint *gp);

    bool checkIfObstacle(GridPoint *gp);

    void getIt(GridPoint *gp);

    GridPoint * getPointFromGrid(GridPoint *gp);

    GridPoint *getParentFromGrid(GridPoint *gp);

    ~Grid();
};

#endif //EX3_GRID_H
