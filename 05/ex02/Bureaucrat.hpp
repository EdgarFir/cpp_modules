#ifndef BUREAUCRAT_HPP

# define BUREAUCRAT_HPP

#include <iostream>

# define GRADE_MAX 1
# define GRADE_MIN 150

class Form;

class Bureaucrat {
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat();
		Bureaucrat(const std::string & name, int grade);
		Bureaucrat(const Bureaucrat & src);
		~Bureaucrat();

		Bureaucrat &operator=(const Bureaucrat & src);

		std::string getName() const;
		int			getGrade() const;

		void		upGrade(int val);
		void		downGrade(int val);
		void		signForm(Form & f);

		class GradeTooHighException : public std::exception {
			private:
				std::string _msg;
			public:
				GradeTooHighException(const std::string &msg) throw();
				virtual const char * what() const throw();
				virtual ~GradeTooHighException() throw();
		};

		class GradeTooLowException : public std::exception {
			private:
				std::string _msg;
			public:
				GradeTooLowException(const std::string &msg) throw();
				virtual const char * what() const throw();
				virtual ~GradeTooLowException() throw();
		};
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj);

#endif