//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_BFS_H
#define EX3_BFS_H

#include <queue>
#include <stack>
#include <iostream>
#include "GridPoint.h"
#include "Grid.h"
#include "Point.h"
using namespace std;

class bfs{
private:
    queue <GridPoint*> q;
    stack<GridPoint*> stk;
public:
    void bfsAlgorithm(GridPoint * start, GridPoint* end, Grid * grid);
    void printPath(GridPoint* start, GridPoint* end, Grid * grid);
    ~bfs();
};

#endif //EX3_BFS_H
