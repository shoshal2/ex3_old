//
// Created by leerosset on 14/12/16.
//

#ifndef EX3_DRIVER_H
#define EX3_DRIVER_H

#include <string>
#include <iostream>
#include "Point.h"
#include "TaxiCab.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
#include "GridPoint.h"
#include "bfs.h"
#include "Grid.h"

using namespace std;

class Driver {

private :
    int id;
    int age;
    int experience;
    int vahicleId;
    char status;
    double satisfaction;
    int costumers;
    TaxiCab *taxi;
    GridPoint* position;
    Trip * trip;


public:
    Driver(int id, int age,char status,  int experience, int vahicleId, Grid * g);

    ~Driver();

    //void move();

    void addTaxi(TaxiCab *taxi);
    void addPassengerScore(int score);
    void addCostumers(int costumers);
    int getAge();
    void setAge(int age);
    int getExperience();
    void setExperience(int experience);
    int getId();
    void setId(int id);
    char getStatus();
    void setStatus(char status);
    double getSatisfaction();
    TaxiCab *getTaxi();
    int getCostumers();
    GridPoint* getPosition();
    void setPosition(GridPoint *point);
    int getVahicleId();
    void addTrip(Trip* trip);
    Trip* getTrip();
    double getTariff();
    void move();
    bool operator == (const Driver& other) const;
    bool operator != (const Driver& other) const;


};

#endif //EX3_DRIVER_H