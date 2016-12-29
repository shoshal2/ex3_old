//
// Created by leerosset on 14/12/16.
//

#include "TaxiCab.h"

TaxiCab::TaxiCab(int id, int type, char manufacturer, char color){
    this->taxiNumber = id;
    this->taxiType = type;
    this->manufacturer = manufacturer;
    this->color = color;
    this->metersPassed = 0;
    this->tariff = 0;

    this->speed = 0;
}

void TaxiCab::move(){
}

/**
 * the method returns the taxi's tariff
 * @return tariff
 */
double TaxiCab::getTariff(){
    return tariff;
}

/**
 * the method returns the taxi's speed
 * @return speed
 */
int TaxiCab::getFast() {
    return speed;
}

/**
 * an override to the == operator.
 * @param point
 * @return true if the TaxiCab is equal to the given TaxiCab
 */
bool TaxiCab::operator == (const TaxiCab& other) const{
    return taxiNumber == other.taxiNumber;
}

/**
 * an override to the != operator.
 * @param point
 * @return true if the point is not equal to the given point
 */
bool TaxiCab::operator != (const TaxiCab& other) const{
    if(this->taxiNumber != other.taxiNumber) {
        return true;
    }
    return false;
}

TaxiCab::~TaxiCab() {
}