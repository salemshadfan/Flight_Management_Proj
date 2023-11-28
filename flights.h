#include <iostream>
#include <vector>
#include <string>

#ifndef FL_H
#define FL_H

#include "Passenger.h"

using namespace std;

class Flight
{
private:
    vector<Passenger> passengerListM;
    vector<vector<Passenger*>> seatMap;
    std::string flightNumM;
    int numOfRowsM;
    int seatsPerRowM;

public:
    Flight();
    ~Flight();

    void readDataFromFile(const std::string &textFile); // making the assumption that the info in the file is valid
    void displaySeatMap();
    void displayPassengerInformation();
    void addPassenger(const string& fName, const string& lName, const string& phone,  const string& id  ,int row, char seat);
    void removePassenger(const string& id);
    void saveDataToFile(const std::string &textFile);

    std::string getFlightNum() const;
    int getNumOfRows() const;
    int getSeatsPerRow() const;
};

#endif