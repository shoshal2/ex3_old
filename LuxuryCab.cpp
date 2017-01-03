//
// Created by leerosset on 14/12/16.
//

#include "LuxuryCab.h"
#include <string>
#include <iostream>

LuxuryCab::LuxuryCab(int id, int type, char manufacturer, char color) : TaxiCab(id, type, manufacturer, color){

    this->speed = 2;
}

LuxuryCab::LuxuryCab() : TaxiCab(){
    this->speed = 2;
}

/**
 * the method returns the speed of the LuxuryCab
 * @return speed
 */
int LuxuryCab::getFast() {
    return speed;
}

/**
 * an override to the == operator.
 * @param other
 * @return true if the LuxuryCab is equal to the given LuxuryCab
 */
bool LuxuryCab::operator == (const LuxuryCab& other) const{
    return taxiNumber == other.taxiNumber;
}

/**
 * an override to the != operator.
 * @param other
 * @return true if the LuxuryCab is not equal to the given LuxuryCab
 */
bool LuxuryCab::operator != (const LuxuryCab& other) const{
    return taxiNumber != other.taxiNumber;
}

LuxuryCab::~LuxuryCab (){}

BOOST_CLASS_EXPORT(LuxuryCab)