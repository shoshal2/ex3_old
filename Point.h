//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_POINT_H
#define EX3_POINT_H

#include <iostream>
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

class Point{


    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }

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
