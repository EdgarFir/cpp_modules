#include "Bureaucrat.hpp"

int main () {

	try {
		Bureaucrat a("Edgar", 0);
		std::cout << a;
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}

	try {
		Bureaucrat b("Edgar", 1);
		std::cout << b;
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}

	try {
		Bureaucrat c("Edgar2", 1);
		c.upGrade(1);
		std::cout << c;
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}

	try {
		Bureaucrat d("Edgar", 150);
		d.downGrade(1);
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}

	Bureaucrat valid("Valid Bureaucrat", 50);
	std::cout << valid;
	valid.upGrade(49);
	std::cout << valid;
	valid.downGrade(149);
	std::cout << valid;

	return 0;
}