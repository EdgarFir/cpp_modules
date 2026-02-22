#ifndef SCALARCONVERTER_HPP

# define SCALARCONVERTER_HPP

#include <iostream>

typedef enum literal_type_e {
        PSEUDO_LITERAL,
        CHAR,
        INT,
        FLOAT,
        DOUBLE
    } literal_type;

class ScalarConverter {
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter & src);
        ~ScalarConverter();
        ScalarConverter & operator=(const ScalarConverter & src);
    public:
        static void convert(const std::string & literal);
};

#endif