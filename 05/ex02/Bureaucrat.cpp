#include "Bureaucrat.hpp"
#include "AForm.hpp"

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

/**
 * @brief Gets name
 * 
 * @return name
 */
std::string Bureaucrat::getName() const {
	return _name;
}

/**
 * @brief Gets grade.
 * 
 * @return grade.
 */
int			Bureaucrat::getGrade() const {
	return _grade;
}

/**
 * @brief Try to down Bureucrat grade. If grade + val higher than GRADE_MIN throw GradeTooLowException.
 * 
 * @param val Value to down.
 */
void		Bureaucrat::upGrade(int val) {
	if (_grade - val < GRADE_MAX)
		throw GradeTooHighException("Error: grade too high, max: 1\n");
	_grade -= val;
}

/**
 * @brief Try to down Bureucrat grade. If grade + val higher than GRADE_MIN throw GradeTooLowException.
 * 
 * @param val Value to down.
*/
void		Bureaucrat::downGrade(int val) {
	if (_grade + val > GRADE_MIN)
		throw GradeTooLowException("Error: grade too low, min: 150\n");
	_grade += val;
}

/**
 * @brief Try to sign a Form. If an Exception is catched during the signing print an explicit error.
 * 
 * @param form Form to sign.
*/
void		Bureaucrat::signForm(AForm & form) {
	try {
		form.beSigned(*this);
		std::cout << _name << " signed " << form.getName() << std::endl;
	}
	catch (std::exception & e) {
		std::cout << _name 
				  << " couldn't sign "
				  << form.getName()
				  << " because "
				  << e.what();
	}
}

/**
 * @brief Try to execute a Form. If an Exception is catched during the execution print an explicit error.
 * 
 * @param form Form to execute.
*/
void 		Bureaucrat::executeForm(AForm const & form) const {
	try {
		form.execute(*this);
		std::cout << _name << " executed " << form.getName() << std::endl;
	}
	catch (std::exception & e) {
		std::cout << _name << " couldn't execute " << form.getName() << " because " << e.what();
	}
}


std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj) {
	os << obj.getName() << ", " << "grade " << obj.getGrade() << std::endl;

	return os;
}

Bureaucrat::GradeTooHighException::GradeTooHighException(const std::string &msg) throw() {
	_msg = msg;
}

/**
 * @brief Convert string _msg attribute to char * and return
 * 
 * @return String msg converted to char *
*/
const char * Bureaucrat::GradeTooHighException::what() const throw() {
	return _msg.c_str();
}

Bureaucrat::GradeTooHighException::~GradeTooHighException() throw() {}


Bureaucrat::GradeTooLowException::GradeTooLowException(const std::string &msg) throw() {
	_msg = msg;
}

/**
 * @brief Convert string _msg attribute to char * and return.
 * 
 * @return String msg converted to char *
*/
const char * Bureaucrat::GradeTooLowException::what() const throw() {
	return _msg.c_str();
}

Bureaucrat::GradeTooLowException::~GradeTooLowException() throw() {}