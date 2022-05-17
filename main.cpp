/* 
 * main.cpp
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Driver for MetroSim, which handles file input and starts the simulation.
 * It checks for the correct program execution in console, reads in data
 * from the input file, and directs output to the output file. If there is a 
 * third input file, it feeds the contents of it into the simulation as 
 * program commands.
 * 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

int main(int argc, char *argv[])
{
    
    // Program fails to run if there are insufficient inputs
    if (argc < 3 or argc > 4) { 
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]\n";
        exit(EXIT_FAILURE);
    }
        
    MetroSim simulation(argv[2]);
    simulation.getStations(argv[1]);

    // If given a command file, run the simulation using it
    if (argc == 4) {
        simulation.fileInput(argv[3]);
    }
    else {
        simulation.userInput();
    }
    
        return 0;
}