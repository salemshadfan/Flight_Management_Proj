#include "flights.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;



Flight::Flight() {

}

Flight::~Flight() {
}

void Flight::readDataFromFile(const string &textFile) {
    ifstream file(textFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << textFile << endl;
        return;
    }

    string flightNum;
    int numOfRows, seatsPerRow;
    string line;
    bool flightInfoRead = false;

    while (getline(file, line)) {
        istringstream iss(line);
        if (!flightInfoRead) {
            iss >> flightNum >> numOfRows >> seatsPerRow;
            flightInfoRead = true;
            flightNumM = flightNum;
            numOfRowsM = numOfRows;
            seatsPerRowM = seatsPerRow;
            passengerListM.resize(numOfRowsM, vector<Passenger>(seatsPerRow));
        } else {
            string firstName, lastName, phone, seatInfo, id;
            iss >> firstName >> lastName >> phone >> seatInfo >> id;
            int row = stoi(seatInfo.substr(0, seatInfo.size() - 1));
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
            if (!passengerListM[i][j].getId().empty()) {
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
    cout<< "First name \t Last name \t Phone \t Row \t Seat \t ID \n" << endl ;
    cout<< "--------------------------------------------------------" << endl ;
    for(int i = 0 ; i < numOfRowsM ; i++){
        for (int j = 0; j < seatsPerRowM ; j++){
            if (!(passengerListM[i][j].getFirstName().empty() &&
            passengerListM[i][j].getLastName().empty() &&
            passengerListM[i][j].getPhoneNum().empty() &&
            passengerListM[i][j].getId().empty())) {
            cout<< passengerListM[i][j].getFirstName() <<" \t "<<passengerListM[i][j].getLastName() <<" \t "<< passengerListM[i][j].getPhoneNum() <<" \t "<< passengerListM[i][j].getRow() <<" \t "<<'A'+passengerListM[i][j].getCol()-1<<" \t "<< passengerListM[i][j].getId() <<"\n"<< endl ;   
            }    
        }
    }
}

    

void Flight::addPassenger(const string& fName, const string& lName, const string& phone, const string& id  ,int row, char seat) {
    int col = seat - 'A' + 1;
    if(passengerListM[row][col].getId() != ""){
        cout << "Seat " << seat << " in row " << row << " is already occupied." << endl;
        return;
    }
    Passenger newPassenger(fName, lName, phone, id, row, col);
    passengerListM[row][col]= newPassenger;
    


}

void Flight::removePassenger(const string& id) {
    for(int i = 0 ; i < numOfRowsM ; i++){
        for (int j = 0; j < seatsPerRowM ; j++){
            if(passengerListM[i][j].getId() == id){
                
                passengerListM[i][j] = Passenger("", "", "", "", 0, 0);
            }
        }
    }
}

void Flight::saveDataToFile(const string &textFile) {
    ofstream file(textFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << textFile << endl;
        return;
    }

    file << getFlightNum() << " " << getNumOfRows() << " " << getSeatsPerRow() << endl;

    for (size_t i = 0; i < passengerListM.size(); ++i) {
        for (size_t j = 0; j < passengerListM[i].size(); ++j) {
            Passenger& currentPassenger = passengerListM[i][j];
            if (!currentPassenger.getFirstName().empty()) {
                file << currentPassenger.getFirstName() << " "
                     << currentPassenger.getLastName() << " "
                     << currentPassenger.getPhoneNum() << " "
                     << currentPassenger.getRow() << 'A' + currentPassenger.getCol() - 1 << " "
                     << currentPassenger.getId() << endl;
            }
        }
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


