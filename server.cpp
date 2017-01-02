//
// Created by leerosset on 29/12/16.
//

#include "server.h"
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

int mainS() {
    std::cout << "Hello, from server" << std::endl;

    Udp udp(1, 5555);
    udp.initialize();

    char buffer[1024];
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;
    udp.sendData("sup?");

    std::string serial_str;

    //get the driver from the client
    Driver * driver;
    boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver;


    // support more than one client?
    return 0;
}
