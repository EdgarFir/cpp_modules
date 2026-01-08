#ifndef FORM_HPP

# define FORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>


class Form {
    private:
        const std::string   _name;
        bool                _is_signed;
        const int           _sign_grade;
        const int           _exec_grade;
    public:
        Form();
        Form(const Form &src);
        Form(const std::string &name, int _sign_grade, int _exec_grade);
        ~Form();

        Form &operator=(const Form &src);

        std::string getName() const;
        int         getSignGrade() const;
        int         getExecGrade() const;
        bool        getIsSigned() const;

        void        beSigned(const Bureaucrat &b);

        class GradeTooHighException : public std::exception {
            private:
                std::string _msg;
            public:
                GradeTooHighException(const std::string & msg) throw();
                virtual ~GradeTooHighException() throw();
                virtual const char * what() const throw();
        };

        class GradeTooLowException : public std::exception {
            private:
                std::string _msg;
            public:
                GradeTooLowException(const std::string & msg) throw();
                virtual ~GradeTooLowException() throw();
                virtual const char * what() const throw();
        };

        class AlreadySignedException : public std::exception {
            private:
                std::string _msg;
            public:
                AlreadySignedException(const std::string & msg) throw();
                virtual ~AlreadySignedException() throw();
                virtual const char * what() const throw();
        };
};

std::ostream &operator<<(std::ostream & os, const Form & obj);

#endif