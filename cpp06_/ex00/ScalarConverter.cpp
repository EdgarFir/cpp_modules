#include "ScalarConverter.hpp"
#include <cstdlib>
#include <limits.h>
#include <limits>
#include <cmath>

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
		return 0;
	
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
				return 0;
			hasPoint = true;
		}
		else if (!std::isdigit(literal[i]))
			return 0;
	}

	if (hasF && hasPoint)
		return FLOAT;
	
	if (hasPoint)
		return DOUBLE;
	
	if (!hasPoint && !hasF)
		return INT;
	
	return 0;
}

static bool isNan(double n) {
	return (n != n);
}

static void printChar(double literal_conversion, int literalType) {
	// TODO
}

static void printInt(double literal_conversion, int literalType) {
	// TODO
}

static void printFloat(double literal_conversion, int literalType) {
	// TODO
}

static void printDouble(double literal_conversion, int literalType) {
	// TODO
}

void ScalarConverter::convert(const std::string & literal) {
    double 	literalConversion;
	int		literalType;

	literalType = getLiteralType(literal);
	if (!literalType) {
		std::cerr << "Invalid literal. Impossible conversion.\n";
		return ;
	}
	literalConversion = std::stod(literal.c_str(), NULL);
	printChar(literalConversion, literalType);
	printInt(literalConversion, literalType);
	printFloat(literalConversion, literalType);
	printDouble(literalConversion, literalType);
}
