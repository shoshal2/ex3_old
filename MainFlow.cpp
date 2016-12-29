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
using namespace std;
std::stringstream ss;

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
void helperAddTrip(string str, TaxiCenter* center){

    int id;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int passenger;
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

    center->insertTrip(id, xStart, yStart, xEnd, yEnd ,passenger, tarriff);

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

int main(){

    TaxiCenter* center = new TaxiCenter();

    string input = "";
    string format;
    int xSize;
    int ySize;
    int x;
    int y;
    int numOfObstacles;

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
        Obstacle * obstacle = new Obstacle();

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

        if(input == "1")
        {
            cin >> format;
            helperAddDriver(format, center);

        }
        if(input == "2")
        {
            cin >> format;
            helperAddTrip(format, center);

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
        if(input == "6")
        {

            center->startDriving();
        }
        if(input == "7")
        {
            break;
        }

        cin >> input;
    }

    delete(center);
    return 0;
}
