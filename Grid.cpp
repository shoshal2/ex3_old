//
// Created by leerosset on 14/12/16.
//

#include "Grid.h"
#include "GridPoint.h"
#include "Point.h"
#include "Obstacle.h"
using namespace std;


Grid::Grid(int sizeX, int sizeY, Obstacle *obstacles){

    this->inputSizeX = sizeX;
    this->inputSizeY = sizeY;
    this->gridObstacles = obstacles;
    this->grid = new GridPoint **[sizeX];
    int i;
    int j;
    for(i = 0; i < sizeX; i++){
        this->grid[i] = new GridPoint * [sizeY];
    }

    for(i = 0; i < sizeX; i++) {
        for(j = 0; j < sizeY; j++) {
            this->grid[i][j] = new GridPoint(i,j);
        }
    }
}


/*
 * the method receives a GridPoint. adds it to the Grid.
 * set the point's neighbors.
 * if there is an obstacle in one of the points, the neighbor at the
 * position will be set as NULL.
 */
void Grid::getNeighbors(GridPoint * gp) {

    //add the point to the grid, if it was not added before
    if ((this->grid[gp->getX()][gp->getY()] == NULL)) {
        this->grid[gp->getX()][gp->getY()] = gp;
    }

    /*
     * now create an array of neighbors.
     */
    GridPoint * neighbor1 = NULL;
    GridPoint * neighbor2 = NULL;
    GridPoint * neighbor3 = NULL;
    GridPoint * neighbor4 = NULL;

    /*
 * if the size of the grid is nX1 (meaning one line)
 */
    if(this->inputSizeY == 1) {
        //neighbors can be only to the right of the point.
        if(gp->getX() == 0){
            // point to the 9 o'clock direction
            neighbor1 = NULL;
            // point to the 12 o'clock direction
            neighbor2 = NULL;
            // point to the 3 o'clock direction
            neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
            // point to the 6 o'clock direction
            neighbor4 = NULL;
        }
            //neighbors can be only to the left of the point.
        else if(gp->getX() ==  this->inputSizeX - 1){
            // point to the 9 o'clock direction
            neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
            // point to the 12 o'clock direction
            neighbor2 = NULL;
            // point to the 3 o'clock direction
            neighbor3 = NULL;
            // point to the 6 o'clock direction
            neighbor4 = NULL;
        }
            //neighbors can be only to the left or the right of the point.
        else {
            // point to the 9 o'clock direction
            neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
            // point to the 12 o'clock direction
            neighbor2 = NULL;
            // point to the 3 o'clock direction
            neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
            // point to the 6 o'clock direction
            neighbor4 = NULL;
        }
    }

        /*
         * if the size of the grid is 1Xn (meaning one row)
         */
    else if(this->inputSizeX == 1) {
        //neighbors can be only above the point.
        if(gp->getX() == 0 && gp->getY() == 0){
            // point to the 9 o'clock direction
            neighbor1 = NULL;
            // point to the 12 o'clock direction
            neighbor2 = new GridPoint(gp->getX(),gp->getY() + 1);
            // point to the 3 o'clock direction
            neighbor3 = NULL;
            // point to the 6 o'clock direction
            neighbor4 = NULL;
        }
            //neighbors can be only under the point.
        else if(gp->getY() ==  this->inputSizeY - 1){
            // point to the 9 o'clock direction
            neighbor1 = NULL;
            // point to the 12 o'clock direction
            neighbor2 = NULL;
            // point to the 3 o'clock direction
            neighbor3 = NULL;
            // point to the 6 o'clock direction
            neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);
        }
            //neighbors can be only above or under the point.
        else {
            // point to the 9 o'clock direction
            neighbor1 = NULL;
            // point to the 12 o'clock direction
            neighbor2 = new GridPoint(gp->getX(),gp->getY() + 1);
            // point to the 3 o'clock direction
            neighbor3 = NULL;
            // point to the 6 o'clock direction
            neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);
        }
    }

    //special case 1: if x == 0
    else if (gp->getX() == 0) {
        //neighbors can't be under or to the left of the point.
        if (gp->getY() == 0) {
            // point to the 9 o'clock direction
            neighbor1 = NULL;
            // point to the 12 o'clock direction
            neighbor2 = new GridPoint(gp->getX(),gp->getY() + 1);
            // point to the 3 o'clock direction
            neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
            // point to the 6 o'clock direction
            neighbor4 = NULL;
        }
            // neighbors can't be above or to the left of the point.
        else if (gp->getY() == this->inputSizeY - 1) {
            // point to the 9 o'clock direction
            neighbor1 = NULL;
            // point to the 12 o'clock direction
            neighbor2 = NULL;
            // point to the 3 o'clock direction
            neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
            // point to the 6 o'clock direction
            neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);
        }
            // else neighbors can't be to the left of the point.
        else {
            // point to the 9 o'clock direction
            neighbor1 = NULL;
            // point to the 12 o'clock direction
            neighbor2 = new GridPoint(gp->getX(),gp->getY() + 1);
            // point to the 3 o'clock direction
            neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
            // point to the 6 o'clock direction
            neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);
        }
    }
        //special case 2: if x == size - 1
    else if (gp->getX() == this->inputSizeX - 1) {
        // neighbors can't be under or to the right of the point.
        if (gp->getY() == 0) {
            // point to the 9 o'clock direction
            neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
            // point to the 12 o'clock direction
            neighbor2 = new GridPoint(gp->getX(), gp->getY() + 1);
            // point to the 3 o'clock direction
            neighbor3 = NULL;
            // point to the 6 o'clock direction
            neighbor4 = NULL;
        }
            // neighbors can't be above or to the right of the point.
        else if (gp->getY() == inputSizeY - 1) {
            // point to the 9 o'clock direction
            neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
            // point to the 12 o'clock direction
            neighbor2 = NULL;
            // point to the 3 o'clock direction
            neighbor3 = NULL;
            // point to the 6 o'clock direction
            neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);
        }
            // else neighbors can't be to the right of the point.
        else {
            // point to the 9 o'clock direction
            neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
            // point to the 12 o'clock direction
            neighbor2 = new GridPoint(gp->getX(), gp->getY() + 1);
            // point to the 3 o'clock direction
            neighbor3 = NULL;
            // point to the 6 o'clock direction
            neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);
        }
    }
        //special case 3: if y == size - 1. neighbors can't be above the point.
    else if ((gp->getY() == inputSizeY - 1) && (gp->getX() < inputSizeX - 1) && (gp->getX() > 0)) {
        // point to the 9 o'clock direction
        neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
        // point to the 12 o'clock direction
        neighbor2 = NULL;
        // point to the 3 o'clock direction
        neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
        // point to the 6 o'clock direction
        neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);
    }
        //special case 4: if y == 0. neighbors can't be under the point.
    else if ((gp->getY() == 0)) {
        if (gp->getX() > 0 ) {
            if (gp->getX() < inputSizeX - 1) {
                // point to the 9 o'clock direction
                neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
                // point to the 12 o'clock direction
                neighbor2 = new GridPoint(gp->getX(), gp->getY() + 1);
                // point to the 3 o'clock direction
                neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
                // point to the 6 o'clock direction
                neighbor4 = NULL;
            }
        }

    }
        // else all four directions
    else {
        // point to the 9 o'clock direction
        neighbor1 = new GridPoint(gp->getX() - 1, gp->getY());
        // point to the 12 o'clock direction
        neighbor2 = new GridPoint(gp->getX(), gp->getY() + 1);
        // point to the 3 o'clock direction
        neighbor3 = new GridPoint(gp->getX() + 1, gp->getY());
        // point to the 6 o'clock direction
        neighbor4 = new GridPoint(gp->getX(), gp->getY() - 1);

    }

    /*
     * check if one of the neighbors is an obstacle point - if so, set it back to null.
     */
    if((neighbor1 != NULL) && (this->checkIfObstacle(neighbor1))) {
        neighbor1 = NULL;
    }
    if((neighbor2 != NULL) && (this->checkIfObstacle(neighbor2))) {
        neighbor2 = NULL;
    }
    if((neighbor3 != NULL) && (this->checkIfObstacle(neighbor3))) {
        neighbor3 = NULL;
    }
    if((neighbor4 != NULL) && (this->checkIfObstacle(neighbor4))) {
        neighbor4 = NULL;
    }
    gp->setNeighbor1(neighbor1);
    gp->setNeighbor2(neighbor2);
    gp->setNeighbor3(neighbor3);
    gp->setNeighbor4(neighbor4);
}

