#ifndef SCALARCONVERTER_HPP

# define SCALARCONVERTER_HPP

#include <iostream>

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter & src);
		ScalarConverter &operator=(const ScalarConverter & src);
	public:
		~ScalarConverter();
		static void convert(const std::string & str);
};

#endif