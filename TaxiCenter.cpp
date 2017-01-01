//
// Created by leerosset on 14/12/16.
//
#include "TaxiCenter.h"

TaxiCenter::TaxiCenter(){
    drivers = new map<int, Driver*>();
    cabs = new map<int, TaxiCab*>();
    trips =  new map<int, Trip*>();
    location = *new map<int, GridPoint>();
}

TaxiCenter::~TaxiCenter() {

    for (map<int, Driver*>::iterator it = drivers->begin(); it != drivers->end(); ++it)
        delete it->second;
    /*
    for (map<int, TaxiCab*>::iterator it = cabs->begin(); it != cabs->end(); ++it)
        delete it->second;
    */
     for (map<int, Trip*>::iterator it = trips->begin(); it != trips->end(); ++it)
        delete it->second;
/*
    for (map<int, GridPoint>::iterator it = location.begin(); it != location.end(); ++it)
        delete &(it->second);
*/
//    drivers->clear();
//    cabs->clear();
//    trips->clear();
//    trips->clear();
    delete drivers;
    delete cabs;
    delete trips;
    //delete &location;
}


map<int,Driver*>* TaxiCenter::getDrivers(){
    return drivers;
}

map<int,TaxiCab*>* TaxiCenter::getCabs(){
    return cabs;
}

map<int,Trip*>* TaxiCenter::getTrips(){
    return trips;
}



/**
 * the method inserts a driver to the map of drivers
 * @param id
 * @param age
 * @param status
 * @param experience
 * @param vahicleId
 */
void TaxiCenter::insertDriver(int id, int age,char status,  int experience, int vahicleId) {

    Driver* newDriver = new Driver(id,age,status,experience, vahicleId);
    drivers->insert ( std::pair<int,Driver*>(id,newDriver) );
    GridPoint * startLoctaion = new GridPoint(0,0);
    location.insert(std::pair<int,GridPoint>(id, *startLoctaion));

}

/**
 * the method inserts a taxi to the map of taxis
 * @param id
 * @param age
 * @param status
 * @param experience
 * @param vahicleId
 */
void TaxiCenter::insertTaxi(int id, int type, char manufacturer, char color){

    if(type == 1){
        StandardCab* stan = new StandardCab(id, type, manufacturer, color);
        cabs->insert ( std::pair<int,TaxiCab*>(id,stan) );
    }
    else{
        LuxuryCab* lux =  new LuxuryCab(id, type, manufacturer, color);
        cabs->insert ( std::pair<int,TaxiCab*>(id,lux));
    }
}

/**
 * the method inserts a trip to the map of trips
 * @param id
 * @param age
 * @param status
 * @param experience
 * @param vahicleId
 */
void TaxiCenter::insertTrip(int id, int xStart, int yStart, int xEnd,int yEnd ,int passenger, double tarriff, int time){
    Trip* trip = new Trip(id, xStart, yStart, xEnd, yEnd ,passenger, tarriff, time);
    trips->insert ( std::pair<int,Trip*>(id,trip));
}

/**
 * the method edits the driver location in the location's map
 * @param id
 * @param gp
 */
void TaxiCenter::editDriverLocation(int id, GridPoint * gp) {
    std::map<int,GridPoint>::iterator it = this->location.find(id);
    if (it != this->location.end())
        it->second = *gp;
}

/**
 * the method prints the driver's location
 * @param id
 */
void TaxiCenter::getDriverLocation(int id) {
    std::map<int,Driver*>::iterator it = this->drivers->find(id);
    it->second->getPosition()->print();
    /*
    std::map<int,GridPoint>::iterator it = this->location.find(id);
    if (it != this->location.end()) {
        it->second.print();
    }
     */
}

/**
 * the method that starts the actual driving: the method assigns the driver
 * to its trip and taxi.
 */
void TaxiCenter::startDriving(int time){
    std::map<int, Trip*>::iterator itTrip = trips->begin();

    std::map<int, Driver*>::iterator itDriver = drivers->begin();
    std::map<int, TaxiCab*>::iterator itTaxi = cabs->begin();

    //loop over the trips, and assign to every trip a driver in the locaion.
    while (itTrip != trips->end()) {
        // if the trip was not assign to a driver
        if(itTrip->second->tripHasADriver() == false) {
            //if the time of the trip arrived
            if(itTrip->second->getTime() == time){
                //starting point of a trip
                GridPoint * gp = itTrip->second->getStartPosition();
                int cabID = 0;
                int driverId = 0;

                while(itDriver != drivers->end()) {
                    GridPoint * dgp = itDriver->second->getPosition();
                    if(*dgp == *gp) {

                        // find the cab and assig it to the driver
                        cabID = itDriver->second->getVahicleId();
                        std::map<int,TaxiCab*>::iterator it = cabs->find(cabID);
                        if (it != this->cabs->end()) {
                            itDriver->second->addTaxi(it->second);
                        }
                    }
                    itDriver++;
                }
            }
            //the trip now has a driver
            itTrip->second->setTripHasADriver();
        }
        itTrip++;
        }

}

/**
 * the method runs over the driver map, and if the driver's trip's time is
 * as the time of the method, the driver start driving/continue driving
 * @param time
 */
void TaxiCenter::moveTheCab(int time) {
    std::map<int, Driver*>::iterator itDriver = drivers->begin();
    while(itDriver != drivers->end()) {
        /*
         * if the time of the driver's trip equals to the method's time,
         * move the driver.
         */
        if(itDriver->second->getTrip()->getTime() == time){
            itDriver->second->move();
        }
        //update the trip's time
        itDriver->second->getTrip()->updateTime();
        //get the next driver
        itDriver++;
    }
}

/**
 * the method deletes the trips which passed their time.
 * (meaning, 5 seconds from the begining of the trip are over)
 */
void TaxiCenter::deleteTrip() {

    std::map<int, Driver*>::iterator itDriver = drivers->begin();

    while(itDriver != drivers->end()) {
        /*
         * if the time of the driver's trip equals to the method's time,
         * move the driver.
         */
        int currentTime = itDriver->second->getTrip()->getTime();
        int startTime = itDriver->second->getTrip()->getStartingTripTime();
        //if the trip passed its duarnce
        if(currentTime == startTime + this->tripDurance){
            //find the trip
            std::map<int,Trip*>::iterator itDelete = trips->find(itDriver->second->getTrip()->getTripId());
            if (itDelete != this->trips->end()) {
                delete(itDelete->second);
                trips->erase(itDelete->first);
            }
        }
        //get the next driver
        itDriver++;
    }
}

//TODO: the next few lines are deleting the trip from the array
/*
 *
        std::map<int,Trip*>::iterator itDelete = trips->find(itTrip->first);
        if (itDelete != this->trips->end()) {
            delete(itTrip->second);
            trips->erase(itTrip->first);
        }
 *
 *
 */

/*
void TaxiCenter::insertDriver(int id, int age,char status,  int experience, int vahicleId) {
    Driver * d = new Driver(id,age,status,experience,vahicleId);
    this->drivers.insert({id,*d});
    this->location.insert({id, *startLoctaion});
}
*/
/*
void TaxiCenter::insertTaxi(int id, int type, char manufacturer, char color){
    TaxiCab * cab = new TaxiCab(id,type,manufacturer,color);
    this->cabs.insert({id, *cab});
}
*/
/*
void TaxiCenter::insertTrip(int id, int xStart, int yStart, int xEnd,int yEnd ,int passenger, double tarriff){
    Trip * trip = new Trip(id,xStart,yStart,xEnd,yEnd,passenger,tarriff);
    this->trips.insert({id,*trip});
}
*/