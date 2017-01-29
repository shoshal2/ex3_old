//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_TAXICENTER_H
#define EX3_TAXICENTER_H
#define tripDurance 5

#include <cstddef>
#include <map>
#include "Driver.h"
#include "TaxiCab.h"
#include "Passenger.h"
#include "Trip.h"
#include "bfs.h"
using namespace std;

class TaxiCenter {
private:
    map<int,Driver*>* drivers;
    map<int,TaxiCab*>* cabs;
    map<int,Trip*> *trips;
    map<int,GridPoint> location;

public:
//    map<int,Driver*>* drivers;
//    map<int,TaxiCab*>* cabs;
//    map<int,Trip*> *trips;
//    map<int,GridPoint> location;


    map<int,Driver*>* getDrivers();
    map<int,TaxiCab*>* getCabs();
    map<int,Trip*>* getTrips();

    TaxiCenter();
    ~TaxiCenter();
    //GridPoint * startLoctaion = new GridPoint(0,0);
    void insertDriver(int id, int age,char status,  int experience, int vahicleId, int socId);
    void insertTrip(int id, int xStart, int yStart, int xEnd,int yEnd ,int passenger, double tarriff, int time, Grid * g);
    void insertTaxi(int id, int type, char manufacturer, char color);
    void editDriverLocation(int id, GridPoint * gp);
    void getDriverLocation(int id); // print (x,y)
    void startDriving(int time);
    void moveTheCab(int time);
    void deleteTrip();
    int isDriverExist(int id);
    void exit();


};

#endif //EX3_TAXICENTER_H