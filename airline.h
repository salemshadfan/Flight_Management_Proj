#include <string>
#include <vector>

#include "Flight.h"

class Airline
{
private:
    std::string airlineName;
    std::vector<Flight> flights;

public:
    Airline();
    ~Airline();
    Airline(const std::string &name) : airlineName(name) {}

    void addFlight(const Flight &flight);

    std::string getAirlineName() const
    {
        return airlineName;
    }
};