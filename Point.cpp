//
// Created by leerosset on 14/12/16.
//

#include <iostream>
#include "Point.h"

Point::Point(int X, int Y){
    x = X;
    y = Y;
}

Point::Point(){
    x = -1;
    y = -1;
}

/**
 * the method returns the x val
 * @return x
 */
int Point::getX(){
    return x;
}

/**
 * the method returns the y val
 * @return y
 */
int Point::getY(){
    return y;
}

/**
 * the methos returns of the point is equal to the given point
 * @param other
 * @return true if so
 */
bool Point::equals(Point other){
    if(other.getX() != getX()){
        return false;
    }
    if(other.getY() != getY()){
        return false;
    }
    return true;
}

/**
 * the method prints the point in the format: (x,y)
 */
void Point::print() {
    std::cout << "(" << x << "," << y << ")" << std::endl;
}

/**
 * an override to the == operator.
 * @param point
 * @return true if the point is equal to the given point
 */
bool Point::operator==(const Point &point) const{
    return this->x == point.x && this->y == point.y;
}

/**
 * an override to the != operator.
 * @param point
 * @return true if the point is not equal to the given point
 */
bool Point::operator != (const Point& point) const{
    return this->x == point.x && this->y == point.y;
}