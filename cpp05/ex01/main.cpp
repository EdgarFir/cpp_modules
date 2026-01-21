#include "Bureaucrat.hpp"
#include "Form.hpp"

int main () {
	
	std::cout << "======= Testing form initialize validations ======\n";
	try {
		Form f("Form 1", 0, 1);
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}
	try {
		Form f("Form 1", 151, 1);
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}
	try {
		Form f("Form 1", 1, 0);
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}
	try {
		Form f("Form 1", 1, 151);
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}
	std::cout << std::endl;

	std::cout << "======= Testing form sign validations ======\n";
	
	Form f("Form 1", 1, 1);
	std::cout << f;

	Bureaucrat b("Bureaucrat 1", 10);
	std::cout << b;

	b.signForm(f);

	// try {
	// 	b.signForm(f);
	// }
	// catch (std::exception &e) {
	// 	std::cout << e.what();
	// }

	b.upGrade(9);
	std::cout << b;
	b.signForm(f);
	b.signForm(f);
	return 0;
}