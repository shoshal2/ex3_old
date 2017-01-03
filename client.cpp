//
// Created by leerosset on 29/12/16.
//

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
#include "Udp.h"
#include <unistd.h>



// take the input string and add a new driver to taxiCanter
Driver* helperAddDriver(string str){

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

    return new Driver(id, age, status, experience, vahicleId);
}



//BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
//BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");

int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    string input = "";
    //Udp udp(0, 6639);
    Udp udp(0, atoi(argv[2]), argv[1]);
    udp.initialize();

    Driver *driver;
    GridPoint *point;
    TaxiCab* cab;

    cin >> input;
    driver = helperAddDriver(input);


    std::string serial_client_driver_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_client_driver_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    udp.sendData(serial_client_driver_str);



    char buffer2[2048];
    udp.reciveData(buffer2, sizeof(buffer2));
    //string cab_str(buffer2);
    //cout << buffer2 << endl;

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
        udp.reciveData(buffer3, sizeof(buffer3));
        //string point_str(buffer3);

        if(buffer3[0] == '7')
            break;

        boost::iostreams::basic_array_source<char> deviceClientPoint(buffer3, sizeof(buffer3));
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > sClientPoint(deviceClientPoint);
        boost::archive::binary_iarchive iaClientPoint(sClientPoint);
        iaClientPoint >> point;
        cout << "client in point: " << endl;
        point->print();

    }


    return 0;
}