/**
 * adds a point to the grid
 * @param gp
 */
void Grid::addTOGrid(GridPoint * gp){
    this->grid[gp->getX()][gp->getY()] = gp;
}

/**
 * the method checks if a given point is in the grid
 * @param gp
 * @return true if so.
 */
bool Grid::checkIfInGrid(GridPoint *gp) {

    if((gp->getX() > this->inputSizeX) || (gp->getX() < 0) ||
       (gp->getY() > this->inputSizeY) || (gp->getY() < 0)) {
        return false;
    }
    if (this->grid[gp->getX()][gp->getY()] != NULL){
        return true;
    }
    return false;
}

/**
 * if the given point is an obstacle, than true is returned.
 * @param gp
 * @return true if there is an obstacle
 */
bool Grid::checkIfObstacle(GridPoint *gp) {
    if(gridObstacles->isEmpt()) {
        return false;
    }
    if(gridObstacles->obstacleAtPoint(*gp) == 1){
        return true;
    }
    else {
        return false;
    }
}

/**
 * the method returns the parent of the given point on the grid
 * @param gp
 * @return the parent
 */
GridPoint * Grid::getParentFromGrid(GridPoint * gp) {
    return this->grid[gp->getX()][gp->getY()]->parent;
}

/**
 * the method returns a point from the grid
 * @param gp
 * @return the point
 */
GridPoint * Grid::getPointFromGrid(GridPoint * gp) {
    return this->grid[gp->getX()][gp->getY()];
}

/**
 * destroy the grid
 */
Grid::~Grid(){
    int i,j;
    for(i = 0; i < this->inputSizeY; ++i)
    {
        for(j = 0; j < this->inputSizeX; ++j) {
            delete(grid[i][j]);
        }
        delete [](grid[i]);
    }
    delete [](grid);
}