//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_POINT_H
#define EX3_POINT_H

#include <iostream>

class Point{

public:
    int x;
    int y;
    Point(int X, int Y);
    Point();
    int getX();
    int getY();
    bool equals(Point other);
    void print();

    bool operator==(const Point &point) const;
    bool operator != (const Point &other) const;
};


#endif //EX3_POINT_H
