#include <iostream>
#include "iter.hpp"

template <typename Value>
void SetToZero(Value& value)
{
    value = 0;
}


template <typename Value>
void PrintValue(const Value& value)
{
    std::cout << "Printing value: ";
    std::cout << "|" << value << "|" << std::endl;
}

int main()
{
    {
        std::string char_arr = "School_42";

        ::iter(char_arr.data(), char_arr.size(), PrintValue<const char>);
        ::iter(char_arr.data(), char_arr.size(), SetToZero<char>);
        ::iter(char_arr.data(), char_arr.size(), PrintValue<const char>);
    }
    std::cout << "=====================================================================\n";
    {
        const std::string char_arr = "School_42";

        ::iter(char_arr.data(), char_arr.size(), PrintValue<const char>);
    }
    std::cout << "=====================================================================\n";
    {
        int int_arr[] = {1, 2, 3, 4, 5};

        ::iter(int_arr, 5, PrintValue<const int>);
        ::iter(int_arr, 5, SetToZero<int>);
        ::iter(int_arr, 5, PrintValue<const int>);
    }
    std::cout << "=====================================================================\n";  
    {
        const int int_arr[] = {1, 2, 3, 4, 5};

        ::iter(int_arr, 5, PrintValue<const int>);
    }

    return 0;
}