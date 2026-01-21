#include <string>
#include <iostream>

/**
 * @brief The goal of this program is distiguish pointers from references.
 * We create an static string, then a pointer and an reference to that string and we can see the differences through their memories address.
 */
int main()
{
    std::string s = "HI THIS IS BRAIN";

    std::string *stringPTR = &s;

    std::string &stringREF = s;

    std::cout << &s << std::endl;
    std::cout << &stringPTR << std::endl;
    std::cout << &stringREF << std::endl;

    std::cout << s << std::endl;
    std::cout << *stringPTR << std::endl;
    std::cout << stringREF << std::endl;
}
