#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main () {
	
	std::cout << "======= Bureaucrats =======\n";
	Bureaucrat low("LOW", 150);
	Bureaucrat medium("MEDIUM", 150);
	Bureaucrat high("HIGH", 1);
	medium = low;
	medium.upGrade(75);

	std::cout << low;
	std::cout << medium;
	std::cout << high;

	std::cout << std::endl;

	Intern intern;

	std::cout << "====== TESTING INTERNS ======\n";
	{
		std::cout << "======= Testing Shrubbery Form validations ======\n";

		AForm *s;
		
		try {
			s = intern.makeForm("shrubbery creation", "TARGET");
		}
		catch (std::exception & e) {
			std::cout << e.what();
		}
		std::cout << "Shrubbery form created: " << *s << std::endl;
	
		low.executeForm(*s);
		low.signForm(*s);
		medium.signForm(*s);
		low.executeForm(*s);
		medium.executeForm(*s);
		std::cout << "Shrubbery form after executed: " << *s << std::endl;
		delete s;
	}	
	{
		std::cout << "======= Testing Robotomy Form validations ======\n";
		
		AForm *r; 

		try {
			r = intern.makeForm("robotomy request", "TARGET");
			std::cout << "Robotomy form created: " << *r << std::endl;
		}
		catch (std::exception & e) {
			std::cout << e.what();
		}
	
		low.executeForm(*r);
		low.signForm(*r);
		medium.signForm(*r);
		high.signForm(*r);
		low.executeForm(*r);
		medium.executeForm(*r);
		high.executeForm(*r);
	
		std::cout << std::endl;
		std::cout << r->getName() << ", Robotomy form after executed: " << *r << std::endl;
		delete r;
	}
	{
		std::cout << "======= Testing Presidential Form validations ======\n";
		AForm *p = intern.makeForm("presidential pardon", "TARGET");
		std::cout << "Presidential form created: " << *p << std::endl;
	
		low.executeForm(*p);
		low.signForm(*p);
		medium.signForm(*p);
		high.signForm(*p);
		low.executeForm(*p);
		medium.executeForm(*p);
		high.executeForm(*p);
	
		std::cout << std::endl;
		std::cout << p->getName() << ", Presidential form after executed: " << *p << std::endl;
		delete p;
	}

	try {
		AForm *invalid = intern.makeForm("invalid", "TARGET");
		std::cout << invalid << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}

	return 0;	
}