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

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
    cout << "  A B C D E F" << endl;
    cout << "+---+---+---+---+---+---+" << endl;

    for (int i = 0; i < numOfRowsM; ++i) {
        if (i < 10) {
            cout << i << " ";
        } else {
            cout << i;
        }
        cout << "|";
        for (int j = 0; j < seatsPerRowM; ++j) {
            cout << " ";
            if (!seatMap[i][j]->getId().empty()) {
                cout << "X";
            } else {
                cout << " ";
            }
            cout << " |";
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
    }
}


    
void Flight::addPassenger(const string& fName, const string& lName, const string& phone, const string& id, int row, char seat) {
    int col = seat - 'A'+ 1;
    if (row < 0 || row > numOfRowsM || col < 0 || col > seatsPerRowM) {
        cout << "Invalid seat position." << endl;
        return;
    }
   
    if (row > 0 && col >= 0 && row <= numOfRowsM && col < seatsPerRowM && seatMap[row - 1][col] != nullptr) {
        cout << "Seat " << seat << " in row " << row << " is already occupied." << endl;
        return;
    }
    Passenger newPassenger(fName, lName, phone, id, row, col);
    passengerListM.push_back(newPassenger);
    seatMap[row][col] = &passengerListM.back();
}


void Flight::removePassenger(const string& id) {
    cout<< "test" << endl;
    for (int i = 1; i < numOfRowsM; ++i) {
        for (int j = 1; j < seatsPerRowM; ++j) {
            if (seatMap[i][j] != nullptr) {
                if(seatMap[i][j]->getId() == id){
                    cout<< i << "space" << j << endl;
                    seatMap[i][j] = nullptr;
                }
            }
        }
    }

    for (size_t i = 0; i < passengerListM.size(); ++i) {
        if (passengerListM[i].getId() == id) {
            passengerListM.erase(passengerListM.begin() + i);
            break;
        }
    }
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


