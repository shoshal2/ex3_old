//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_STANDARDCAB_H
#define EX3_STANDARDCAB_H


#include <string>
#include <iostream>

using namespace std;

#include "TaxiCab.h"

class StandardCab : public TaxiCab{


public:
    StandardCab(int id, int type, char manufacturer, char color);
    ~StandardCab();
    int getFast();
    bool operator == (const StandardCab& other) const;
    bool operator != (const StandardCab& other) const;

};

#endif //EX3_STANDARDCAB_H