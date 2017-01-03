//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_TAXICAB_H
#define EX3_TAXICAB_H


#include <cstddef>
#include <iostream>
#include <string>
#include "Trip.h"
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

using namespace std;


class TaxiCab {



    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & taxiNumber;
        ar & taxiType;
        ar & manufacturer;
        ar & color;
    }



protected:
    int taxiNumber;
    int taxiType;
    char manufacturer;
    char color;
    int metersPassed;
    int speed;
    double tariff;


public:
    TaxiCab(int id, int type, char manufacturer, char color);
    TaxiCab();
    virtual ~TaxiCab();


    virtual double getTariff();
    virtual void move();
    int getFast();
    bool operator == (const TaxiCab& other) const;
    bool operator != (const TaxiCab& other) const;
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(TaxiCab)
#endif //EX3_TAXICAB_H