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
#include <sstream>


#include "src/Udp.h"
#include <unistd.h>
using namespace std;


// take the input string and add a new driver to taxiCanter
void helperAddDriver(string str, TaxiCenter* center);
// take the input string and add a new Trip to taxiCanter
void helperAddTrip(string str, TaxiCenter* center);
// take the input string and add a new Taxi to taxiCanter
void helperAddTaxi(string str, TaxiCenter* center);



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

int main(int argc, char *argv[]){
    std::cout << "Hello, from server\n" << std::endl;
    TaxiCenter* center = new TaxiCenter();

    int clock = 0; // The Time of the Server
    int countMove = 0;
    Socket* socket = new Udp(1, atoi(argv[1]));
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
    //cin >> input;
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
            int numberOfDrivers = stoi(input);

            while (numberOfDrivers > 0) {
                //cin >> format;
                char buffer[1024];
                socket->reciveData(buffer, sizeof(buffer));
                cout << buffer << endl;
                string format(buffer);
                helperAddDriver(format, center);
                numberOfDrivers--;
            }

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
            break;
        }

        if(input == "9" && countMove != 0)
        {
            clock += 1;
            cout << "Time: " << clock << endl;
            center->moveTheCab(clock);

        }
        if(input == "9" && countMove == 0)
        {
            countMove++;
            clock += 1;
            cout << "Time: " << clock << endl;
            center->startDriving(clock);
            center->moveTheCab(clock);

        }


        cin >> input;
    }

    delete(center);
    return 0;
}
