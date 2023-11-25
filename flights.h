#include <iostream>
#include <vector>
#include <string>

#include "Passenger.h"

using namespace std;

class Flight
{
private:
    vector<Passenger> passengerListM;
    string flightNumM;
    int numOfRowsM;
    int seatsPerRowM;

public:
    Flight();
    ~Flight();

    readDataFromFile(const string &textFile); // making the assumption that the info in the file is valid
    displaySeatMap();
    displayPassengerInformation();
    addPassenger(const string& fName, const string& lName, const string& phone, int row, char seat);
    removePassenger(int id);
    saveDataToFile(const string &textFile);

    string getFlightNum() const;
    int getNumOfRows() const;
    int getSeatsPerRow() const;
};
