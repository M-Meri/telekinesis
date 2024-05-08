#ifndef __SPREAD_SHEET_H_
#define __SPREAD_SHEET_H_

#include <ostream>
#include <initializer_list>
#include <string>
#include <iomanip>
#include "cell.h"

class SpreadSheet
{
    public:
    using size_type = size_t;

    private:
    class Row;

    public:
    SpreadSheet();
    SpreadSheet(size_type);
    SpreadSheet(size_type, size_type);
    SpreadSheet(size_type, size_type, const Cell&);
    SpreadSheet(size_type, std::initializer_list<Cell>&);
    SpreadSheet(const SpreadSheet&);
    SpreadSheet(SpreadSheet&&);
    ~SpreadSheet();

    const SpreadSheet& operator=(const SpreadSheet&);
    const SpreadSheet& operator=(SpreadSheet&&);

    Cell& at(size_type, size_type);
    const Cell& at(size_type, size_type) const;
    Row operator[](size_type);
    const Row operator[](size_type) const;

    public:
    void clear() noexcept;
    void add_row(size_type, const Cell&);
    void add_col(size_type, const Cell&);
    void resize_row(size_type);
    void resize_col(size_type);
    void resize(size_type, size_type);
    void delete_row(size_type);
    void delete_col(size_type);
    void removeRows(std::initializer_list<size_type>);
    void removeCols(std::initializer_list<size_type>);
   // void mirrorH();
   // void mirrorV();
   // void mirrorD();
   // void mirrorSD();
   // void rotate(int);

    SpreadSheet slice(size_type, size_type);
    SpreadSheet slice(std::initializer_list<size_type>, std::initializer_list<size_type>) const; 
    size_type row() const;
    size_type column() const;

    private:
    Cell** cells;
    size_type x;
    size_type y;
};

class SpreadSheet::Row
{
    private:
    Cell* ptr;

    public:
    Row() = delete;
    explicit Row(Cell*);

    const Row& operator=(const Row&) = delete;
    const Row& operator=(Row&&) = delete;

    Cell& operator[](size_t);
    const Cell& operator[](size_t) const;
};

bool operator==(const SpreadSheet&, const SpreadSheet&);
bool operator!=(const SpreadSheet&, const SpreadSheet&);
std::ostream& operator<<(std::ostream&, const SpreadSheet&);

#endif