#include "../includes/ScalarConverter.hpp"
#include <cstdlib>
#include <limits.h>
#include <limits>
#include <cmath>
#include <cctype>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter & src) { static_cast<void>(src); }
ScalarConverter::~ScalarConverter() {}
ScalarConverter & ScalarConverter::operator=(const ScalarConverter & src) {
    static_cast<void>(src);
    return *this;
}

/**
 * @brief isPseudoLiteral is a static (internal) helper function that checks 
 * if a given string literal is a pseudo-literal representing special floating-point 
 * values such as positive infinity, negative infinity, or NaN (Not a Number). 
 * It returns true if the literal matches any of the 
 * recognized pseudo-literals ("+inf", "-inf", "+inff", "-inff", "nan", "nanf"),
 * and false otherwise.
 * 
 * @param literal the input string literal to check for being a pseudo-literal 
 * representing special floating-point values 
 * @return true if the literal is a recognized pseudo-literal representing special 
 * floating-point values,
 * @return false if the literal does not match any of the recognized pseudo-literals, 
 * indicating it is not a pseudo-literal.
 */
static bool isPseudoLiteral(const std::string & literal) {
    return ((literal == "+inf" || literal == "-inf" ||
			 literal == "+inff" || literal == "-inff" ||
			 literal == "nan" || literal == "nanf"));
}

/**
 * @brief getLiteralType object is a static (internal) 
 * helper function that determines the type of a given string literal.
 * 
 * @param literal the input string literal to analyze and classify 
 * as CHAR, INT, FLOAT, DOUBLE, PSEUDO_LITERAL, or invalid (-1)
 * @return int representing the type of the literal:
 */
static int getLiteralType(const std::string & literal) {
    bool	hasPoint;
	bool	hasF;
	size_t	limit;
	
	if (literal.empty())
		return -1;
	
	// Check if is pseudo literal
	if (isPseudoLiteral(literal))
		return PSEUDO_LITERAL;

	// Check if is char
	if (literal.size() == 1 && !std::isdigit(literal[0]))
		return CHAR;
	
	hasPoint = false;
	hasF = (literal[literal.size() - 1] == 'f');
	limit = literal.size() - (hasF ? 1 : 0);
	for (size_t i = 0; i < limit; ++i) {
		if (i == 0 && (literal[i] == '+' || literal[i] == '-'))
			continue;
		if (literal[i] == '.') {
			if (i == 0 || i == limit - 1 || hasPoint)
				return -1;
			hasPoint = true;
		}
		else if (!std::isdigit(literal[i]))
			return -1;
	}

	if (hasF && hasPoint)
		return FLOAT;
	
	if (hasPoint)
		return DOUBLE;
	
	if (!hasPoint && !hasF)
		return INT;
	
	return -1;
}

/**
 * @brief isNan is a static (internal) helper function that 
 * checks if a given double value n is NaN (Not a Number).
 * 
 * @param n the double value to check for being NaN (Not a Number)
 * @return true if n is NaN (Not a Number), which is determined by the property that NaN 
 * is not equal to itself,
 * @return false if n is a valid number (not NaN), which means it is equal to itself. 
 */
static bool isNan(double n) {
	return (n != n);
}

/**
 * @brief isAscii is a static (internal) helper function that checks
 *  if a given double value c can be represented as an ASCII character.
 * 
 * @param c the double value to check for being within the ASCII character range (0 to 127 inclusive) 
 * @return true if c is within the ASCII character range (0 to 127 inclusive), 
 * indicating it can be represented as an ASCII character,
 * @return false if c is outside the ASCII character range, indicating 
 * it cannot be represented as an ASCII character.
 */
static bool isAscii(double c) {
	return (c >= 0 && c <= 127);
}

/**
 * @brief hasDecimalValues is a static (internal) 
 * helper function that checks if a given double value d has any fractional part.
 * 
 * @param d the double value to check for having decimal (fractional) values
 * @return true if d has a fractional part (i.e., the floor of d is not equal to d itself),
 * @return false if d is an integer value (i.e., the floor of d is equal to d), 
 * indicating no decimal values.
 */
static bool hasDecimalValues(double d) {
	return (std::floor(d) != d);
}

/**
 * @brief isPosInf is a static (internal) helper function that checks if a 
 * given value d of any type Type is positive infinity.
 * 
 * @tparam Type	the type of the value to check for positive infinity (e.g., float, double)
 * @param d the value to check for being positive infinity
 * @return true if d is positive infinity according to std::numeric_limits<Type>::infinity(),
 * @return false otherwise
 */
template <typename Type>
static bool isPosInf(Type d) {
	return (d == std::numeric_limits<Type>::infinity());
}

/**
 * @brief isInsideIntLimits is a static (internal) helper function that checks if
 *  a given double value n is within the representable range of an int. 
 * It returns true if n is greater than or equal to std::numeric_limits<int>::min()
 *  and less than or equal to std::numeric_limits<int>::max(), indicating that 
 * it can be safely converted to an int without overflow. Otherwise, 
 * it returns false, indicating that the value is outside the limits of what an int can represent.
 * 
 * @param n the double value to check against int limits
 * @return true 
 * @return false 
 */
static bool isInsideIntLimits(double n) {
	return !(n < std::numeric_limits<int>::min() || n > std::numeric_limits<int>::max());
}

