#include "Seat.h"

Seat::Seat(int row, int col)
    : rowM(row), colM(col) {}

int Seat::getRow() const
{
    return rowM;
}

int Seat::getCol() const
{
    return colM;
}

void Seat::setRow(int row)
{
    rowM = row;
}

void Seat::setCol(int col)
{
    colM = col;
}