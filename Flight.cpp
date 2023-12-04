#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>

#include "Flight.h"

using namespace std;

Flight::Flight() : numOfRowsM(0), seatsPerRowM(0)
{
}

Flight::~Flight()
{
}

void Flight::readDataFromFile(const std::string &textFile)
{
    std::ifstream file(textFile);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << textFile << std::endl;
        return;
    }

    std::string line;
    bool flightInfoRead = false;

    while (getline(file, line))
    {
        std::istringstream iss(line);
        if (!flightInfoRead)
        {
            std::string flightNum;
            int numOfRows, seatsPerRow;
            std::getline(iss, flightNum, '\t');
            iss >> numOfRows >> seatsPerRow;
            flightInfoRead = true;
            flightNumM = flightNum;
            numOfRowsM = numOfRows;
            seatsPerRowM = seatsPerRow;
            seatMap.resize(numOfRowsM, std::vector<Passenger *>(seatsPerRowM, nullptr));
        }
        else
        {
            std::string firstName, lastName, phone, seatInfo, id;
            std::getline(iss, firstName, '\t');
            std::getline(iss, lastName, '\t');
            std::getline(iss, phone, '\t');
            std::getline(iss, seatInfo, '\t');
            std::getline(iss, id, '\t');
            int row = std::stoi(seatInfo.substr(0, seatInfo.size() - 1));
            char col = seatInfo[seatInfo.size() - 1];
            restorePassenger(firstName, lastName, phone, id, row, col);
        }
    }

    file.close();
}

void Flight::displaySeatMap() {
    int maxRow = (numOfRowsM >= 10) ? 2 : 1;

    cout << "Aircraft Seat Map" << endl;
    cout << string(maxRow + 1, ' ');
    for (char c = 'A'; c < 'A' + seatsPerRowM; ++c) {
        cout << "  " << c << " ";
    }
    cout << endl;
    cout << string(maxRow, ' ') << " +";
    for (int i = 0; i < seatsPerRowM; ++i) {
        cout << "---+";
    }
    cout << endl;

    for (int i = 0; i < numOfRowsM; ++i) {
        cout << left << setw(maxRow + 1) << (i + 1) << "|";
        for (int j = 0; j < seatsPerRowM; ++j) {
            if (seatMap[i][j] != nullptr) {
                cout << " X |";
            } else {
                cout << "   |";
            }
        }
        cout << endl;
        cout << string(maxRow, ' ') << " +";
        for (int k = 0; k < seatsPerRowM; ++k) {
            cout << "---+";
        }
        cout << endl;
    }
}

void Flight::displayPassengerInformation()
{
    std::cout << std::left;
    std::cout << std::setw(16) << "\nFirst name"
              << std::setw(16) << "Last name"
              << std::setw(16) << "Phone"
              << std::setw(5) << "Row"
              << std::setw(5) << "Seat"
              << std::setw(6) << "ID" << std::endl;

    std::cout << "---------------------------------------------------------------" << std::endl;

    for (const Passenger &passenger : passengerListM)
    {
        std::cout << std::setw(16) << passenger.getFirstName()
                  << std::setw(16) << passenger.getLastName()
                  << std::setw(16) << passenger.getPhoneNum()
                  << std::setw(5) << passenger.getRow()
                  << std::setw(5) << static_cast<char>('A' + passenger.getCol() - 1)
                  << std::setw(6) << passenger.getId() << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
    }
    std::cout << endl;
}

void Flight::restorePassenger(const string &fName, const string &lName, const string &phone, const string &id, int row, char seat)
{
    int col = seat - 'A' + 1;
    Passenger newPassenger(fName, lName, phone, id, row, col);
    passengerListM.push_back(newPassenger);
    seatMap[row - 1][col - 1] = &passengerListM.back();
}

