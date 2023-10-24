#include <iostream>
#include <stdexcept>
#include <string>

#include "big_integer.h"

int main()
{
    try
    {
        big_integer i1("114575");
        i1.print();
        std::cout << " + ";
        
        big_integer i2("78524");
        i2.print();
        std::cout << " = ";
        
        big_integer i3 = i1 + i2;
        i3.print();
        std::cout << std::endl;
        
        big_integer i4("569841");
        int multiplier = 317;
        i4.print();
        std::cout << " * " << multiplier << " = ";
        big_integer i5 = i4 * multiplier;
        i5.print();
        std::cout << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    
    return 0;
}
