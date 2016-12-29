//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_LUXURYCAB_H
#define EX3_LUXURYCAB_H

#include <string>

using namespace std;

#include "TaxiCab.h"



class LuxuryCab : public TaxiCab{


public:
    LuxuryCab(int id, int type, char manufacturer, char color);
    ~LuxuryCab ();
    int getFast();

    bool operator == (const LuxuryCab& other) const;
    bool operator != (const LuxuryCab& other) const;
};

#endif //EX3_LUXURYCAB_H