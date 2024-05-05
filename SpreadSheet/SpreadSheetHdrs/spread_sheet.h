#ifndef __SPREAD_SHEET_H_
#define __SPREAD_SHEET_H_

#include <ostream>
#include <initializer_list>
#include <string>
#include "cell.h"

class SpreadSheet
{
    public:
    using size_type = size_t;

    public:
    SpreadSheet();
    SpreadSheet(size_type);
    SpreadSheet(size_type, size_type);
    SpreadSheet(size_type, size_type, const Cell&);
    SpreadSheet(size_type, std::initializer_list<const Cell>&);
    SpreadSheet(const SpreadSheet&);
    SpreadSheet(SpreadSheet&&);
    ~SpreadSheet();

    const SpreadSheet& operator=(const SpreadSheet&);
    const SpreadSheet& operator=(SpreadSheet&&);

    Cell& at(size_type, size_type);
    const Cell& at(size_type, size_type) const;

    public:
    void clear();
    void add_row(size_type, const Cell&);
    void add_colum(size_type, const Cell&);
    void resize_row(size_type);
    void resize_colum(size_type);
    void resize(size_type, size_type);
    void delete_row(size_type);
    void delete_colum(size_type);

    SpreadSheet slice(size_type, size_type);
    size_type row() const;
    size_type colum() const;

    private:
    Cell** cells;
    size_type x;
    size_type y;
};

std::ostream& operator<<(std::ostream&, const SpreadSheet&);

#endif