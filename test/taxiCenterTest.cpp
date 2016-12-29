////
//// Created by leerosset on 18/12/16.
////
//
//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include "../Point.h"
//#include "../GridPoint.h"
//#include "../Driver.h"
//#include "../TaxiCab.h"
//#include "../Passenger.h"
//#include "../Trip.h"
//#include "../TaxiCenter.h"
//
//using namespace std;
//using testing::Eq;
//
//TEST(TaxiCenter_BasicTest1, addToDriversCheck) {
//
//    TaxiCenter * c = new TaxiCenter();
//    EXPECT_EQ(c->getDrivers()->size(), 0);
//    EXPECT_EQ(c->getTrips()->size(), 0);
//    EXPECT_EQ(c->getCabs()->size(), 0);
//    c->insertDriver(1,35, 'S', 10, 1);
//    c->insertDriver(2,35, 'S', 10, 1);
//    c->insertDriver(3,35, 'S', 10, 1);
//    EXPECT_EQ(c->getDrivers()->size(), 3);
//    EXPECT_EQ(c->getTrips()->size(), 0);
//    EXPECT_EQ(c->getCabs()->size(), 0);
//
//}
//
//
//
//
//TEST(TaxiCenter_BasicTest2, addCheck) {
//
//    TaxiCenter* c = new TaxiCenter();
//
//    c->insertDriver(1,35, 'S', 10, 1);
//    c->insertDriver(2,35, 'S', 10, 1);
//    c->insertDriver(3,35, 'S', 10, 1);
//
//
//    EXPECT_EQ(c->getDrivers()->size(), 3);
//    EXPECT_EQ(c->getTrips()->size(), 0);
//    EXPECT_EQ(c->getCabs()->size(), 0);
//
//    c->insertTrip(1, 0, 0, 3,3 ,5, 100);
//    c->insertTrip(2, 0, 0, 3,3 ,5, 100);
//
//    EXPECT_EQ(c->getDrivers()->size(), 3);
//    EXPECT_EQ(c->getTrips()->size(), 2);
//    EXPECT_EQ(c->getCabs()->size(), 0);
//
//
//}
//
//
//TEST(TaxiCenter_BasicTest3, addCheck) {
//
//    TaxiCenter* c = new TaxiCenter();
//
//    c->insertTaxi(1, 1, 'H', 'G');
//    c->insertTaxi(2, 2, 'S', 'R');
//
//    EXPECT_EQ(c->getCabs()->size(), 2);
//
//}
//
//
//TEST(TaxiCenter_BasicTest2, drivingCheck) {
//
//    TaxiCenter* c = new TaxiCenter();
//
//    c->insertDriver(1,35, 'S', 10, 1);
//    c->insertTrip(1, 0, 0, 3,3 ,5, 100);
//    c->insertTaxi(1, 1, 'H', 'G');
//
//    c->startDriving();
//
//    EXPECT_EQ(c->getDrivers()->size(), 1);
//    EXPECT_EQ(c->getTrips()->size(), 0);
//    EXPECT_EQ(c->getCabs()->size(), 1);
//
//
//}
//
//TEST(TaxiCenter_BasicTest3, getDriverLocation) {
//    TaxiCenter* c = new TaxiCenter();
//    c->insertDriver(1,35, 'S', 10, 1);
//
//    testing::internal::CaptureStdout();
//    std::map<int,Driver*>::iterator it = c->getDrivers()->find(1);
//    c->getDriverLocation(it->first);
//    std::string ActualOut = testing::internal::GetCapturedStdout();
//    EXPECT_STREQ("(0,0)\n", ActualOut.c_str());
//
//}
