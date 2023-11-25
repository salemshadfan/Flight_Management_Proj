#include <iostream>

using namespace std;

class Seat
{
private:
    int rowM;
    int colM;

public:
    Seat(int row, int col);

    int getRow() const;
    int getCol() const;

    void setRow(int row);
    void setCol(int col);
};
