#include <iostream>
#include <string>

#ifndef PASS_H
#define PASS_H

#include "Seat.h"

using namespace std;

class Passenger
{
private:
    Seat *seatPtrM;
    std::string fNameM;
    std::string lNameM;
    std::string phoneNumM;
    std::string idM;

public:
    Passenger(std::string fName, std::string lName, std::string phoneNum, std::string id, int row, int col);
    Passenger();
    ~Passenger();

    Passenger(const Passenger &src);
    Passenger &operator=(const Passenger &rhs);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNum() const;
    std::string getId() const;
    int getRow() const;
    int getCol() const;
};

#endif