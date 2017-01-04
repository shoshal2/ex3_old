/*
 * MainFlow.cpp
 *
 *  Created on: Dec 11, 2016
 *      Author: mahmuds
 */


#include "TaxiCenter.h"
#include "Obstacle.h"
#include <iostream>
#include <string>
#include "Driver.h"
#include "Trip.h"
#include "TaxiCab.h"
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
#include "Udp.h"
#include <unistd.h>


using namespace std;


// take the input string and add a new driver to taxiCanter
void helperAddDriver(string str, TaxiCenter* center);

// take the input string and add a new Trip to taxiCanter
void helperAddTrip(string str, TaxiCenter* center);

// take the input string and add a new Taxi to taxiCanter
void helperAddTaxi(string str, TaxiCenter* center);

/**
 * the method sends the position of the driver to the client
 * (the trip information)
 * @param center
 */
void sendPositionToClient(TaxiCenter* center, int time, Socket* soc);

// take the input string and add a new driver to taxiCanter
void helperAddDriver(string str, TaxiCenter* center){

    int id;
    int age;
    char status;
    int experience;
    int vahicleId;


    for (unsigned int i=0; i < str.size(); i++)
    {
        if (str[i] == ',') {
            str[i] = ' ';
        }
    }

    str.size();
    stringstream ss(str);

    ss >> id;
    ss >> age;
    ss >> status;
    ss >> experience;
    ss >> vahicleId;

    center->insertDriver(id, age, status, experience, vahicleId);
}

// take the input string and add a new Trip to taxiCanter
void helperAddTrip(string str, TaxiCenter* center, Grid * g){

    int id;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int passenger;
    int time;
    double tarriff;


    for (unsigned int i=0; i < str.size(); i++)
    {
        if (str[i] == ',') {
            str[i] = ' ';
        }
    }

    stringstream ss(str);

    ss >> id;
    ss >> xStart;
    ss >> yStart;
    ss >> xEnd;
    ss >> yEnd;
    ss >> passenger;
    ss >> tarriff;
    ss >> time;

    center->insertTrip(id, xStart, yStart, xEnd, yEnd ,passenger, tarriff, time, g);

}

// take the input string and add a new Taxi to taxiCanter
void helperAddTaxi(string str, TaxiCenter* center){

    int id;
    int type;
    char manufacturer;
    char color;


    for (unsigned int i=0; i < str.size(); i++)
    {
        if (str[i] == ',') {
            str[i] = ' ';
        }
    }

    stringstream ss(str);

    ss >> id;
    ss >> type;
    ss >> manufacturer;
    ss >> color;


    center->insertTaxi(id, type, manufacturer, color);
}

/**
 * the method sends the position of the driver to the client
 * (the trip information)
 * @param center
 */
void sendPositionToClient(TaxiCenter* center, int time, Socket* soc) {

    std::string serial_server_position_str;

    GridPoint * gp;
    std::map<int, Driver*>::iterator itDriver = center->getDrivers()->begin();
    while(itDriver != center->getDrivers()->end()) {
        /*
         * if the time of the driver's trip equals to the method's time,
         * the driver moved.
         */
        if(itDriver->second->getTrip() != NULL) {

            if(itDriver->second->getTrip()->getStartTripDrivingTime() <= time){

                int currentTime = itDriver->second->getTrip()->getTime();
                int startTime = itDriver->second->getTrip()->getStartingTripTime();
                if(currentTime != startTime + 6) {

                    //cout << "sending info to client" << endl;

                    gp = itDriver->second->getPosition();
                    //gp->print();
                    boost::iostreams::back_insert_device<std::string> inserterPosition(serial_server_position_str);
                    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > sServerPosition(inserterPosition);
                    boost::archive::binary_oarchive oaServerPosition(sServerPosition);
                    oaServerPosition << gp;
                    sServerPosition.flush();

                    soc->sendData(serial_server_position_str);
                }
            }
        }
        //get the next driver
        itDriver++;
    }
}

