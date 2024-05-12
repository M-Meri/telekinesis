#include <iostream>
#include <string>
#include <initializer_list>
#include "spread_sheet.h"

int main()
{
    SpreadSheet s1 = SpreadSheet(1, 3, 4); // : ok
    std::cout << s1; // 4 4 4 : ok
    s1[0][2] = 5.4;
    std::cout << s1; // 4 4 5.4 : ok
    s1[0][0] = std::string("kiwi");
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

    s1.delete_col(0);
    std::cout << s1;// :ok

    s2.delete_row(0);
    std::cout << s2; // :ok

    std::initializer_list<Cell> init = {Cell(8), Cell(std::string("hello")),Cell(3.14), Cell('c'), Cell(true)}; 
    SpreadSheet sp = SpreadSheet(4, init);
    std::cout << sp; // :ok
    std::cout << sp[1][3] << std::endl; // c :ok
    sp[0][3] = std::string("Adele");
    SpreadSheet sp1 = sp.slice({0, 2}, {1, 3, 4});
    std::cout << sp1; // :ok

    std::cout << "SOME TESTS FOR CELL\n";

    std::vector<int> vec = {1, 78, 45, 67, 90};
    Cell cell = vec;
    
    std::cout << cell << std::endl; // :Ok

    vec.push_back(100);
    std::cout << vec << std::endl; // :OK
    vec = static_cast<std::vector<int>>(cell);
    std::cout << vec << std::endl;
    const Cell cell2 = vec;
    std::cout << (cell2 == cell) << (cell != cell2) << std::endl;// 10 : OK


    std::cout << std::endl << "MIRRORS" << std::endl << std::endl;
    SpreadSheet test = {3,4};
    int c = 1;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            test[i][j] = c++;
        }
    }
    std::cout << test;
    SpreadSheet tmp = test;
    tmp.mirrorH();
    std::cout << tmp;
    tmp = test;
    tmp.rotate(1);
    std::cout << tmp;
    tmp = test;
    tmp.rotate(2);
    std::cout << tmp;
    tmp = test;
    tmp.rotate(3);
    std::cout << tmp;
    tmp = test;
    tmp.mirrorD();
    std::cout << tmp;
    tmp = test;
    tmp.mirrorV();
    std::cout << tmp;
    tmp = test;
    tmp.mirrorSD();
    std::cout << tmp;
}