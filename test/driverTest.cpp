////
//// Created by leerosset on 18/12/16.
////
//
//# include <gtest/gtest.h>
//# include "../Driver.h"
//# include "../LuxuryCab.h"
//# include "../Point.h"
//# include <cstddef>
//
//using namespace std;
//
///*
//TEST(Driver_BasicTest, SanityChecks1) {
//
//Driver d1(1,20,'M',1, 1);
//Driver d2(2,40,'M', 10,2);
//
//EXPECT_EQ(d1.getId(), 1);
//EXPECT_EQ(d2.getId(), 2);
//EXPECT_NE(d2.getAge(), d1.getAge());
//EXPECT_EQ(d2.getExperience(), 10);
//EXPECT_EQ(d2.getAge(), 40);
//EXPECT_EQ(d2.getStatus(), d1.getStatus());
//EXPECT_EQ(d1.getCostumers(), 0);
//d1.addCostumers(3);
//EXPECT_EQ(d1.getCostumers(), 3);
//
//}
//
//TEST(Driver_BasicTest, SanityChecks2) {
//
//Driver d1(3,20,'S',1, 1);
//
//
//EXPECT_EQ(d1.getId(), 3);
//d1.setAge(50);
//EXPECT_EQ(d1.getAge(), 50);
//d1.setExperience(10);
//EXPECT_NE(d1.getExperience(), 1);
//d1.setStatus('M');
//EXPECT_EQ(d1.getStatus(), 'M');
//
//}
//
//
//TEST(Driver_BasicTest, SanityFunctionChecks) {
//Driver d1(3,40,'M',11, 1);
//Driver d2(4,45,'M',19, 2);
//
//
//
//EXPECT_TRUE(d1.getTaxi() == NULL);
//EXPECT_EQ(d2.getSatisfaction(), 0);
//EXPECT_EQ(d2.getCostumers(), 0);
//d2.addCostumers(5);
//EXPECT_EQ(d2.getCostumers(), 5);
//d2.addCostumers(5);
//EXPECT_EQ(d2.getCostumers(), 10);
//EXPECT_FALSE(d2.getPosition() ==  NULL);
//d2.addCostumers(5);
//EXPECT_EQ(d2.getCostumers(), 15);
//d2.setStatus('S');
//EXPECT_NE(d2.getStatus(), d1.getStatus());
//
//
//}
//
//
//TEST(Driver_BasicTest, ComplexFunctionChecks) {
//
//Driver d1(3,40,'M',11, 1);
//Driver d2(4,45,'M',19, 2);
//LuxuryCab * taxi = new LuxuryCab(3, 1, 'H', 'R');
//GridPoint * p1 = new GridPoint(5,3);
//
//EXPECT_TRUE(d1.getTaxi() == NULL);
//d1.addTaxi(taxi);
//EXPECT_EQ(d1.getTaxi() ,taxi);
//EXPECT_EQ(d1.getTaxi()->getFast(), 2);
//
//EXPECT_FALSE(d2.getPosition() == NULL);
//d1.setPosition(p1);
//EXPECT_EQ(d1.getPosition(), p1);
//EXPECT_EQ(d1.getPosition()->getX(), 5);
//EXPECT_EQ(d1.getPosition()->getY(), 3);
//}
//*/
//
//TEST(DriverTrip_Test, FunctionSanityChecks) {
//
//Driver d1(1,20,'M',1, 321);
//
//Trip * t1 = new Trip(171,0,0,3,2,4,100);
//
//d1.addTrip(t1);
//EXPECT_EQ(d1.getTrip(), t1);
//
//EXPECT_EQ(d1.getTrip()->getStartPosition()->getX(), 0);
//EXPECT_EQ(d1.getTrip()->getStartPosition()->getY(), 0);
//
//EXPECT_EQ(d1.getTrip()->getEndPosition()->getX(), 3);
//EXPECT_EQ(d1.getTrip()->getEndPosition()->getY(), 2);
//EXPECT_EQ(d1.getTariff() , 100);
//}
//
//
//TEST(StandardCab_Test_DriverTrip, FunctionSanityChecks) {
//
//Driver d1(1,40,'M',12, 111);
//StandardCab st(111,2, 'H', 'B');
//
//Trip * t1 = new Trip (777,1,1,2,1,2,75);
//
//
//d1.addTrip(t1);
//EXPECT_EQ(d1.getTrip(), t1);
//
//EXPECT_EQ(d1.getTrip()->getStartPosition()->getX(), 1);
//EXPECT_EQ(d1.getTrip()->getStartPosition()->getY(), 1);
//
//EXPECT_EQ(d1.getTrip()->getEndPosition()->getX(), 2);
//EXPECT_EQ(d1.getTrip()->getEndPosition()->getY(), 1);
//EXPECT_EQ(d1.getTariff() , 75);
//
//
//}
//
