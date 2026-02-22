#include "ScalarConverter.hpp"
#include <cstdlib>
#include <limits>

int main() {
    // ScalarConverter::convert("42.");
    // ScalarConverter::convert("42.0ff");
    // ScalarConverter::convert("-nan");
    // ScalarConverter::convert("0.0f");
    // ScalarConverter::convert("-inf");

    std::string a = "inf";

    double d = std::strtod(a.c_str(), NULL);

    std::cout << (d == -std::numeric_limits<double>::infinity()) << std::endl;

    std::cout << (d > 0) << "\n";

    if (d >= 0 && d <= 127)
        std::cout << "HEREEE\n";
    else
        std::cout << "NOT HERE\n";

    std::cout << (static_cast<float>(d) > __FLT_MAX__);
}