//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_GRIDPOINT_H
#define EX3_GRIDPOINT_H


using namespace std;
#include "Point.h"
#include <cstddef>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace boost::archive;

class GridPoint: public Point
{

    friend class boost::serialization::access;
    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Point>(*this);
        ar & x;
        ar & y;

    }

private:
    int distance;
    bool visited;
    int x;
    int y;


public:
    GridPoint *parent;
    GridPoint *neighbor1;
    GridPoint *neighbor2;
    GridPoint *neighbor3;
    GridPoint *neighbor4;
    GridPoint(int X, int Y) : Point(X, Y){
        x = X;
        y = Y;
        distance = 0;
        visited = false;
        parent = NULL;
        neighbor1 = NULL;
        neighbor2 = NULL;
        neighbor3 = NULL;
        neighbor4 = NULL;
    };
    GridPoint() : Point(){
        x = -1;
        y = -1;
        distance = 0;
        visited = false;
        parent = NULL;
        neighbor1 = NULL;
        neighbor2 = NULL;
        neighbor3 = NULL;
        neighbor4 = NULL;
    };
    int getDistance();
    void setDistance(int num);
    bool isVisited();
    void setToVisitedPoint();
    void setParent(GridPoint *gp);
    //neighbor to the 9 o'clock direction
    void setNeighbor1(GridPoint *gp);
    //neighbor to the 12 o'clock direction
    void setNeighbor2(GridPoint *gp);
    //neighbor to the 3 o'clock direction
    void setNeighbor3(GridPoint *gp);
    //neighbor to the 6 o'clock direction
    void setNeighbor4(GridPoint *gp);
    bool equalsTO(GridPoint * other);
    string toString();

    bool operator==(const GridPoint & gp) const;
    bool operator<(const GridPoint & gp) const;
    bool operator>(const GridPoint & gp) const;

    ~GridPoint();
};


#endif //EX3_GRIDPOINT_H
