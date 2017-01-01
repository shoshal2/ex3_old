//
// Created by leerosset on 29/12/16.
//

#include "client.h"

int mains(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    //cout << argv[1] << endl;

    string input = "";

    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    cin >> input;
    udp.sendData(input);
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;

    return 0;
}
