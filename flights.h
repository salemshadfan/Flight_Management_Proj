#include <iostream>
#include <vector>
#include <string>

#include "Passenger.h"

using namespace std;

class Flight
{
private:
    vector<Passenger> passengerListM;
    std::string flightNumM;
    int numOfRowsM;
    int seatsPerRowM;

public:
    Flight();
    ~Flight();

    void readDataFromFile(const std::string &textFile); // making the assumption that the info in the file is valid
    void displaySeatMap();
    void displayPassengerInformation();
    void addPassenger(const std::string& fName, const std::string& lName, const std::string& phone, int row, char seat);
    void removePassenger(int id);
    void saveDataToFile(const std::string &textFile);

    std::string getFlightNum() const;
    int getNumOfRows() const;
    int getSeatsPerRow() const;
};
