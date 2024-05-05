#include <iostream>
#include <string>
#include "../SpreadSheetHdrs/cell.h"

Cell::Cell(int val) : str{std::to_string(val)}
{}

Cell::Cell(double val) : str{std::to_string(val)}
{}

Cell::Cell(std::string val) : str{val}
{}

Cell::Cell(const Cell& rhv) : str{rhv.str}
{}

Cell::Cell(Cell&& rhv) : str{std::move(rhv.str)}
{}

const Cell& Cell::operator=(const Cell& rhv)
{
    str = rhv.str;
    return *this;
}

const Cell& Cell::operator=(Cell&& rhv)
{
    str = std::move(rhv.str);
    return *this;
}

Cell::operator int() const
{
    return std::stoi(str);
}

Cell::operator double() const
{
    return std::stod(str);
}

Cell::operator std::string() const
{
    return str;
}

std::istream& operator>>(std::istream& in, Cell& cell)
{
    std::string str;
    in >> str;
    cell = Cell(str);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
    out << (std::string)cell;
    return out;
}