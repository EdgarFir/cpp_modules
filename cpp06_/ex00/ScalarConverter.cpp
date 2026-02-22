#include "ScalarConverter.hpp"
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

static bool isPseudoLiteral(const std::string & literal) {
    return ((literal == "+inf" || literal == "-inf" ||
			 literal == "+inff" || literal == "-inff" ||
			 literal == "nan" || literal == "nanf"));
}

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
		return true;
	
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

static bool isNan(double n) {
	return (n != n);
}

static bool isAscii(double c) {
	return (c >= 0 && c <= 127);
}

template <typename Type, typename MinBoundType, typename MaxBoundType>
static bool isOutOfBounds(Type n, MinBoundType minBound, MaxBoundType maxBound) {
	return (n < minBound || n > maxBound);
}

static void printChar(double literalConverted, int literalType) {
	char c;

	if (literalType == CHAR || isAscii(literalConverted)) {
		c = static_cast<unsigned char>(literalConverted);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'\n";
		else 
			std::cout << "char: Non displayble\n";
		return ; 
	}
	std::cout << "char: impossible\n";
}

static void printInt(double literalConverted, int literalType) {
	if (literalType != PSEUDO_LITERAL && 
		!isOutOfBounds<double, int, int>(literalConverted, INT_MIN, INT_MAX)) {
			std::cout << "int: " << static_cast<int>(literalConverted) << std::endl;
			return ;
	}
	std::cout << "int: impossible\n";
}

static bool hasDecimalValues(double d) {
	return ((d - static_cast<int>(d)) > 0);
}

template <typename Type>
static bool isPosInf(Type d) {
	return (d == std::numeric_limits<Type>::infinity());
}

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
	if (!isOutOfBounds(literalConverted, __FLT_MIN__, __FLT_MAX__)) {
		std::cout << "float: " << literalConverted 
							   << (!hasDecimalValues(literalConverted) ? ".0" : "")
							   << suffix
							   << std::endl;
		return ;
	}
	std::cout << "float: impossible\n";
}

static void printDouble(double literal_conversion, int literalType) {
	// TODO
	return ;
}

void ScalarConverter::convert(const std::string & literal) {
    double 	literalConversion;
	int		literalType;

	std::cout << "converting: " << literal << "\n";

	literalType = getLiteralType(literal);
	if (literalType == -1) {
		std::cerr << "Invalid literal. Impossible conversion.\n";
		return ;
	}
	literalConversion = std::stod(literal.c_str(), NULL);
	printChar(literalConversion, literalType);
	printInt(literalConversion, literalType);
	printFloat(literalConversion, literalType);
	printDouble(literalConversion, literalType);
}

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
}
