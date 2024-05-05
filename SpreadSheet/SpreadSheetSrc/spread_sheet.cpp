#include <iostream>
#include <string>
#include <initializer_list>
#include "../SpreadSheetHdrs/spread_sheet.h"

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

SpreadSheet::SpreadSheet(size_type row, std::initializer_list<const Cell>& init)
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

void SpreadSheet::clear()
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
        x = rhv.x;
        for(size_type i = 0; i < x; ++i)
        {
            tmp[i] = new Cell[rhv.y];
            for(size_type j = 0; j < rhv.y; ++j)
            {
                tmp[i][j] = rhv.cells[i][j];
            }
        }
        y = rhv.y;
        clear();
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

Cell& SpreadSheet::at(size_type row, size_type col)
{
    return cells[row][col];
}

const Cell& SpreadSheet::at(size_type row, size_type col) const
{
    return cells[row][col];
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

void SpreadSheet::add_colum(size_type index, const Cell& val)
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

void SpreadSheet::resize_row(size_type add)
{
    if(add < x)
    {
        for(size_type i = add; i < x; ++i)
        {
            delete[] cells[i];
        }
        x = add;
        return;
    }
    if(add == x)
    {
        return;
    }
    Cell** tmp = new Cell*[add];
    for (size_type i = 0; i < add; ++i)
    {
        tmp[i] = new Cell[y];
        if(i < x)
        {
            for(size_type j = 0; j < y; ++j)
            {
                tmp[i][j] = cells[i][j];
            }
        }
    }
    size_type tmpy = y;
    clear();
    x = add;
    y = tmpy;
    cells = tmp;
    tmp = nullptr;
}

void SpreadSheet::resize_colum(size_type add)
{
    if(add <= y)
    {
        y = add;
        return;
    }
    Cell** tmp = new Cell*[x];
    for (size_type i = 0; i < x; ++i)
    {
        tmp[i] = new Cell[add];
        for(size_type j = 0; j < y; ++j)
        {
            tmp[i][j] = cells[i][j];
        }
    }
    size_type tmpx = x;
    clear();
    y = add;
    x = tmpx;
    cells = tmp;
    tmp = nullptr;
}

void SpreadSheet::resize(size_type row, size_type col)
{
    resize_row(row);
    resize_colum(col);
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

void SpreadSheet::delete_colum(size_type col)
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

SpreadSheet SpreadSheet::slice(size_type from, size_type count)
{
    if(from + count > x)
    {
        throw;
    }
    SpreadSheet tmp = SpreadSheet(count, y);
    for(size_type i = 0; i < count; ++i)
    {
        for(size_type j = 0; j < y; j++)
        {
            tmp.at(i, j) = cells[from + i][j];
        }
    }
    return tmp;
}

SpreadSheet::size_type SpreadSheet::row() const
{
    return x;
}

SpreadSheet::size_type SpreadSheet::colum() const
{
    return y;
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob)
{
    for(SpreadSheet::size_type i = 0; i < ob.row(); ++i)
    {
        for(SpreadSheet::size_type j = 0; j < ob.colum(); ++j)
        {
            out << ob.at(i, j) << ' ';
        }
        out << std::endl;
    }
    return out;
}