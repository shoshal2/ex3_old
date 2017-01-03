//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_STANDARDCAB_H
#define EX3_STANDARDCAB_H


#include <string>
#include <iostream>
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
#include <boost/serialization/export.hpp>
using namespace std;

#include "TaxiCab.h"

class StandardCab : public TaxiCab{

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<TaxiCab>(*this);
        ar & speed;
    }


public:
    StandardCab(int id, int type, char manufacturer, char color);
    StandardCab();
    ~StandardCab();
    int getFast();
    bool operator == (const StandardCab& other) const;
    bool operator != (const StandardCab& other) const;

};

#endif //EX3_STANDARDCAB_H