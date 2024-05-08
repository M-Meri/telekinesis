#include <iostream>
#include <string>
#include <initializer_list>
#include "../SpreadSheetHdrs/spread_sheet.h"

int main()
{
    SpreadSheet s1 = SpreadSheet(1, 3, 4); // : ok
    std::cout << s1; // 4 4 4 : ok
    s1.at(0, 2) = 5.4;
    std::cout << s1; // 4 4 5.4 : ok
    s1.at(0, 0) = std::string("kiwi");
    std::cout << s1; // kiwi 4 5.4 : ok
    s1.add_row(0, 3);
    std::cout << s1; // 3 3 3
                     // kiwi 4 5.4 :OK
    SpreadSheet s2 = s1;
    std::cout << s2 ; // :OK

    s2.add_col(2, 4.67);
    std::cout << s2; // :OK

    s1.resize_row(5);
    std::cout << s1.row() << std::endl;// :ok
    s1.resize_col(2);
    std::cout << s1; // :OK
    s1.resize_col(4);
    std::cout << s1.column() << std::endl << s1;// :ok

    s1.resize(2, 2);
    std::cout << s1;//:ok

    SpreadSheet s3 = s1.slice(1, 1);
    std::cout << s3; // :ok

    s1.delete_col(0);
    std::cout << s1;// :ok

    s2.delete_row(0);
    std::cout << s2; // :ok

    std::initializer_list<Cell> init = {Cell(8), Cell(std::string("hello")),Cell(3.14), Cell('c'), Cell(bool(1))}; 
    SpreadSheet sp = SpreadSheet(4, init);
    std::cout << sp; // :ok
    std::cout << sp[1][3] << std::endl; // c :ok
    sp[0][3] = std::string("Adele");
    SpreadSheet sp1 = sp.slice({0, 2}, {1, 3, 4});
    std::cout << sp1; // :ok
}