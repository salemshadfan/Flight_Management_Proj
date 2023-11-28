#include <string>
#include <vector>
#include "airline.h"

using namespace std;


Airline::Airline(){
    airlineName = "";
}


Airline::~Airline(){
   
}


void Airline::addFlight(const Flight& flight){
    flights.push_back(flight);
    airlineName = flight.getFlightNum();
}
