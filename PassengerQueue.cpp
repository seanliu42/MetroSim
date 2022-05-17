/* 
 * PassengerQueue.cpp
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Implementation of the PassengerQueue interface. The PassengerQueue is built
 * with a vector, and has the standard operations of a queue. It is used to
 * store Passengers.
 * 
 * NOTE: This is implemented using std::vector.
 */

#include <iostream>
#include <string>
#include <vector>
#include "PassengerQueue.h"
using namespace std;

// Purpose: Initializes an empty PassengerQueue 
PassengerQueue::PassengerQueue() {
    
}

// Purpose: Deletes PassengerQueue when it goes out of scope 
PassengerQueue::~PassengerQueue() {

}

// Purpose: Returns, but does not remove, the element at the queue's front 
Passenger PassengerQueue::front() {
    
    if (queue.size() == 0) {
        cerr << "Cannot get the front of an empty queue" << endl;
        exit(EXIT_FAILURE);
    }
    return queue.front();
}

/*    Purpose: Inserts a new passenger at the end of the queue
 * Parameters: a passenger to be stored in the queue
 */
void PassengerQueue::enqueue(Passenger passenger) {
    
        queue.push_back(passenger);    
}

/*    Purpose: Removes the passenger at the end of the queue
 * Parameters: none
 *    Returns: the recently removed passenger 
 */
 
void PassengerQueue::dequeue() {
    
    if (queue.size() == 0) {
        cerr << "Cannot dequeue from of an empty queue" << endl;
        exit(EXIT_FAILURE);
    }
    
    queue.erase(queue.begin());
}

/*    Purpose: Get the number of passengers being stored in the queue
 * Parameters: none
 *    Returns: The number of passengers currently stored in the list
 */
int PassengerQueue::size() {
    
    int waitSize = queue.size();
    return waitSize;
}

/* Purpose: Prints all the Passengers in the PassengerQueue
* Parameters: none
*    Returns: none
*/
void PassengerQueue::print(ostream &output) {
    
     for (int i = 0; i < size(); i++) {
              queue[i].print(output);
     }
}
