#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() 
    : AForm("Robotomy Form", 72, 45), _target("default target") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string & target) 
    : AForm("Robotomy Form", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm & src) 
    : AForm("Robotomy Form", 72, 45), _target(src._target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm & src) {
    if (this != &src) {
        this->_target = src._target;
    }
    return *this;
}

/**
 * @brief Try to execute Form. If Form not signed or
 * Bureaucrat grade lower than Form exec grade, throw Exception.
 * 
 * @param executor Bureaucrat that will execute form. 
*/
void        RobotomyRequestForm::execute(Bureaucrat const & executor) const {
    if (!this->getIsSigned())
        throw NotSignedException("robotic form is not signed\nRobotomy failed\n");
    if (this->getExecGrade() < executor.getGrade())
        throw GradeTooLowException("bureaucrat exec grade too low\nRobotomy failed\n");
    std::cout << "Making some drilling noises....\n";
    std::cout << _target << " has been robotomized successfully 50% of the time\n";
}