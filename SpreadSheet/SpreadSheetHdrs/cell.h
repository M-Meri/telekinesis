#ifndef __CELL_H__
#define __CELL_H_

#include <ostream>
#include <istream>
#include <string>

class Cell
{
    public:
    Cell() = default;
    Cell(std::string);
    Cell(int);
    Cell(double);
    Cell(const Cell&);
    Cell(Cell&&);
    ~Cell() = default;

    const Cell& operator=(const Cell&);
    const Cell& operator=(Cell&&);

    operator int() const;
    operator double() const;
    operator std::string() const;

    private:
    std::string str;
};

std::istream& operator>>(std::istream&, Cell&);
std::ostream& operator<<(std::ostream&, const Cell&);

#endif