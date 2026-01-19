#include "ScalarConverter.hpp"
#include <stdlib.h>
#include <limits.h>
#include <iomanip>
#include <cctype>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter & src) { static_cast<void>(src); }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter & src) {
	static_cast<void>(src);
	return *this;
}

ScalarConverter::~ScalarConverter() {}

/**
 * @brief Print impossible scalar type message.
 */
static void printImpossible() {
	std::cout << "char: impossible\n"
			  << "int: impossible\n"
			  << "float: impossible\n"
			  << "double: impossible\n";
}

/**
 * @brief Validate if d is NaN. According to standard IEEE-754, NaN is not equal to NaN.
 * 
 * @return True if d is NaN, else False.
 */
static int isNan(double d) {
	return d != d;
}

/**
 * @brief Ensure d is not NaN, and is a valid char following ASCII table decimal values. In that case is impossible to scale. 
 * If d is valid to scale print char scalar type if is printable, else prints "Non displayble".
 * 
 * @param d Number to scale and print.
*/
static void printChar(double d) {
	if (isNan(d) || d < 0 || d > 127) {
		std::cout << "char: impossible\n";
		return ;
	}
	char c = static_cast<char>(d);
	if (!std::isprint(c))
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: " << "'" << c << "'" << std::endl;
}

/**
 * @brief Ensure d is not NaN, overflow or underflow int type or it's impossible to scale to int. 
 * In that case print impossible
 * If d is valid to scale, print int scalar type.
 * 
 * @param d Number to scale and print.
*/
static void printInt(double d) {
	if (isNan(d) || d > INT_MAX || d < INT_MIN)
		std::cout << "int: impossible\n";
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
}

/**
 * @brief Print float scalar type with 1 decimal.
 * 
 * @param d Number scale and print. 
*/
static void printFloat(double d) {
	std::cout << "float: "
			  << std::fixed << std::setprecision(1)
			  << static_cast<float>(d) << "f\n";
}

/**
 * @brief Print double scalar type with 1 decimal.
 * 
 * @param d Number scale and print. 
*/
static void printDouble(double d) {
	std::cout << "double: " 
			  << std::fixed << std::setprecision(1)
			  << d << std::endl;
}

/**
 * @brief Check if str is a char literal.
 * 
 * @param str String to check.
 * 
 * @return True if str is a char literal, else False.
*/
static bool isChar(const std::string & str) {
	return (str.size() == 1 && !std::isdigit(static_cast<unsigned char>(str[0])));
}

void ScalarConverter::convert(const std::string & str) {
	double 	d;
	char * 	end_ptr;
	size_t	str_size;

	str_size = str.size();
	if (str_size != 0) {
		if (isChar(str)) {
			d = static_cast<double>(str[0]);
		}
		else {
			d = std::strtod(str.c_str(), &end_ptr);
			if (!(*end_ptr == '\0' || (end_ptr == &str[str_size - 1] && *end_ptr == 'f'))) {
				printImpossible();
				return ;
			}
		}
		printChar(d);
		printInt(d);
		printFloat(d);
		printDouble(d);
		return ;
	}
	printImpossible();
}