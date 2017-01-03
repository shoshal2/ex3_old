//
// Created by leerosset on 29/12/16.
//

#include "client.h"
#include "Driver.h"
#include "Trip.h"
#include "TaxiCab.h"
#include "LuxuryCab.h"
#include "StandardCab.h"




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





int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;


    string input = "";
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    Driver *driver;
    GridPoint *point;
    TaxiCab* cab;




    cin >> input;
    driver = helperAddDriver(input);


    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    udp.sendData(serial_str);




    char buffer2[2048];
    udp.reciveData(buffer2, sizeof(buffer2));
    string cab_str(buffer2);
    cout << buffer2 << endl;

    boost::iostreams::basic_array_source<char> device2(cab_str.c_str(), cab_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ia2(s2);
    ia2 >> cab;




    while(true) {
        char buffer1[2048];
        udp.reciveData(buffer1, sizeof(buffer1));
        string point_str(buffer1);
        cout << buffer1 << endl;

        if(point_str == "7")
            break;

        boost::iostreams::basic_array_source<char> device1(point_str.c_str(), point_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
        boost::archive::binary_iarchive ia1(s1);
        ia1 >> point;
    }


    return 0;
}
