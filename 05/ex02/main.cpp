#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main () {
	
	std::cout << "======= Bureaucrats =======";
	Bureaucrat low("LOW", 150);
	Bureaucrat medium("MEDIUM", 150);
	Bureaucrat high("HIGH", 1);
	medium = low;
	medium.upGrade(75);

	std::cout << low;
	std::cout << medium;
	std::cout << high;

	std::cout << std::endl;

	{
		std::cout << "======= Testing Shrubbery Form validations ======\n";
		AForm *s = new ShrubberyCreationForm("TARGET");
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
		AForm *r = new RobotomyRequestForm("TARGET");
		std::cout << "Robotomy form created: " << *r << std::endl;
	
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
		AForm *p = new PresidentialPardonForm("TARGET");
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

	return 0;	
}