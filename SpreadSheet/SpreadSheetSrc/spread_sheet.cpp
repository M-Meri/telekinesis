#include <iostream>
#include <string>
#include <initializer_list>
#include <iomanip>
#include "spread_sheet.h"

SpreadSheet::SpreadSheet():cells{nullptr}, x{0}, y{0}
{}

SpreadSheet::SpreadSheet(size_type rowcols)
    :cells{new Cell*[rowcols]}, x{rowcols}, y{rowcols}
{
    for(size_type i = 0; i < x; ++i)
    {
        cells[i] = new Cell[y];
    }
}

SpreadSheet::SpreadSheet(size_type row, size_type col)
    :cells{new Cell*[row]}, x{row}, y{col}
{
    for(size_type i = 0; i < x; ++i)
    {
        cells[i] = new Cell[y];
    }
}

SpreadSheet::SpreadSheet(size_type row, size_type col, const Cell& val)
    :cells{new Cell*[row]}, x{row}, y{col}
{
    for(size_type i = 0; i < x; ++i)
    {
        cells[i] = new Cell[y];
        for(size_type j = 0; j < y; ++j)
        {
            cells[i][j] = val;
        }
    }
}

SpreadSheet::SpreadSheet(size_type row, std::initializer_list<Cell>& init)
    :cells{new Cell*[row]}, x{row}, y{init.size()}
{
    for(size_type i = 0; i < x; ++i)
    {
        cells[i] = new Cell[y];
        size_type j = 0;
        for(auto& item : init)
        {
            cells[i][j++] = item;
        }
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)
    :cells{new Cell*[rhv.x]}, x{rhv.x}, y{rhv.y}
{
    for(size_type i = 0; i < x; ++i)
    {
        cells[i] = new Cell[y];
        for(size_type j = 0; j < y; ++j)
        {
            cells[i][j] = rhv.cells[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv)
    :cells{rhv.cells}, x{rhv.x}, y{rhv.y}
{
    rhv.cells = nullptr;
    rhv.x = 0;
    rhv.y = 0;
}

SpreadSheet::~SpreadSheet()
{
    clear();
}

void SpreadSheet::clear() noexcept
{
    for(size_type i = 0; i < x; ++i)
    {
        delete[] cells[i];
    }
    delete[] cells;
    x = 0;
    y = 0;
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv)
{
    if(this != &rhv)
    {
        Cell** tmp = new Cell*[rhv.x];
        for(size_type i = 0; i < rhv.x; ++i)
        {
            tmp[i] = new Cell[rhv.y];
            for(size_type j = 0; j < rhv.y; ++j)
            {
                tmp[i][j] = rhv.cells[i][j];
            }
        }
        clear();
        y = rhv.y;
        x = rhv.x;
        cells = tmp;
        tmp = nullptr;
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv)
{
    if(this != &rhv)
    {
        cells = rhv.cells;
        rhv.cells = nullptr;
        rhv.x = 0;
        rhv.y = 0;
    }
    return *this;
}

SpreadSheet::Row SpreadSheet::operator[](size_type row)
{
    return Row(cells[row]);
}

const SpreadSheet::Row SpreadSheet::operator[](size_type row) const
{
    return Row(cells[row]);
}

void SpreadSheet::add_row(size_type index, const Cell& val)
{
    if(index > x)
    {
        throw;
    }
    Cell** tmp = new Cell*[x];
    for(size_type i = 0; i < x + 1; ++i)
    {
        tmp[i] = new Cell[y];
        if(i < index)
        {
            for(size_type j = 0; j < y; ++j)
            {
                tmp[i][j] = cells[i][j];
            }
        }
        else if(i == index)
        {
            for(size_type j = 0; j < y; ++j)
            {
                tmp[i][j] = val;
            }
        }
        else
        {
            for(size_type j = 0; j < y; ++j)
            {
                tmp[i][j] = cells[i - 1][j];
            }
        }
    }
    size_type xtmp = x;
    size_type ytmp = y;
    clear();
    x = xtmp + 1;
    y = ytmp;
    cells = tmp;
    tmp = nullptr;
}

void SpreadSheet::add_col(size_type index, const Cell& val)
{
    if(index > x)
    {
        throw;
    }
    Cell** tmp = new Cell*[x];
    ++y;
    for(size_type i = 0; i < x; ++i)
    {
        tmp[i] = new Cell[y];
        for(size_type j = 0; j < y; ++j)
        {
            if(index == j)
            {
                tmp[i][j] = val;
                continue;
            }
            if(j < index)
            {
                tmp[i][j] = cells[i][j];
                continue;
            }
            tmp[i][j] = cells[i][j-1];
        }
    }
    size_type xtmp = x;
    size_type ytmp = y;
    clear();
    x = xtmp;
    y = ytmp;
    cells = tmp;
    tmp = nullptr;
}

void SpreadSheet::resize_row(size_type cnt)
{
    resize(cnt, y);
}

void SpreadSheet::resize_col(size_type cnt)
{
    resize(x, cnt);
}

void SpreadSheet::resize(size_type row, size_type col)
{
    Cell** tmp = new Cell*[row];
    for(int i = 0; i < row; ++i)
    {
        tmp[i] = new Cell[col];
    }
    for(int i = 0; i < row && i < x; ++i)
    {
        for(int j = 0; j < col && j < y; ++j)
        {
            tmp[i][j] = cells[i][j];
        }
    }
    clear();
    cells = tmp;
    tmp = nullptr;
    x = row;
    y = col;
}

void SpreadSheet::delete_row(size_type row)
{
    if(row >= x)
    {
        throw;
    }
    delete[] cells[row];
    for(size_type i = row; i < x - 1; ++i)
    {
        cells[i] = cells[i + 1];
    }
    --x;
}

void SpreadSheet::removeRows(std::initializer_list<size_type> rows)
{
    for(size_type row : rows)
    {
        delete_row(row);
    }
}

void SpreadSheet::removeCols(std::initializer_list<size_type> cols)
{
    for(size_type col : cols)
    {
        delete_col(col);
    }
}

void SpreadSheet::delete_col(size_type col)
{
    if(col >= y)
    {
        throw;
    }
    for(size_type i = 0; i < x; ++i)
    {
        for(size_type j = col; j < y - 1; ++j)
        {
            cells[i][j] = cells[i][j + 1];
        }
    }
    --y;
}

void SpreadSheet::mirrorH()
{
    for(int i = 0; i < x/2; ++i)
    {
        for(int j = 0; j < y; ++j)
        {
            Cell tmp = cells[i][j];
            cells[i][j] = cells[x - 1 - i][j];
            cells[x - 1 - i][j]  = tmp;
        }
    }
}

void SpreadSheet::rotate(int count)
{
    int cnt = (count >= 0) ? (count % 4) : (-count % 4);
    while(cnt--)
    {
        Cell** tmp = new Cell*[y];
        for(int i = 0; i < y; ++i)
        {
            tmp[i] = new Cell[x];
            for(int j = 0; j < x; ++j)
            {
                tmp[i][j] = cells[x - 1 - j][i];
            }
        }
        size_t newx = y;
        size_t newy = x;
        clear();
        cells = tmp;
        x = newx;
        y = newy;
        tmp = nullptr;
    }
}

void SpreadSheet::mirrorV()
{
    rotate(2);
    mirrorH();
}

void SpreadSheet::mirrorD()
{
    rotate(3);
    mirrorH();
}

void SpreadSheet::mirrorSD()
{
    rotate(1);
    mirrorH();
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_type> rows, std::initializer_list<size_type> cols) const
{
    SpreadSheet tmp{rows.size(), cols.size()};
    size_type i  = 0;
    for(size_type row : rows)
    {
        size_type j = 0;
        for(size_type col : cols)
        {
            tmp[i][j++] = cells[row][col];
        }
        ++i;
    }
    return tmp;
}

SpreadSheet::size_type SpreadSheet::row() const
{
    return x;
}

SpreadSheet::size_type SpreadSheet::column() const
{
    return y;
}

SpreadSheet::Row::Row(Cell* ptr): ptr{ptr}
{}

Cell& SpreadSheet::Row::operator[](size_t col)
{
    return ptr[col];
}

const Cell& SpreadSheet::Row::operator[](size_t col) const
{
    return ptr[col];
}

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv)
{
    if(lhv.row() != rhv.row() || lhv.column() != rhv.column())
    {
        return false;
    }
    for(size_t i = 0; i < rhv.row(); ++i)
    {
        for(size_t j = 0; j < rhv.column(); ++j)
        {
            if(std::string(lhv[i][j]) != std::string(rhv[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}
bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv)
{
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob)
{
    for(SpreadSheet::size_type j = 0; j < ob.column(); ++j)
            {
                out << "_________";
            }
            out << std::endl;
    for(SpreadSheet::size_type i = 0; i < ob.row(); ++i)
    {
        for(SpreadSheet::size_type j = 0; j < ob.column(); ++j)
        {
            out << std::setw(8) << std::left << ob[i][j] << '|';
        }out << std::endl;
        if(i != ob.row() - 1)
        {
            for(SpreadSheet::size_type j = 0; j < ob.column(); ++j)
            {
                out << "--------|";
            }
            out << std::endl;
        } else {
            for(SpreadSheet::size_type j = 0; j < ob.column(); ++j)
            {
                out << "________|";
            }
            out << std::endl;
        }
    }
    return out;
}
/****
std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob)
{
    for(SpreadSheet::size_type i = 0; i < ob.row(); ++i)
    {
        for(SpreadSheet::size_type j = 0; j < ob.column(); ++j)
        {
            out << ob[i][j] << ' ';
        }
        out << std::endl;
    }
    return out;
}
****/