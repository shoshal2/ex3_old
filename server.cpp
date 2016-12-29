////
//// Created by leerosset on 29/12/16.
////
//
//#include "server.h"
//
//int main() {
//    std::cout << "Hello, from server" << std::endl;
//
//    Udp udp(1, 5555);
//    udp.initialize();
//
//    char buffer[1024];
//    udp.reciveData(buffer, sizeof(buffer));
//    cout << buffer << endl;
//    udp.sendData("sup?");
//
//
//
////    usleep(5000);
//
//    return 0;
//}