//
// Created by leerosset on 14/12/16.
//

#include "bfs.h"

/*
 * the method that runs the bfs algorithm.
 * check every point's heighbors, update the parent of a point and its distance
 * the method uses a queue.
 */
void bfs::bfsAlgorithm(GridPoint* start, GridPoint* end, Grid * grid) {
    GridPoint* current = start;
    current->parent = start;
    q.push(current);
    grid->addTOGrid(current);

    while(!q.empty()) {
        q.pop();
        if (!(current->isVisited())){
            //get the point's neighbors
            grid->getNeighbors(current);

            /*
             * for each neighbor, check if it has a parent. if so, it is already
             * in the grid.
             */

            //neighbor 1 - the one to the 9 o'clock direction
            if(current->neighbor1 != NULL) {

                GridPoint * gp1 = grid->getPointFromGrid(current->neighbor1);

                //if neighbor have no father
                if(gp1->parent == NULL) {
                    //set current as parent, and set the distance
                    gp1->parent = current;
                    gp1->setDistance(current->getDistance());
                    q.push(gp1);
                }
            }

            //neighbor 2 - the one to the 12 o'clock direction
            if(current->neighbor2 != NULL) {

                GridPoint * gp2 = grid->getPointFromGrid(current->neighbor2);
                //if neighbor have no father
                if(gp2->parent == NULL) {
                    //set current as parent, and set the distance
                    gp2->parent = current;
                    gp2->setDistance(current->getDistance());
                    q.push(gp2);
                }
            }

            //neighbor 3 - the one to the 3 o'clock direction
            if(current->neighbor3 != NULL) {

                GridPoint * gp3 = grid->getPointFromGrid(current->neighbor3);
                //if neighbor have no father
                if(gp3->parent == NULL) {
                    //set current as parent, and set the distance
                    gp3->parent = current;
                    gp3->setDistance(current->getDistance());
                    q.push(gp3);
                }
            }

            //neighbor 4 - the one to the 6 o'clock direction
            if(current->neighbor4 != NULL) {
                GridPoint * gp4 = grid->getPointFromGrid(current->neighbor4);
                //if neighbor have no father
                if(gp4->parent == NULL){
                    //set current as parent, and set the distance
                    gp4->parent = current;
                    gp4->setDistance(current->getDistance());
                    q.push(gp4);
                }
            }
            //set current as a visited point
            current->setToVisitedPoint();
        }
        /*
         * see the top element, unless the queue is empty.
         */
        if(!q.empty()) {
            current = q.front();
        }

    }
}

/*
 * find the path from start point to the end point.
 * the method starts from the ending point, and goes to its parent, and to its parent and so on,
 * and every point its passes its adds it to a stack. then its pop from the stack in order to get
 * the right path.
 */
void bfs::printPath(GridPoint *start, GridPoint *end, Grid * grid) {
    bfsAlgorithm(start, end, grid);

    GridPoint * current = end;

    while(!(current->equalsTO(start))){

        stk.push(current);

        GridPoint *gp = grid->getParentFromGrid(current);

        current = gp;
    }
    stk.push(start);
    while(!(stk.empty())) {
        current = stk.top();
        current->print();
        stk.pop();
    }
}

bfs::~bfs() {
}