//
// Created by leerosset on 14/12/16.
//

#include "Driver.h"
#include "bfs.h"
#include <string>
#include <iostream>
using namespace std;





Driver::Driver(int id, int age,char status,  int experience, int vahicleId){

    this->id = id;
    this->age = age;
    this->status = status;
    this->experience = experience;
    this->vahicleId = vahicleId;
    trip = NULL;
    satisfaction = 0;
    costumers = 0;
    taxi = NULL;
    position = new GridPoint(0,0);


}

/**
 * the method destroy the driver
 */
Driver::~Driver(){
    delete taxi;
    delete position;
}

/**
 * the method returns the id of the driver's vahicle.
 * @return vahicleId
 */
int Driver:: getVahicleId() {
    return this->vahicleId;
}

/**
 * the method add a taxi to the driver
 * @param taxi
 */
void Driver::addTaxi(TaxiCab *taxi)
{
    this->taxi = taxi;
}

/**
 * the method add to the drivr's customers satisfaction, the score of the
 * last ride, and calculates the new score.
 * @param score
 */
void Driver::addPassengerScore(int score)
{
    this->satisfaction += score / (costumers+1);
}

/**
 * the method adds a new customers to the total number of customers of the
 * driver.
 * @param costumers
 */
void Driver::addCostumers(int costumers)
{
    this->costumers += costumers;
}

/**
 * the method add a trip to the driver.
 * @param trip
 */
void Driver::addTrip(Trip*  trip) {
    this->trip = trip;
}

/**
 * the method returns the driver's trip.
 * @return trip
 */
Trip* Driver::getTrip() {
    return trip;
}

/**
 * return the age of the driver
 * @return
 */
int Driver::getAge()
{
    return age;
}

/**
 * set the age of the driver.
 * @param age
 */
void Driver::setAge(int age)
{
    this->age = age;
}

/**
 * the method returns the driver's experience.
 * @return experience
 */
int Driver::getExperience()
{
    return experience;
}

/**
 * the method sets the driver's experience.
 * @param experience
 */
void Driver::setExperience(int experience)
{
    this->experience = experience;
}

/**
 * the method returns the driver's id.
 * @return
 */
int Driver::getId()
{
    return id;
}

/**
 * the method sets the driver's id.
 * @param id
 */
void Driver::setId(int id)
{
    this->id = id;
}

/**
 * the method returns the driver's status - married and etc.
 * @return status
 */
char Driver::getStatus()
{
    return status;
}

/**
 * the method sets the driver's status.
 * @param status
 */
void Driver::setStatus(char status)
{
    this->status = status;
}

/**
 * the method returns the satisfaction of the driver (provided by the customers)
 * @return satisfaction
 */
double Driver::getSatisfaction()
{
    return satisfaction;
}

/**
 * the method returns the driver's taxi
 * @return taxi
 */
TaxiCab* Driver::getTaxi()
{
    return this->taxi;
}

/**
 * the method returns the driver's number of costumers.
 * @return costumers
 */
int Driver::getCostumers()
{
    return costumers;
}

/**
 * the method returns the driver's position
 * @return position
 */
GridPoint* Driver::getPosition()
{
    return position;
}

/**
 * the method sets the driver's position
 * @param point
 */
void Driver::setPosition(GridPoint* point)
{
    position = new GridPoint(point->getX(), point->getY());;
}

/**
 * the method returns the trip's tariff
 * @return
 */
double Driver::getTariff() {
    return trip->getTarriff();
}

/**
 * the method moves the driver, according to the path of the trip,
 * and the cab.
 */
void Driver::move() {
    this->setPosition(this->trip->move(this->taxi->getFast()));
}

/**
 * an override to the == operator.
 * @param other
 * @return true if the driver is equal to the given driver
 */
bool Driver::operator == (const Driver& other) const{
    return id == other.id;
}

/**
 * an override to the != operator.
 * @param other
 * @return true if the driver is not equal to the given driver
 */
bool Driver::operator != (const Driver& other) const{
    return id != other.id;
}
