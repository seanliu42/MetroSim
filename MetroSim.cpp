/* 
 * MetroSim.cpp
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Implementation of the MetroSim interface. MetroSim consists of vectors of
 * PassengerQueues, which are the stations and the train. It also has a
 * vector of strings, which contains the station names. Its functions,
 * help run the program, by executing commands through user/file input and 
 * printing the simulation to the console.
 * 
 * NOTE: This is implemented using std::vector.
 */

#include <iostream>
#include "MetroSim.h"

using namespace std;

// Purpose: Default constructor
MetroSim::MetroSim() {
    
    currentStation = 0; 
    passengerID = 1; 
}

// Purpose: Second constructor with a specific output file
MetroSim::MetroSim(string filename) {
    
    currentStation = 0;
    passengerID = 1;
    
    output_file.open(filename); 
    
    // Print error statement and close program with invalid file input
    if (output_file.fail()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
}

// Purpose: Destructor which closes the output file
MetroSim::~MetroSim() {
    
    output_file.close();
}

/* getStations
 *    Purpose: Stores station names from input file into a vector of strings
 * Parameters: Name of the file with the station names
 *    Returns: None
 */
void MetroSim::getStations(string filename) {
    
    ifstream infile;
    infile.open(filename); 
    
    // Print error statement and close program with invalid file input
    if (infile.fail()) { 
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    
    string input;
    // Continually read and store the stations into vectors until file ends
    while(!infile.eof()) {
        getline(infile, input);
        stationNames.push_back(input);
        
        // Create a PassengerQueue for each station in the file 
        // Add them to the vector of stations and train
        PassengerQueue queue;
        stationQueues.push_back(queue);
        train.push_back(queue);
    }

    numStations = stationNames.size() - 1; 
    infile.close();
}

/* printSimulation
 *    Purpose: Prints the MetroSim to console, which entails the list of
 *             stations, location of the train, and all Passengers at a 
 *             station or on the train.
 * Parameters: None
 *    Returns: None
 */
void MetroSim::printSimulation() {
    
    cout << "Passengers on the train: {";
    // Print every Passenger in the train list
    for (int i = 0; i < numStations; i++) {
        train.at(i).print(cout);
    }
    cout << "}" << endl;
    
    for (int i = 0; i < numStations; i++) { 
        // Print an indicator of which station the train is currently at
        if (i == currentStation) {
            cout << "TRAIN: ";
        } 
        else {
            cout << "       ";
        } 
        
        // Print the station name and their PassengerQueues
        cout << "[" << i + 1 << "] " << stationNames.at(i) << " {";
        stationQueues.at(i).print(cout);
        cout << "}" << endl;
    }
}

/* addToStation
 *    Purpose: Add a Passenger to their FROM station
 * Parameters: Passenger to be enqueued and their station number
 *    Returns: None
 */
void MetroSim::addToStation(Passenger passenger, int station) {
    
    stationQueues.at(station-1).enqueue(passenger);
}

/* metroMove
 *    Purpose: Boards all Passengers at the current station, moves the train 
 *             to the next station and detrains all Passengers going there
 * Parameters: None
 *    Returns: None
 */
void MetroSim::metroMove() {
    
    board(currentStation); // Board all Passengers at the current station
    
    currentStation++; // Move train to the next station
    
    // Return to first station at the end of the line
    if (currentStation == numStations) { 
        currentStation = 0;
    }

    detrain(currentStation); // Detrain all Passengers at the new station 
}

/* userInput
 *    Purpose: Prompt the user to enter commands: "p ARRIVAL DEPARTURE",
 *             "m m", or "m f"
 * Parameters: None
 *    Returns: None
 */
void MetroSim::userInput() {
    
    printSimulation();
    cout << "Command? ";
    
    query(cin); // Query is my helper function for modularity
}

/* fileInput
 *    Purpose: Run the simulation with the commands from the command file
 * Parameters: Name of the command file
 *    Returns: None
 */
void MetroSim::fileInput(string filename) {
    
    ifstream infile;
    infile.open(filename);
    
    // If the file fails to open, cease operations and print error message
    if (infile.fail()) { 
        cerr << "Error: could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    
    printSimulation(); 
    cout << "Command? ";
    
    // Run the query function using the command file
    query(infile); 
    
    infile.close();
}

/* board
 *    Purpose: Helper function which enqueues all passengers from their
 *             stations to the train.
 * Parameters: Station number that Passengers should board
 *    Returns: None
 */
void MetroSim::board(int station) {
    
    int num_boarders = stationQueues.at(station).size();
    
    // Iterate through all Passengers in the station PassengerQueue
    for (int i = 0; i < num_boarders; i++) {
        // Get the Passenger's destination
        int destination = stationQueues.at(station).front().to - 1;
        // Enqueue the Passenger at their destination car on the train
        train.at(destination).enqueue(stationQueues.at(station).front()); 
        // Remove the Passenger from the station queue
        stationQueues.at(station).dequeue();
    }
}

/* detrain
 *    Purpose: Helper function which dequeues all passengers from the train 
 * Parameters: Station number that the Passengers should detrain
 *    Returns: None
 */
void MetroSim::detrain(int station) {
    
    int num_passengers = train.at(station).size();
    
    // Iterate through all of the Passengers on the train car
    for (int i = 0; i < num_passengers; i++) {
        // Get the Passenger's info
        Passenger departer = train.at(station).front();
        // Remove that Passenger from the train
        train.at(station).dequeue();
        // Call outputToFile to print their exit status to the output file
        outputToFile(departer.id, station);
    }    
}

/* invalidInput
 *    Purpose: Prints error statement and exits program for invalid stations
 * Parameters: A Passenger's station numbers
 *    Returns: None
 */
void MetroSim::invalidInput(int from, int to) {
    
    if ((from > numStations) || (to > numStations)) {
        cerr << "Floating exception" << endl; 
        exit(EXIT_FAILURE);
    }
}

/* query
 *    Purpose: Read in the commands from the user or text file, and run the
 *             corresponding functions.
 * Parameters: istream to take inputs from
 *    Returns: None
 *       Note: Assumes commands are formatted correctly. If a command 
 *             is used incorrectly, the program does not function normally
 */
void MetroSim::query(istream &input) {
    
    string letter;
    while(input >> letter) { 
        if (letter == "p") { // If "p ARRIVAL DEPARTURE" command is used
            int from;
            int to;
            input >> from; 
            input >> to;    
            invalidInput(from, to); // Checks if input is valid
            
            // Create the new Passenger and add them to the station
            Passenger new_passenger = Passenger(passengerID, from, to);
            addToStation(new_passenger, from);
            passengerID++; // Increments passngerID for the next Passenger
        } 
        else if (letter == "m") {
            input >> letter;
            if (letter == "m"){ // If "m m" command is used
                metroMove();
            }
            else if (letter == "f") { // If "m f" command is used
                cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
                exit(EXIT_SUCCESS);
            }
        }
        
        printSimulation(); // Update the console of the simulation
        cout << "Command? ";    
    }
}

/* outputToFile
 *    Purpose: Helper function called within detrain(). Sends an update to the
 *             output file noting where a Passenger detrained.
 * Parameters: PassengerID number and their departure station number
 *    Returns: None
 */
void MetroSim::outputToFile(int id, int station) {
    
    output_file << "Passenger " << id << " left train at station ";
    output_file << stationNames.at(station) << endl;
}