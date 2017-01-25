

#include "client.h"
#include "Driver.h"
#include "Trip.h"
#include "TaxiCab.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}



// take the input string and add a new driver to taxiCanter
Driver* helperAddDriver(string str, int* flag){

    int id;
    int age;
    char status;
    int experience;
    int vahicleId;

    int counter = 0;
    for (unsigned int i=0; i < str.size(); i++)
    {
        if (str[i] == ',') {
            counter++;
            str[i] = ' ';
        }
    }

    if(counter != 4){
        *flag = 0;
        return NULL;
    }

    str.size();
    stringstream ss(str);


    stringstream check(str);
    string input;


    check >> input;
    if(!is_digits(input)){
        *flag = 0;
        return NULL;
    }
    ss >> id;
    if(id < 0){
        *flag = 0;
        return NULL;
    }



    check >> input;
    if(!is_digits(input)){
        *flag = 0;
        return NULL;
    }
    ss >> age;
    if(age < 0){
        *flag = 0;
        return NULL;
    }



    check >> input;
    if(is_digits(input)){
        *flag = 0;
        return NULL;
    }
    ss >> status;
    if(status != 'S' && status != 'M' && status != 'D' && status != 'W'){
        *flag = 0;
        return NULL;
    }


    check >> input;
    if(!is_digits(input)){
        *flag = 0;
        return NULL;
    }
    ss >> experience;
    if(experience < 0){
        *flag = 0;
        return NULL;
    }


    check >> input;
    if(!is_digits(input)){
        *flag = 0;
        return NULL;
    }
    ss >> vahicleId;
    if(vahicleId < 0){
        *flag = 0;
        return NULL;
    }

    return new Driver(id, age, status, experience, vahicleId);
}


int mainc(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    string input = "";


    Driver *driver;
    GridPoint *point;
    TaxiCab* cab;

    int flag = 1;
    cin >> input;
    //driver = helperAddDriver(input, &flag);
    helperAddDriver(input, &flag);
    if(flag == 0) {
        return 0;
    }


    Tcp tcp(0, atoi(argv[2]), argv[1]);
    tcp.initialize();


    std::string serial_client_driver_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_client_driver_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    tcp.sendData(serial_client_driver_str, 0);


    char buffer2[2048];
    tcp.reciveData(buffer2, sizeof(buffer2),0);


    std::string serial_cab_str;
    boost::iostreams::basic_array_source<char> deviceClientCab(buffer2, sizeof(buffer2));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > sClientCab(deviceClientCab);
    boost::archive::binary_iarchive iaClientCab(sClientCab);
    iaClientCab >> cab;



    /*
     * the trip in this case is the path the driver needs to follow.
     * meaning: the client recieves the points of the path, as long as the
     * trip continues.
     */
    while(true) {
        char buffer3[2048];
        tcp.reciveData(buffer3, sizeof(buffer3),0);


        if(buffer3[0] == '7')
            break;

        boost::iostreams::basic_array_source<char> deviceClientPoint(buffer3, sizeof(buffer3));
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > sClientPoint(deviceClientPoint);
        boost::archive::binary_iarchive iaClientPoint(sClientPoint);
        iaClientPoint >> point;


    }


    return 0;
}
