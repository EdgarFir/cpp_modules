#include "../includes/ScalarConverter.hpp"

int main() {
	ScalarConverter::convert("42");
	std::cout << "\n";
	ScalarConverter::convert("nan");
	std::cout << "\n";
	ScalarConverter::convert("+inf");
	std::cout << "\n";
	ScalarConverter::convert("-inf");
	std::cout << "\n";
	ScalarConverter::convert("+inff");
	std::cout << "\n";
	ScalarConverter::convert("-inff");
	std::cout << "\n";
	ScalarConverter::convert("nanf");
	std::cout << "\n";
	ScalarConverter::convert("nann");
	std::cout << "\n";
	ScalarConverter::convert("nanff");
	std::cout << "\n";
	ScalarConverter::convert("+infff");
	std::cout << "\n";
	ScalarConverter::convert("++inff");
	std::cout << "\n";
	ScalarConverter::convert("42.01");
	std::cout << "\n";
	ScalarConverter::convert("-42");
	std::cout << "\n";
	ScalarConverter::convert("-0");
}