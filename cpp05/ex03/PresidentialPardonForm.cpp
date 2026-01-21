#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() 
    : AForm("Presidential Form", 25, 5), _target("default target") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string & target) 
    : AForm("Presidential Form", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm & src) 
    : AForm("Presidential Form", 25, 5), _target(src._target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm & src) {
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
void        PresidentialPardonForm::execute(Bureaucrat const & executor) const {
    if (!this->getIsSigned())
        throw NotSignedException("presidential form is not signed\n");
    if (this->getExecGrade() < executor.getGrade())
        throw GradeTooLowException("bureaucrat exec grade too low\n");
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox.\n";
}

/**
 * @brief Create a new allocated Presidential form.
 * 
 * @param target Name of the target.
 * 
 * @returns new PresidentialPardonForm initialized with target.
*/
AForm       *PresidentialPardonForm::createPresidential(const std::string & target) {
    return new PresidentialPardonForm(target);
}
