#########################################################
#             HOMEWORK 2: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds MetroSim
MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(LDFLAGS) -o MetroSim main.o MetroSim.o PassengerQueue.o Passenger.o
	
# This rule builds PassengerQueue.o
PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h 
	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp

# The below rule will be used by unit_test.
# Please add any other .o files that are needed by PassengerQueue,
# and any other .o files you wish to test. 
unit_test: unit_test_driver.o PassengerQueue.o Passenger.o
	$(CXX) $(CXXFLAGS) $^

# This rule provides your submission 
# NOTE: Don't forget to add any additional files you want to submit to this
#		rule! If you do not add them, they will not be submitted.
provide:
	provide comp15 hw2_MetroSim PassengerQueue.h \
				    PassengerQueue.cpp \
				    Passenger.h Passenger.cpp \
				    unit_tests.h Makefile \
					README main.cpp \
					MetroSim.cpp MetroSim.h \ 
					test1.txt test2.txt \
					test_commands.txt \
					stations.txt testoutput

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
