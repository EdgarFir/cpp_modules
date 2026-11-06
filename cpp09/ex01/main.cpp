#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: Usage: ./ex00 <expression>\n";
        return 1;
    }

    RPN rpn;

    int res = 0;
    if (rpn.CalculateExpression(argv[1], res))
    {
        std::cout << "Value: " << res << std::endl;
        return 0;
    }

    return 1;
}
