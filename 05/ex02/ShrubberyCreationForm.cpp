#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() 
    : AForm("Shrubbery Form", 145, 137), _target("default target") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string & target) 
    : AForm("Shrubbery Form", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm & src) 
    : AForm("Shrubbery Form", 145, 137), _target(src._target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm & src) {
    if (this != &src) {
        this->_target = src._target;
    }
    return *this;
}

/**
 * @brief Try to execute Form. If Form not signed or
 * Bureaucrat grade lower than Form exec grade, throw Exception.
 * Open file and write ASCII trees inside.
 * 
 * @param executor Bureaucrat that will execute form. 
*/
void        ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
    if (!this->getIsSigned())
        throw NotSignedException("shrubbery form is not signed\n");
    if (this->getExecGrade() < executor.getGrade())
        throw GradeTooLowException("bureaucrat exec grade too low\n");
    
    std::ofstream file((_target + "_shrubbery").c_str());
    if (!file) {
        std::cout << "Error: opening file\n";
        return ;
    }
    file << "ASCII trees\n";
    if (file.fail()) {
        std::cout << "Error: writting to file\n";
    }
}