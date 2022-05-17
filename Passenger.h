/* 
 * Passenger.h
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Interface for Passenger. Defines Passenger as a struct, which contains the 
 * Passenger's ID, ARRIVAL station, and DEPARTURE station.
 * 
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);

};

#endif
