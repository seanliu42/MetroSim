/* 
 * Passenger.cpp
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Implementation of the Passenger interface.
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*    Purpose: Print the information of the Passenger
 * Parameters: ostream to output to
 *    Returns: none
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" 
               << to << "]";
}
