//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_TAXICAB_H
#define EX3_TAXICAB_H


#include <cstddef>
#include <iostream>
#include <string>
#include "Trip.h"

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
    virtual ~TaxiCab();


    virtual double getTariff();
    virtual void move();
    int getFast();
    bool operator == (const TaxiCab& other) const;
    bool operator != (const TaxiCab& other) const;
};

#endif //EX3_TAXICAB_H