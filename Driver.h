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

using namespace std;
using namespace boost::archive;

class Driver {

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & age;
        ar & experience;
        ar & vahicleId;
        ar & status;
        ar & satisfaction;
        ar & costumers;
        //ar & taxi;
        ar & position;
        //ar & trip;
    }

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
    Driver(int id, int age, char status, int experience, int vahicleId);
    Driver() : id(0), age(0), status(0), experience(0), vahicleId(0){}
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