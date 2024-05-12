#ifndef __CELL_H__
#define __CELL_H_

#include <ostream>
#include <istream>
#include <vector>
#include <string>

std::istream& operator>>(std::istream&, std::vector<int>&);
std::ostream& operator<<(std::ostream&, const std::vector<int>&);

class Cell
{
    public:
    Cell() = default;
    Cell(std::string);
    Cell(int);
    Cell(double);
    Cell(bool);
    Cell(char);
    Cell(const std::vector<int>&);
    Cell(const Cell&);
    Cell(Cell&&);
    ~Cell() = default;

    const Cell& operator=(const Cell&);
    const Cell& operator=(Cell&&);  
    const Cell& operator=(int);  
    const Cell& operator=(double);  
    const Cell& operator=(char);  
    const Cell& operator=(bool);  
    const Cell& operator=(std::string);  
    const Cell& operator=(const std::vector<int>&);

    operator int() const;
    operator double() const;
    operator char() const;  
    operator bool() const;
    operator std::string() const;
    operator std::vector<int>() const; 

    private:
    std::string str;
};

bool operator==(const Cell&, const Cell&);
bool operator!=(const Cell&, const Cell&);

std::istream& operator>>(std::istream&, Cell&);
std::ostream& operator<<(std::ostream&, const Cell&);

#endif