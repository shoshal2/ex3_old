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
#include "Tcp.h"
#include <unistd.h>
#include <cstdlib>


using namespace std;

// Multiple arguments to function called by pthread_create()
struct arg_struct {
    int fd;
    TaxiCenter* center;
    Socket* server;
};

// Multiple arguments to function called by pthread_create()
struct arg_struct_trip {
    int xSize;
    int ySize;
    Obstacle * obstacle;
    TaxiCenter* center;
    string* format;
};

bool isDigit(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

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
void helperAddDriver(string str, TaxiCenter* center, int socId){

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

    center->insertDriver(id, age, status, experience, vahicleId, socId);
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
                soc->sendData(itDriver->second->getPosition()->toString(), itDriver->second->getSocId());
            }
        }
        //get the next driver
        itDriver++;
    }
}

int flag = 1;

void *startNewClient(void *threadArg) {

    int tid;
    struct arg_struct* dim = (struct arg_struct*) threadArg;

    tid = dim->fd;

    Socket *mysocket = dim->server;

    char buffer[1024];
    mysocket->reciveData(buffer, sizeof(buffer), tid);

    TaxiCenter* center = dim->center;

    Driver * driverFromClient;
    boost::iostreams::basic_array_source<char> deviceServerDriver(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > sServerDriver(deviceServerDriver);
    boost::archive::binary_iarchive iaServerDriver(sServerDriver);
    iaServerDriver >> driverFromClient;

    center->getDrivers()->insert(std::pair<int,Driver*>(driverFromClient->getId(), driverFromClient));

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

    mysocket->sendData(serial_server_cab_str, tid);

    while(flag) {

    }

    pthread_exit(NULL);
}

void *startNewTripThread(void *threadArg) {

    int tid;
    struct arg_struct_trip* args = (struct arg_struct_trip*) threadArg;

    TaxiCenter* center = args->center;
    string* format = args->format;
    int xSize = args->xSize;
    int ySize = args->ySize;
    Obstacle* obstacle = args->obstacle;

    Grid * g = new Grid(xSize, ySize, obstacle);

    helperAddTrip(*format, center, g);

    pthread_exit(NULL);
}

int checkTripValidity(string str, int xSize, int ySize){

    int id;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int passenger;
    int time;
    double tarriff;
    int counter = 0;

    for (unsigned int i=0; i < str.size(); i++)
    {
        if (str[i] == ',') {
            counter++;
            str[i] = ' ';
        }
    }

    //there were more than 2 numbers
    if (counter > 7) {
        return -1;
    }

    stringstream ss(str);
    stringstream check(str);
    string inputTemp = "";


    ss >> id;
    ss >> xStart;
    ss >> yStart;
    ss >> xEnd;
    ss >> yEnd;
    ss >> passenger;
    ss >> tarriff;
    ss >> time;

    // if the id is invalid

    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(id < 0) {
        return -1;
    }

    // if the xstart of the trip or the xend of the trip are invalid
    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(xStart < 0 || xEnd > xSize - 1) {
        return -1;
    }

    // if the ystart of the trip or the yend of the trip are invalid
    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(yStart < 0 || yEnd > ySize - 1) {
        return -1;
    }

    // if the number of passengers is invalid
    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(passenger < 0) {
        return  -1;
    }

    //if the tariff is invalid
    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(tarriff < 0) {
        return -1;
    }

    // if the trip's starting time is invalid
    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(time <= 0) {
        return -1;
    }

    return 1;
}

int checkTaxiValidity(string str) {

    int id;
    int type;
    char manufacturer;
    char color;
    int counter = 0;

    for (unsigned int i=0; i < str.size(); i++)
    {
        if (str[i] == ',') {
            counter++;
            str[i] = ' ';
        }
    }


    //there were more than 4 inputs
    if (counter > 3) {
        return -1;
    }

    stringstream ss(str);
    stringstream check(str);
    string inputTemp = "";

    ss >> id;
    ss >> type;
    ss >> manufacturer;
    ss >> color;

    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(id < 0) {
        return -1;
    }

    check >> inputTemp;
    if(!isDigit(inputTemp)) {
        return -1;
    }
    if(type != 1 && type != 2){
        return -1;
    }

    if(manufacturer != 'H' && manufacturer != 'S' && manufacturer != 'T'
            && manufacturer != 'F') {
        return -1;
    }

    if(color != 'R' && color != 'B' && color != 'G'
       && color != 'P' && color != 'W') {
        return -1;
    }

    return 1;
}



int mainc(int argc, char *argv[]){
    std::cout << "Hello, from server" << std::endl;
    TaxiCenter* center = new TaxiCenter();

    int clock = 0; // The Time of the Server
    //Socket* socket = new Tcp(1, 90006, "127.0.0.1");
    Socket* socket = new Tcp(1, atoi(argv[1]), "127.0.0.1");
    socket->initialize();

    pthread_t *threads;
    pthread_t *threadTrip;
    int *threadsIdSockets;

    string input = "";
    string format;
    int xSize;
    int ySize;
    int x;
    int y;
    int numOfObstacles;
    int numberOfDrivers;
    Obstacle * obstacle = new Obstacle();
    bool inputsValid = false;

    while (!inputsValid) {
        /*
         * the logic:
         * if one of the inputs will be invalid, then we will change the inputsValid back
         * to be false - meaning the loop must repeat untill all the inputs are valid.
         */
        inputsValid = true;

        // get the size of the grid
        char gridSize[4048];

        cin.getline(gridSize, sizeof(gridSize));

        stringstream ss(gridSize);
        stringstream check(gridSize);
        string inputTemp = "";
        string inputEnd = "";
        int counter = 0;

        for (int i = 0; gridSize[i] != NULL; i++)
            if(gridSize[i] == ' ') {
                counter++;
            }

        //there were more than 2 numbers
        if (counter > 1) {
            cout << "-1" << endl;
            inputsValid = false;
            continue;
        }

        check >> inputTemp;
        if(!isDigit(inputTemp)) {
            cout << "-1" << endl;
            inputsValid = false;
            continue;
        }

        check >> inputTemp;
        if(!isDigit(inputTemp)) {
            cout << "-1" << endl;
            inputsValid = false;
            continue;
        }

        ss >> xSize;
        ss >> ySize;

        // check the validity of the grids size
        if (xSize <= 0 || ySize <= 0) {
            cout << "-1" << endl;
            inputsValid = false;
            continue;
        }

        /*
         * check if the number of obstacle is valid
         */

        // get the size of the obstacles
        char obstaclesNumber[100];
        cin.getline(obstaclesNumber, sizeof(obstaclesNumber));

        stringstream ss1(obstaclesNumber);
        stringstream check1(obstaclesNumber);
        inputTemp = "";
        counter = 0;

        for (int i = 0; obstaclesNumber[i] != NULL; i++)
            if(obstaclesNumber[i] == ' ') {
                counter++;
            }

        //there were more than 1 number
        if (counter > 0) {
            cout << "-1" << endl;
            inputsValid = false;
            continue;
        }

        check1 >> inputTemp;
        if(!isDigit(inputTemp)) {
            cout << "-1" << endl;
            inputsValid = false;
            continue;
        }

        ss1 >> numOfObstacles;


        //check the validity of the obstacle's number
        if (numOfObstacles < 0){
            cout << "-1" << endl;
            inputsValid = false;
            continue;
        }

        if (numOfObstacles > 0) {
            int i;
            counter = 0;
            for (i = 0; i < numOfObstacles; i++) {
                //get the obstacle's point
                cin >> input;
                for (unsigned int i = 0; i < input.size(); i++) {
                    if (input[i] == ',') {
                        counter++;
                        input[i] = ' ';
                    }
                }

                if(counter > 1) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    continue;
                }

                stringstream ss(input);
                stringstream check(input);
                string inputTemp = "";

                check >> inputTemp;
                if(!isDigit(inputTemp)) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    continue;
                }

                check >> inputTemp;
                if(!isDigit(inputTemp)) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    continue;
                }

                ss >> x;
                ss >> y;

                //check the validity of the input
                if((x < 0 || x > xSize - 1)||(y < 0 || y > ySize - 1)) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    continue;
                }
                GridPoint *ob = new GridPoint(x, y);
                obstacle->addObstacle(ob);
            }

            obstacle->setNotEmpty();
        }
        cin >> input;

        while (input != "7") {

            if (input == "1") {

                /*
 * check if the number of obstacle is valid
 */

                // get the size of the obstacles
                char driversNumber[100];
                cin.ignore();
                cin.getline(driversNumber, sizeof(driversNumber));

                stringstream ss1(driversNumber);
                stringstream check1(driversNumber);
                inputTemp = "";
                counter = 0;

                for (int i = 0; driversNumber[i] != NULL; i++)
                    if(driversNumber[i] == ' ') {
                        counter++;
                    }

                //there were more than 1 number
                if (counter > 0) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    input = "7";
                    cin.ignore();
                    break;
                }

                check1 >> inputTemp;
                if(!isDigit(inputTemp)) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    input = "7";
                    cin.ignore();
                    break;
                }

                ss1 >> numberOfDrivers;

                //check the validity of the drivers number
                if(numberOfDrivers <= 0) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    input = "7";
                    cin.ignore();
                    break;
                }

                threads = new pthread_t[numberOfDrivers];
                threadsIdSockets = new int[numberOfDrivers];

                int rc;
                int i = 0;
                int count = numberOfDrivers;
                while (count > 0) {

                    int k = socket->acceptClient();
                    int *new_sock = (int *) malloc(1);
                    *new_sock = k;
                    struct arg_struct *args = (struct arg_struct *) malloc(sizeof(struct arg_struct));
                    args->server = socket;
                    args->center = center;
                    args->fd = k;
                    threadsIdSockets[count - 1] = k;
                    count--;
                    rc = pthread_create(&threads[i], NULL, startNewClient, (void *) args);
                    i++;

                    if (rc) {
                        cout << "Error:unable to create thread," << rc << endl;
                        exit(-1);
                    }
                }

                input = "0";
            }
            if (input == "2") {
                threadTrip = new pthread_t[1];
                cin >> format;
                struct arg_struct_trip *args = (struct arg_struct_trip *) malloc(sizeof(struct arg_struct_trip));
                args->center = center;
                args->format = new string(format);

                // call function that will check if the trips format is invalid.
                int temp = checkTripValidity(format, xSize, ySize);
                // if the temp is negative, then the trip input was invalid
                if(temp < 0) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    input = "7";
                    cin.ignore();
                    break;

                }

                args->xSize = xSize;
                args->ySize = ySize;
                args->obstacle = obstacle;
                int rc = pthread_create(&threadTrip[0], NULL, startNewTripThread, (void *) args);
                if (rc) {
                    cout << "Error:unable to create thread," << rc << endl;
                    exit(-1);
                }
            }
            if (input == "3") {
                cin >> format;
                // check the validity of the taxi
                int temp = checkTaxiValidity(format);
                // if the temp is negative, then the taxi input was invalid
                if(temp < 0) {
                    cout << "-1" << endl;
                    inputsValid = false;
                    input = "7";
                    cin.ignore();
                    break;
                }
                helperAddTaxi(format, center);

            }
            if (input == "4") {
                int id = 0;
                cin >> id;
                center->getDriverLocation(id);
            }
            if (input == "7") {
                break;
            }

            if (input == "9") {
                clock += 1;
                // see if there are trips to be assigned
                center->startDriving(clock);
                // see if there are drivers to be moves
                center->moveTheCab(clock);
                // send to the client any movements of the drivers
                sendPositionToClient(center, clock, socket);
                // see if there are trips to be deleted
                center->deleteTrip();
            }
            cin >> input;
        }
    }
    flag = 0;
    int k = 0;
    while(k < numberOfDrivers){
        socket->sendData("7",threadsIdSockets[k]);
        k++;
    }
    delete(socket);
    delete(center);
    return 0;
}
