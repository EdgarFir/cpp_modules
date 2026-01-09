#ifndef INTERN_HPP

# define INTERN_HPP

#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
    private:
    public:
        Intern();
        Intern(const Intern & src);
        ~Intern();

        Intern &operator=(const Intern & src);
        AForm * makeForm(const std::string & name, const std::string & target);
};

#endif