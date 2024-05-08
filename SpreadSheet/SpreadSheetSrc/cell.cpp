#include <iostream>
#include <string>
#include "../SpreadSheetHdrs/cell.h"

std::istream& operator>>(std::istream& in, std::vector<int>& vec)
{
    vec.clear();
    int tmp;
    while(in >> tmp)
    {
        vec.push_back(tmp);
        if(in.peek() == '\n')
        {
            break;
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec)
{
    for(size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ' ';
    }
    return out;
}

Cell::Cell(int val) : str{std::to_string(val)}
{}

Cell::Cell(double val) : str{std::to_string(val)}
{}

Cell::Cell(bool val) : str{std::to_string(val)}
{}

Cell::Cell(char val) : str{val}
{}

Cell::Cell(const std::vector<int>& vec)
{
    if(!vec.empty())
    {
        str = std::to_string(vec[0]);
        for(size_t i = 1; i < vec.size(); ++i)
        {
            str += std::to_string(vec[i]);
        }
    }
}

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

const Cell& Cell::operator=(int rhv)
{
    str = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(double rhv)
{
    str = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(bool rhv)
{
    str = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(char rhv)
{
    str = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(std::string rhv)
{
    str = rhv;
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& rhv)
{
    str.clear();
    if(!rhv.empty())
    {
        str = std::to_string(rhv[0]);
        for(size_t i = 1; i < rhv.size(); ++i)
        {
            str += std::to_string(rhv[i]);
        }
    }
    return *this;
}

Cell::operator int() const
{
    return std::stoi(str);
}

Cell::operator bool() const
{
    return static_cast<bool>(std::stoi(str));
}

Cell::operator char() const
{
    if(str.size() != 0)
    {
        throw;
    }
    return str[0];
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