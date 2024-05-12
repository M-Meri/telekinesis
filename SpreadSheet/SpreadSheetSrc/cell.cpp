#include <iostream>
#include <string>
#include <sstream>
#include "cell.h"

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
        out << vec[i] << ' ';
    }
    return out;
}

Cell::Cell(int val) : str{std::to_string(val)}
{}

Cell::Cell(double val) : str{std::to_string(val)}
{}

Cell::Cell(bool val)
{
    str = (val == true) ? "true" : "false";
}

Cell::Cell(char val) : str{val}
{}

Cell::Cell(const std::vector<int>& vec)
{
    std::stringstream ss;
    ss << vec;
    str = ss.str();
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
    str = (rhv == true) ? "true": "false";
    return *this;
}

const Cell& Cell::operator=(char rhv)
{
    str = rhv;
    return *this;
}

const Cell& Cell::operator=(std::string rhv)
{
    str = rhv;
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& rhv)
{
    std::stringstream ss;
    ss << rhv;
    str = ss.str();
    return *this;
}

Cell::operator int() const
{
    return std::stoi(str);
}

Cell::operator bool() const
{
    return (str == "true") ? true : false;
}

Cell::operator char() const
{
    if(str.size() != 1)
    {
        return '\0';
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

Cell::operator std::vector<int>() const
{
    std::vector<int> vec;
    std::stringstream ss(str);
    ss >> vec;
    return vec;
}

bool operator==(const Cell& lhv, const Cell& rhv)
{
    return static_cast<std::string>(lhv) == static_cast<std::string>(rhv);
}

bool operator!=(const Cell& lhv, const Cell& rhv)
{
    return static_cast<std::string>(lhv) != static_cast<std::string>(rhv);
}

std::istream& operator>>(std::istream& in, Cell& cell)
{
    std::string str;
    in >> str;
    cell = static_cast<Cell>(str);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
    out << static_cast<std::string>(cell);
    return out;
}