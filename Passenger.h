#include <iostream>
#include <string>

#include "Seat.h"

using namespace std;

class Passenger
{
private:
    Seat *seatPtrM;
    string fNameM;
    string lNameM;
    string phoneNumM;
    string idM;

public:
    Passenger(string fName, string lName, string phoneNum, string id, int row, int col);
    ~Passenger();

    Passenger(const Passenger &src);
    Passenger &operator=(const Passenger &rhs);

    string getFirstName() const;
    string getLastName() const;
    string getPhoneNum() const;
    string getId() const;
    int getRow() const;
    int getCol() const;
};
