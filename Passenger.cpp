#include "Passenger.h"

// validation will be done in the flight class

Passenger::Passenger(string fName, string lName, string phoneNum, string id, int row, int col)
    : fNameM(fName), lNameM(lName), phoneNumM(phoneNum), idM(id), seatPtrM(new Seat(row, col)) {}

Passenger::~Passenger()
{
    delete seatPtrM;
}

Passenger::Passenger()
{
}

Passenger::Passenger(const Passenger &src)
    : fNameM(src.fNameM), lNameM(src.lNameM), phoneNumM(src.phoneNumM), idM(src.idM)
{
    seatPtrM = new Seat(src.getRow(), src.getCol());
}

Passenger &Passenger::operator=(const Passenger &rhs)
{
    if (this != &rhs)
    {
        delete seatPtrM;
        seatPtrM = new Seat(rhs.getRow(), rhs.getCol());
        fNameM = rhs.fNameM;
        lNameM = rhs.lNameM;
        phoneNumM = rhs.phoneNumM;
        idM = rhs.idM;
    }
    return *this;
}

string Passenger::getFirstName() const
{
    return fNameM;
}

string Passenger::getLastName() const
{
    return lNameM;
}

string Passenger::getPhoneNum() const
{
    return phoneNumM;
}

string Passenger::getId() const
{
    return idM;
}

int Passenger::getRow() const
{
    return seatPtrM->getRow();
}

int Passenger::getCol() const
{
    return seatPtrM->getCol();
}