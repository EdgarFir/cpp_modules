#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern & src) { static_cast<void>(src); }

Intern::~Intern() {}

Intern &Intern::operator=(const Intern & src) {
    static_cast<void>(src);
    return *this;
}

/**
 * @brief Initialize a 'name' form with target.
 * Ensure form name is valid and return it allocated.
 * 
 * @param name Name of form type.
 * @param target Target to initialize form.
 * 
 * @return New Form if name is valid, else NULL.
 */
AForm *Intern::makeForm(const std::string & name, const std::string & target) {
    AForm *form = NULL;
    
    std::string form_types[3] = {
        "robotomy request",
        "presidential pardon",
        "shrubbery creation"
    };

    AForm *(*form_creators[3])(const std::string &) = {
        &RobotomyRequestForm::createRobotomy,
        &PresidentialPardonForm::createPresidential,
        &ShrubberyCreationForm::createShrubbery
    };

    int found = -1;
    for (int i = 0; i < 3; i++) {
        if (name == form_types[i])
            found = i;
    }
    if (found == -1)
        throw AForm::CreateFormException("Error: form name doesn't exist.\n");
    
    form = form_creators[found](target);
    std::cout << "Intern creates " << form->getName() << std::endl;
    return form;
}   

