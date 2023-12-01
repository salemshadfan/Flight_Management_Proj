#include "flights.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

Flight::Flight() : numOfRowsM(0), seatsPerRowM(0) {
}

Flight::~Flight() {
}

void Flight::readDataFromFile(const std::string &textFile) {
    std::ifstream file(textFile);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << textFile << std::endl;
        return;
    }

    std::string line;
    bool flightInfoRead = false;

    while (getline(file, line)) {
        std::istringstream iss(line);
        if (!flightInfoRead) {
            std::string flightNum;
            int numOfRows, seatsPerRow;
            std::getline(iss, flightNum, '\t');
            iss >> numOfRows >> seatsPerRow;
            flightInfoRead = true;
            flightNumM = flightNum;
            numOfRowsM = numOfRows;
            seatsPerRowM = seatsPerRow;
            seatMap.resize(numOfRowsM, std::vector<Passenger*>(seatsPerRowM, nullptr));
        } else {
            std::string firstName, lastName, phone, seatInfo, id;
            std::getline(iss, firstName, '\t');
            std::getline(iss, lastName, '\t');
            std::getline(iss, phone, '\t');
            std::getline(iss, seatInfo, '\t');
            std::getline(iss, id, '\t');
            int row = std::stoi(seatInfo.substr(0, seatInfo.size() - 1));
            char col = seatInfo[seatInfo.size() - 1];
            addPassenger(firstName, lastName, phone, id, row, col);
        }
    }

    file.close();
}


void Flight::displaySeatMap() {
    cout << "Aircraft Seat Map" << endl;
    cout << "  A   B   C   D   E   F" << endl;
    cout << "+---+---+---+---+---+---+" << endl;

    for (int i = 0; i < numOfRowsM; ++i) {
        cout << i + 1 << "|";
        for (int j = 0; j < seatsPerRowM; ++j) {
            if (seatMap[i][j] != nullptr) {
                cout << " X |"; 
            } else {
                cout << "   |"; 
            }
        }
        cout << endl;
        cout << "+---+---+---+---+---+---+" << endl;
    }
}


void Flight::displayPassengerInformation() {
    std::cout << std::left; 
    std::cout << std::setw(16) << "First name" 
              << std::setw(16) << "Last name" 
              << std::setw(16) << "Phone" 
              << std::setw(5) << "Row" 
              << std::setw(5) << "Seat" 
              << std::setw(6) << "ID" << std::endl;

    std::cout << "---------------------------------------------------------------" << std::endl;

    for (const Passenger& passenger : passengerListM) {
        std::cout << std::setw(16) << passenger.getFirstName()
                  << std::setw(16) << passenger.getLastName()
                  << std::setw(16) << passenger.getPhoneNum()
                  << std::setw(5) << passenger.getRow()
                  << std::setw(5) << static_cast<char>('A' + passenger.getCol() - 1)
                  << std::setw(6) << passenger.getId() << std::endl;
                std::cout << "---------------------------------------------------------------" << std::endl;
    }
}

void Flight::addPassenger(const string& fName, const string& lName, const string& phone, const string& id, int row, char seat) {
    int col = seat - 'A' + 1;
    if (row < 0 || row > numOfRowsM || col < 0 || col > seatsPerRowM) {
        cout << "Invalid seat position." << endl;
        return;
    }
   
    if (seatMap[row-1][col-1] != nullptr) {
        cout << "Seat " << seat << " in row " << row << " is already occupied." << endl;
        return;
    }
    
    Passenger newPassenger(fName, lName, phone, id, row, col);
    passengerListM.push_back(newPassenger);
    seatMap[row-1][col-1] = &passengerListM.back();
}



void Flight::removePassenger(const std::string& id) {
    for (int i = 0; i < passengerListM.size(); ++i) {
        cout << "Checking ID: " << passengerListM[i].getId() <<"- " << id << endl;
        if (passengerListM[i].getId() == id) {
            int row = passengerListM[i].getRow() - 1;
            int col = passengerListM[i].getCol() - 1;
            if (row >= 0 && row < numOfRowsM && col >= 0 && col < seatsPerRowM) {
                seatMap[row][col] = nullptr;
            }
            passengerListM.erase(passengerListM.begin() + i);
            cout << "Passenger with ID " << id << " removed successfully." << endl;
            return;
        }
    }
    cout << "Passenger with ID " << id << " not found." << endl;
}



void Flight::saveDataToFile(const string &textFile) {
    ofstream file(textFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << textFile << endl;
        return;
    }

    file << getFlightNum() << "\t" << getNumOfRows() << "\t" << getSeatsPerRow() << endl;

    for (const Passenger& currentPassenger : passengerListM) {
        file << currentPassenger.getFirstName() << "\t"
             << currentPassenger.getLastName() << "\t"
             << currentPassenger.getPhoneNum() << "\t"
             << currentPassenger.getRow() << static_cast<char>('A' + currentPassenger.getCol() - 1) << "\t"
             << currentPassenger.getId() << endl;
    }

    file.close();
}


string Flight::getFlightNum() const {
    return flightNumM;
}

int Flight::getNumOfRows() const {
    return numOfRowsM;
}

int Flight::getSeatsPerRow() const {
    return seatsPerRowM;
}


