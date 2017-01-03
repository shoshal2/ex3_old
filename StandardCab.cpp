//
// Created by leerosset on 14/12/16.
//

#include "StandardCab.h"
#include <string>
#include <iostream>

//using namespace std;



StandardCab::StandardCab(int id, int type, char manufacturer, char color) : TaxiCab(id, type, manufacturer, color){
    this->speed = 1;
}

StandardCab::StandardCab() : TaxiCab(){
    this->speed = 1;
}

/**
 * the method returns the speed of the StandardCab
 * @return speed
 */
int StandardCab::getFast() {
    return speed;
}


/**
 * an override to the == operator.
 * @param other
 * @return true if the StandardCab is equal to the given StandardCab
 */
bool StandardCab::operator == (const StandardCab& other) const{
    return taxiNumber == other.taxiNumber;
}

/**
 * an override to the != operator.
 * @param other
 * @return true if the StandardCab is not equal to the given StandardCab
 */
bool StandardCab::operator != (const StandardCab& other) const{
    return taxiNumber == other.taxiNumber;
}

StandardCab::~StandardCab(){}

BOOST_CLASS_EXPORT(StandardCab)