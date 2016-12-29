//
// Created by leerosset on 29/12/16.
//

#include "client.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;

    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    char buffer[1024];
    udp.sendData("hello");
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;

    return 0;
}