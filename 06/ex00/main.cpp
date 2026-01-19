#include "ScalarConverter.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <sstream>
#include <iomanip>

void test(const std::string & input) {
	std::cout << "input: " << input << std::endl;
	ScalarConverter::convert(input);
	std::cout << "\n";
}

std::string intToString(int num) {
	std::stringstream ss;

	ss << num;
	return ss.str();
}

void myTests() {
	{
		std::cout << "==== Testing invalid input ====\n";
		test("");
		test(".f");
		test("invalid");
		test("123abc");
		test("3.ff");
		test("infff");
		test("nannn");
		test("++inff");
		test("--inf");
		test("nnan");	
	}
	{
		std::cout << "==== Testing valid char ====\n";
		test("a");
		test("?");
		test("42");
		test("126");
		test(",");
		std::cout << "==== Testing non displayble char ====\n";
		for (int i = 0; i <= 32; i++) {
			std::stringstream ss;
			test(intToString(i));
		}
		test("127");
	}
	{
		std::cout << "==== Testing float, double ====\n";
		std::stringstream dbl_max;
		std::stringstream flt_max;

		dbl_max << DBL_MAX;
		flt_max << FLT_MAX;

		test(dbl_max.str());
		test(flt_max.str());
		test("-999999999999999999999999999999999999999999999.9999");
		test("42.0");
		test("-42.0f");
		test("3.f");
		test("3.14");
		test("99999999999999999999999999999999999999999999999.9999");
		test("+inff");
		test("inff");
		test("-inff");
		test("-inf");
		test("nan");
		test("nanf");
	}
}

int main(int argc, char **argv) {
	if (argc == 2) {
		ScalarConverter::convert(argv[1]);
		return 0;
	}
	std::cerr << "Usage: ./ScaleConverter <literal>\n";
	return 1;
}