int mains(int argc, char *argv[]){
    std::cout << "Hello, from server" << std::endl;
    TaxiCenter* center = new TaxiCenter();

    int clock = 0; // The Time of the Server

    Socket* socket = new Udp(1, atoi(argv[1]), "127.0.0.1");
    socket->initialize();

    string input = "";
    string format;
    int xSize;
    int ySize;
    int x;
    int y;
    int numOfObstacles;
    Obstacle * obstacle;

    // get the size of the grid
    char gridSize[100];
    cin.getline(gridSize,sizeof(input));

    stringstream ss(gridSize);
    ss >> xSize;
    ss >> ySize;

    // get the size of the obstacles
    cin >> numOfObstacles;
    if(numOfObstacles > 0) {
        obstacle = new Obstacle();

        int i;
        for(i = 0; i < numOfObstacles; i++){
            //get the obstacle's point
            cin >> input;
            for (unsigned int i=0; i < input.size(); i++)
            {
                if (input[i] == ',') {
                    input[i] = ' ';
                }
            }
            stringstream ss(input);
            ss >> x;
            ss >> y;
            GridPoint * ob = new GridPoint(x,y);
            obstacle->addObstacle(ob);
        }
    }

    cin >> input;
    while(input != "7"){

        if(input == "1") {

            cin >> input;
            int numberOfDrivers;
            stringstream ss(input);
            ss >> numberOfDrivers;
            //int numberOfDrivers = stoi(input);

            char buffer[2048];
            socket->reciveData(buffer, sizeof(buffer));
            //cout << buffer << endl;

            Driver * driverFromClient;
            boost::iostreams::basic_array_source<char> deviceServerDriver(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > sServerDriver(deviceServerDriver);
            boost::archive::binary_iarchive iaServerDriver(sServerDriver);
            iaServerDriver >> driverFromClient;

            //cin >>format;
            //helperAddDriver(format, center);

            center->getDrivers()->insert(std::pair<int,Driver*>(driverFromClient->getId(), driverFromClient));


            /*
            while (numberOfDrivers > 0) {
                //cin >> format;
                char buffer[1024];
                socket->reciveData(buffer, sizeof(buffer));
                cout << buffer << endl;
                string format(buffer);
                helperAddDriver(format, center);
                numberOfDrivers--;
            }
*/
            /*
             * send the taxi to the client
             */

            std::string serial_server_cab_str;

            //look for the taxi with the id
            int cabID = driverFromClient->getVahicleId();
            TaxiCab * cab;
            std::map<int,TaxiCab*>::iterator it = center->getCabs()->find(cabID);
            if (it != center->getCabs()->end()) {
                cab = it->second;
            }
            boost::iostreams::back_insert_device<std::string> inserterServerCab(serial_server_cab_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > sServerCab(inserterServerCab);
            boost::archive::binary_oarchive oaServerCab(sServerCab);
            oaServerCab << cab;
            sServerCab.flush();

            socket->sendData(serial_server_cab_str);

        }
        if(input == "2")
        {
            cin >> format;
            Grid * g = new Grid(xSize, ySize, obstacle);

            helperAddTrip(format, center, g);

        }
        if(input == "3")
        {
            cin >> format;
            helperAddTaxi(format, center);

        }
        if(input == "4")
        {
            int id =0;
            cin >> id;
            center->getDriverLocation(id);
        }

        if(input == "7")
        {
            socket->sendData("7");
            break;
        }

        if(input == "9" )
        {


            clock += 1;
            // see if there are trips to be assigned
            center->startDriving(clock);
            // see if there are drivers to be moves
            center->moveTheCab(clock);
            //send to the client any movements of the drivers
            sendPositionToClient(center, clock, socket);
            // see if there are trips to be deleted
            center->deleteTrip();

        }

        cin >> input;
    }
    socket->sendData("7");
    delete(socket);
    delete(center);
    return 0;
}
