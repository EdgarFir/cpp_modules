#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat() : _grade(0) {}

Bureaucrat::Bureaucrat(const std::string & name, int grade) : _name(name), _grade(grade) {
	if (_grade < GRADE_MAX)
		throw GradeTooHighException("Error: Bureaucrat grade too high, max: 1\n");
	if (_grade > GRADE_MIN)
		throw GradeTooLowException("Error: Bureaucrat grade too low, min: 150\n");
}

Bureaucrat::Bureaucrat(const Bureaucrat & src) : _name(src._name), _grade(src._grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat & src) {
	if (this != &src) {
		_grade = src._grade;
	}
	return *this;
}

std::string Bureaucrat::getName() const {
	return _name;
}

int			Bureaucrat::getGrade() const {
	return _grade;
}

void		Bureaucrat::upGrade(int val) {
	if (_grade - val < GRADE_MAX)
		throw GradeTooHighException("Error: grade too high, max: 1\n");
	_grade -= val;
}

void		Bureaucrat::downGrade(int val) {
	if (_grade + val > GRADE_MIN)
		throw GradeTooLowException("Error: grade too low, min: 150\n");
	_grade += val;
}

void		Bureaucrat::signForm(Form & f) {
	try {
		f.beSigned(*this);
		std::cout << _name << " signed " << f.getName() << std::endl;
	}
	catch (std::exception & e) {
		std::cout << _name 
				  << " couldn't sign "
				  << f.getName()
				  << " because "
				  << e.what();
	}
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj) {
	os << obj.getName() << ", " << "grade " << obj.getGrade() << std::endl;

	return os;
}

Bureaucrat::GradeTooHighException::GradeTooHighException(const std::string &msg) throw() {
	_msg = msg;
}

const char * Bureaucrat::GradeTooHighException::what() const throw() {
	return _msg.c_str();
}

Bureaucrat::GradeTooHighException::~GradeTooHighException() throw() {}


Bureaucrat::GradeTooLowException::GradeTooLowException(const std::string &msg) throw() {
	_msg = msg;
}

const char * Bureaucrat::GradeTooLowException::what() const throw() {
	return _msg.c_str();
}

Bureaucrat::GradeTooLowException::~GradeTooLowException() throw() {}