//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_LUXURYCAB_H
#define EX3_LUXURYCAB_H



using namespace std;
#include <string>
#include "TaxiCab.h"
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


class LuxuryCab : public TaxiCab{

    friend class boost::serialization::access;
    template<class Archive>

    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<TaxiCab>(*this);
        ar & this->speed;
    }

public:
    LuxuryCab(int id, int type, char manufacturer, char color);
    LuxuryCab();
    ~LuxuryCab ();
    int getFast();

    bool operator == (const LuxuryCab& other) const;
    bool operator != (const LuxuryCab& other) const;
};

#endif //EX3_LUXURYCAB_H