/**
 * @brief isInsideFloatLimits is a static (internal) helper function that checks 
 * if a given double value n is within the representable range of a float. 
 * It returns true if n is greater than or equal to -std::numeric_limits<float>::max() 
 * and less than or equal to std::numeric_limits<float>::max(), 
 * indicating that it can be safely converted to a float without overflow. 
 * Otherwise, it returns false, indicating that the value is outside the limits of what 
 * a float can represent.
 * 
 * @param n the double value to check against float limits 
 * @return true 
 * @return false 
 */
static bool isInsideFloatLimits(double n) {
	return !(n < -std::numeric_limits<float>::max() || n > std::numeric_limits<float>::max());
}

/**
 * @brief printChar is a static (internal) helper function 
 * that attempts to print the character 
 * representation of a given double literalConverted.
 * 
 * @param literalConverted the double value to convert 
 * and print as a character
 * @param literalType the type of the original literal 
 * (used to determine if it's a pseudo-literal, which cannot be converted to char)
 */
static void printChar(double literalConverted, int literalType) {
	char c;

	if (literalType != PSEUDO_LITERAL 
		&& !isNan(literalConverted) && isAscii(literalConverted)) 
	{
		c = static_cast<unsigned char>(literalConverted);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'\n";
		else 
			std::cout << "char: Non displayable\n";
		return ;
	}
	std::cout << "char: impossible\n";
}


/**
 * @brief printInt is a static (internal) helper function 
 * that attempts to print the integer 
 * representation of a given double literalConverted.
 * 
 * @param literalConverted the double value to convert and print as an integer 
 * @param literalType the type of the original literal (used to determine if it's a 
 * pseudo-literal, which cannot be converted to int)
 */
static void printInt(double literalConverted, int literalType) {
	if (literalType != PSEUDO_LITERAL &&
		!isNan(literalConverted) &&
		isInsideIntLimits(literalConverted)
	) {
			std::cout << "int: " << static_cast<int>(literalConverted) << std::endl;
			return ;
	}
	std::cout << "int: impossible\n";
}


/**
 * @brief printFloat is a static (internal) helper that writes a C-style float
 * representation to std::cout for a given double literalConverted and an int literalType.
 * It handles pseudo-literals (printing a possible '+' for +inf), clamps zero to 0 to avoid signed zero,
 * casts and prints the value with an 'f' suffix (appending ".0" when there are no fractional digits) 
 * if within float limits, and prints "float: impossible" when conversion is out of range.
 * 
 * @param literalConverted the double value to convert and print as a float 
 * @param literalType the type of the original literal (used to determine if it's a pseudo-literal)
 */
static void printFloat(double literalConverted, int literalType) {
	char suffix = 'f';

	if (literalType == PSEUDO_LITERAL) {
		std::cout << "float: "
				  << (isPosInf<float>(literalConverted) ? "+" : "" )
				  << literalConverted 
				  << suffix 
				  << std::endl;
		return ;
	}

	if (isInsideFloatLimits(literalConverted)) {
		if (literalConverted == 0.0)
			literalConverted = 0;

		std::cout << "float: " << static_cast<float>(literalConverted) 
							   << (!hasDecimalValues(literalConverted) ? ".0" : "")
							   << suffix
							   << std::endl;
		return ;
	}

	std::cout << "float: impossible\n";
}

/**
 * @brief  prints a "double: " representation of the value to std::cout. 
 * It treats pseudo-literals (when literalType == PSEUDO_LITERAL) specially 
 * by prefixing a "+" for positive infinity via isPosInf, 
 * normalises 0.0 to 0 (removing negative zero), 
 * and appends ".0" when hasDecimalValues indicates no fractional part, 
 * ending output with std::endl.
 * 
 * @param literalConverted the double value to print as a double representation
 * @param literalType the type of the original literal, used to determine if it's a pseudo-literal for special formatting
 */
static void printDouble(double literalConverted, int literalType) {
	if (literalType == PSEUDO_LITERAL) {
		std::cout << "double: " 
				  << (isPosInf<double>(literalConverted) ? "+" : "" )
				  << literalConverted 
				  << std::endl;
		return ;
	}

	if (literalConverted == 0.0)
			literalConverted = 0;
	
	std::cout << "double: " << literalConverted
							<< (!hasDecimalValues(literalConverted) ? ".0" : "")
							<< std::endl;
}

/**
 * @brief convert is the main static method of ScalarConverter that takes a string literal, 
 * determines its type, converts it to a double, and prints its char, int, float, and double 
 * representations. It first checks the literal type using getLiteralType, handles invalid 
 * literals by printing an error message, converts chars directly to their ASCII integer values, 
 * and uses std::strtod for numeric conversions. It then calls printChar, printInt, printFloat, and 
 * printDouble to output the respective representations based on the converted value and its original type.
 * 
 * @param literal the input string literal to convert and print in various scalar forms
 */
void ScalarConverter::convert(const std::string & literal) {
    double 	literalConversion;
	int		literalType;

	literalType = getLiteralType(literal);
	if (literalType == -1) {
		std::cerr << "Invalid literal. Impossible conversion.\n";
		return ;
	}

	if (literalType == CHAR)
		literalConversion = static_cast<int>(literal[0]);
	else
		literalConversion = std::strtod(literal.c_str(), NULL);

	printChar(literalConversion, literalType);
	printInt(literalConversion, literalType);
	printFloat(literalConversion, literalType);
	printDouble(literalConversion, literalType);
}

