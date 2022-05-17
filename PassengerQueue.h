/* 
 * PassengerQueue.h
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Interface for PassengerQueue. Defines PassengerQueue as a class, which 
 * stores Passengers. Its functions are the standard operations of a queue.
 * 
 */

#ifndef _PASSENGERQUEUE_H_
#define _PASSENGERQUEUE_H_


// Put any other necessary includes here

using namespace std;

#include <vector>
#include "Passenger.h"

// Put any other structs you need here

class PassengerQueue
{
public:
    // Constructors
    // Default constructor
     PassengerQueue();
     // Destructor
     ~PassengerQueue();
    
    // PassengerQueue Functions
    // Returns the front Passenger in the PassengerQueue
    Passenger front();
    // Adds a Passenger to the back of the PassengerQueue
    void enqueue(Passenger passenger);
    // Removes the front Passenger of the PassengerQueue
    void dequeue();
    // Returns the size of the PassengerQueue
    int size();
    // Prints the Passengers in the PassengerQueue
    void print(ostream &output);

private:
    vector<Passenger> queue;    

};

#endif
