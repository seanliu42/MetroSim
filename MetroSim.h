/* 
 * MetroSim.h
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Interface for MetroSim. Defines MetroSim as a class, which is the main
 * component for this program. Its functions enable the user's commands to
 * be executed. The class stores integers for keeping track of what station
 * the train is at, the amount of stations the train goes to, and the 
 * Passenger ID numbers.
 * 
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"

// Put any other necessary includes here

#include "PassengerQueue.h"

#include <sstream>
#include <fstream>
 
using namespace std;

// Put any other structs you need here

class MetroSim
{
public:
    // Constructors
    // Default constructor
    MetroSim(); 
    // Secondary constructor that outputs to a specific output file
    MetroSim(string output_file); 
    // Destructor
    ~MetroSim(); 
    
    // MetroSim driver functions
    // Gets the station names from the station file and adds it to a queue
    void getStations(string filename);     
    // Helper function used when the simulation commands are from user input
    void userInput();
    // Helper function used when the simulation commands are from a file
    void fileInput(string filename);

private:
    // Vectors of PassengerQueues for the train and the stations
    vector<PassengerQueue> train; 
    vector<PassengerQueue> stationQueues; 
    // Vector of strings for all the station names
    vector<std::string> stationNames;
    
    int currentStation; // Keeps track of where the train is at
    int numStations; // Helps iterate the train through the stations
    int passengerID; // Helps increment passengerID for new Passengers
    
    ofstream output_file; // The output file given by the user
    
    // MetroSim functions
    // Prints simulation to console
    void printSimulation(); 
    // Adds Passengers to their stations
    void addToStation(Passenger passenger, int station);
    // Iterates the train vector and enqueue/dequeues Passengers if needed
    void metroMove();
    // Helper functions for enqueueing and dequeueing passengers
    void board(int station); 
    void detrain(int station);
    // Helper function to call the necessary functions for each user command
    void query(istream &input); 
    // Helper function that prints error messages for invalid inputs
    void invalidInput(int from, int to);
    // Helper function for printing Passenger exit updates to the output file
    void outputToFile(int id, int station); 
    
};

#endif
