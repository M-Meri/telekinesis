#include <iostream>
#include "../StringHeaders/myString.h"

int main()
{
    MyString<> str1;
    std::cout << str1.empty() << std::endl;// 1

    MyString<> str2{2};
    std::cout << str2.length() << std::endl; //2

    str1.append('h');
    std::cout << str1 << std::endl; // h
    str1.append("ello");
    std::cout << str1 << std::endl;//hello

    str2[0] = '_';
    std::cout << str2 << std::endl; // _
    str2.at(1) = 'w';
    std::cout << str2 << std::endl; // _w

    str1.append(str2);
    std::cout << str1 << std::endl; // hello_w
    std::cout << str2 << std::endl; // _w

    str1.replace("ll", "11");
    std::cout << str1 << std::endl; // he11o_w

    str2.insert(0, "he11o");
    std::cout << str2 << std::endl; // he11o_w

    std::cout << (str1 == str2 ) << std::endl; // 1

    str1 += 'o';
    std::cout << str1 << std::endl;// he11o_wo

    str1.reverse();
    std::cout << str1 << std::endl; // ow_o11eh

    str1.replaceAll("o", "123");
    std::cout << str1 << std::endl; // 123w_12311eh

    MyString str3 = str2;
    str3 *= 3;
    std::cout << str3 << std::endl; // he11o_whe11o_whe11o_w

    str2 += str1;
    std::cout << str2 << std::endl; // he11o_w123w_12311eh

    std::cout << str1.rfind('3') << "     " << str1.rfind("12") << std::endl;// 7 5
}