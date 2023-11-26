#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "flights.h"
using namespace std;

// define constants
const string flightInfo = "flight_info.txt";

int main()
{
    cout << "Version: 1.0" << endl;
    cout << "Term Project - Flight Management Program in C++" << endl;
    cout << "Produced by: Salem, Tara, Asher" << endl;
    cout << "Year: 2023" << endl;

    Flight flight;
    flight.readDataFromFile(flightInfo);

    int choice;
    do
    {
        cout << "\nPlease select one of the following options:" << endl;
        cout << "1. Display Flight Seat Map" << endl;
        cout << "2. Display Passengers Information" << endl;
        cout << "3. Add a New Passenger" << endl;
        cout << "4. Remove an Existing Passenger" << endl;
        cout << "5. Save data" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice: (1, 2, 3, 4, 5, or 6) ";
        cin >> choice;

        switch (choice) {
            case 1:{
                flight.displaySeatMap();
                break;
            }
            case 2: {
                flight.displayPassengerInformation();
                break;
            }
            case 3: {
                string fName, lName, phone,id;
                int row;
                char seat;
                cout << "Enter the passenger's first name: ";
                cin >> fName;
                cout << "Enter the passenger's last name: ";
                cin >> lName;
                cout << "Enter the passenger's phone number: ";
                cin >> phone;
                cout << "Enter the passenger's ID: ";
                cin >> id;
                cout << "Enter the passenger's desired row: ";
                cin >> row;
                cout << "Enter the passenger's desired seat (A-F): ";
                cin >> seat;
                flight.addPassenger(fName, lName, phone, id ,  row, seat);
                break;
            }
            case 4: {
                string id;
                cout << "Enter the ID of the passenger to be removed: ";
                cin >> id;
                flight.removePassenger(id);
                break;
            }
            case 5: {
                flight.saveDataToFile(flightInfo);
                break;
            }
            case 6: {
                cout << "Program terminated." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
                break;
        }

    } while (choice != 6);
    return 0;
  
}