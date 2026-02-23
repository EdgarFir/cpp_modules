#include "../includes/ScalarConverter.hpp"
#include <sstream>
#include <limits>
#include <iomanip>

void testScalarConverter(const std::string & literal) {
	std::cout << "==== Testing " << literal << " ====\n";
	ScalarConverter::convert(literal);
	std::cout << "\n";
}

int main() {
	testScalarConverter("42");
	testScalarConverter("nan");
	testScalarConverter("+inf");
	testScalarConverter("-inf");
	testScalarConverter("+inff");
	testScalarConverter("-inff");
	testScalarConverter("nanf");
	testScalarConverter("nann");
	testScalarConverter("nanff");
	testScalarConverter("+infff");
	testScalarConverter("++inff");
	testScalarConverter("42.01");
	testScalarConverter("-42");
	testScalarConverter("-0");

	// Testing limits
	std::ostringstream i_max;
	std::ostringstream i_min;
	std::ostringstream f_max;
	std::ostringstream f_min;
	
	i_max << std::numeric_limits<int>::max();
	i_min << -std::numeric_limits<int>::min();
	f_max << std::fixed << std::numeric_limits<float>::max();
	f_min << std::fixed << -std::numeric_limits<float>::max();

	testScalarConverter(i_max.str());
	testScalarConverter(i_min.str());
	testScalarConverter(f_max.str());
	testScalarConverter(f_min.str());

}