void Flight::addPassenger()
{
    string fName, lName, phone, id;
    int row;
    char seat;
    bool validInput = false;

    std::cout << "\nEnter the passenger's first name: ";
    std::getline(std::cin, fName);

    std::cout << "Enter the passenger's last name: ";
    std::getline(std::cin, lName);

    std::cout << "Enter the passenger's phone number: ";
    std::getline(std::cin, phone);

    // std::cout << "Enter the passenger's ID: ";
    // std::cin >> id;

    bool idExists;
    do {
        idExists = false;
        cout << "Enter the passenger's ID: ";
        std::getline(std::cin, id);

        for (const Passenger& passenger : passengerListM) {
            if (passenger.getId() == id) {
                idExists = true;
                std::cin.clear();
                cout << "ID already exists. Please enter a different ID." << endl;
                break;
            }
        }
    } while (idExists);

    do
    {
        std::cout << "Enter the passenger's desired row: ";
        string rowInput;
        std::getline(std::cin, rowInput);

        validInput = true;
        for (char c : rowInput)
        {
            if (!isdigit(c))
            {
                validInput = false;
                std::cout << "\nPlease enter a valid integer for the row (1-" << numOfRowsM << ").\n"
                          << endl;
                break;
            }
        }

        if (validInput)
        {
            row = stoi(rowInput);
            if (row < 1 || row > numOfRowsM)
            {
                std::cout << "\nInvalid seat position. Please enter a row between 1 and " << numOfRowsM << ".\n"
                          << endl;
                validInput = false;
            }
        }
        else
        {
            std::cin.clear();
        }
    } while (!validInput);

    do
    {
        validInput = true;
        std::cout << "Enter the passenger's desired seat: ";
        std::cin >> seat;
        std::cout << endl;
        int col = seat - 'A' + 1;
        if (col < 0 || col > (seatsPerRowM + 1))
        {
            std::cout << "Invalid seat position. Please enter a valid seat.\n"
                      << endl;
            validInput = false;
        }

    } while (!validInput);

    int col = seat - 'A' + 1;
    if (seatMap[row - 1][col - 1] != nullptr)
    {
        std::cout << "Seat " << seat << " in row " << row << " is already occupied.\n"
                  << endl;
        return;
    }

    Passenger newPassenger(fName, lName, phone, id, row, col);
    passengerListM.push_back(newPassenger);
    seatMap[row - 1][col - 1] = &passengerListM.back();
}

void Flight::removePassenger(const std::string &id)
{
    for (int i = 0; i < passengerListM.size(); ++i)
    {

        if (passengerListM[i].getId() == id)
        {
            int row = passengerListM[i].getRow() - 1;
            int col = passengerListM[i].getCol() - 1;
            if (row >= 0 && row < numOfRowsM && col >= 0 && col < seatsPerRowM)
            {
                seatMap[row][col] = nullptr;
            }
            passengerListM.erase(passengerListM.begin() + i);
            std::cout << "\nPassenger with ID " << id << " removed successfully.\n"
                      << endl;
            return;
        }
    }
    std::cout << "\nPassenger with ID " << id << " not found.\n"
              << endl;
}

void Flight::saveDataToFile(const string &textFile)
{
    ofstream file(textFile);
    if (!file.is_open())
    {
        cerr << "\nError opening file: " << textFile << endl;
        return;
    }

    file << getFlightNum() << "\t" << getNumOfRows() << "\t" << getSeatsPerRow() << endl;

    for (const Passenger &currentPassenger : passengerListM)
    {
        file << currentPassenger.getFirstName() << "\t"
             << currentPassenger.getLastName() << "\t"
             << currentPassenger.getPhoneNum() << "\t"
             << currentPassenger.getRow() << static_cast<char>('A' + currentPassenger.getCol() - 1) << "\t"
             << currentPassenger.getId() << endl;
    }

    file.close();
}

string Flight::getFlightNum() const
{
    return flightNumM;
}

int Flight::getNumOfRows() const
{
    return numOfRowsM;
}

int Flight::getSeatsPerRow() const
{
    return seatsPerRowM;
}
