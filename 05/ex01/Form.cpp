#include "Form.hpp"

Form::Form() : _is_signed(false), _sign_grade(150), _exec_grade(150) {}

Form::Form(const std::string &name, int sign_grade, int _exec_grade) 
    : _name(name), _is_signed(false), _sign_grade(sign_grade), _exec_grade(_exec_grade) {
    if (_sign_grade < GRADE_MAX)
        throw GradeTooHighException("Error: Form sign grade too high, max: 1\n");
    if (_sign_grade > GRADE_MIN)
        throw GradeTooLowException("Error: Form sign grade too low, min: 150\n");
    if (_exec_grade < GRADE_MAX)
        throw GradeTooHighException("Error: Form sign grade too high, max: 1\n");
    if (_exec_grade > GRADE_MIN)
        throw GradeTooLowException("Error: Form sign grade too low, min: 150\n");
}

Form::Form(const Form &src) 
    : _name(src._name), _is_signed(src._is_signed), _sign_grade(src._sign_grade), _exec_grade(src._exec_grade) {
}

Form::~Form() {}

/**
 * @brief Equal operator overload. 
 * If src not equal to actual object, assign src non const atributtes.
 *
 * @param src 
 * @return Return this
 */
Form &Form::operator=(const Form &src) {
    
    if (this != &src) {
        this->_is_signed = src._is_signed;
    }
    return *this;
}

/**
 * @brief Form name getter.
 * 
 * @return Form name
 */
std::string Form::getName() const {
    return _name;
}

/**
 * @brief Form sign grade getter.
 * 
 * @return Form sign grade.
 */
int         Form::getSignGrade() const {
    return _sign_grade;
}

/**
 * @brief Form exec grade getter.
 * 
 * @return Form exec grade.
 */
int         Form::getExecGrade() const {
    return _exec_grade;
}

bool        Form::getIsSigned() const {
    return _is_signed;
}

Form::GradeTooHighException::GradeTooHighException(const std::string & msg) throw() {
    _msg = msg;
}

Form::GradeTooHighException::GradeTooHighException::~GradeTooHighException() throw() {}

/**
 * @brief Overrides std::exception 'what' method.
 * 
 * @return Exception message.
 */
const char * Form::GradeTooHighException::GradeTooHighException::what() const throw() {
    return _msg.c_str();
}

Form::GradeTooLowException::GradeTooLowException(const std::string & msg) throw() {
    _msg = msg;
}

Form::GradeTooLowException::GradeTooLowException::~GradeTooLowException() throw() {}

/**
 * @brief Overrides std::exception 'what' method.
 * 
 * @return Exception message.
 */
const char * Form::GradeTooLowException::GradeTooLowException::what() const throw() {
    return _msg.c_str();
}

Form::AlreadySignedException::AlreadySignedException(const std::string & msg) throw() {
    _msg = msg;
}

Form::AlreadySignedException::AlreadySignedException::~AlreadySignedException() throw() {}

/**
 * @brief Overrides std::exception 'what' method.
 * 
 * @return Exception message.
 */
const char * Form::AlreadySignedException::AlreadySignedException::what() const throw() {
    return _msg.c_str();
}

/**
 * @brief Ensure Bureaucrat grade is not lower than Form sign grade,
 * else throw exception.
 * 
 * @param b Bureaucrat object.
 */
void        Form::beSigned(const Bureaucrat &b) {
    if (_is_signed)
        throw AlreadySignedException("form is already signed\n");
    if (b.getGrade() > _sign_grade)
        throw GradeTooLowException("bureaucrat grade not enough to sign form\n");
    _is_signed = true;
}

/**
 * @brief Insertion operator overload.
 * 
 * @param os Ostream object.
 * @param obj Form object.
 * 
 * @return Ossteam object reference.
 */
std::ostream &operator<<(std::ostream & os, const Form & obj) {
    os << obj.getName() << ", "
       << "signed: " << obj.getSignGrade()
       << ", sign grade: " << obj.getSignGrade()
       << ", exec grade: " << obj.getExecGrade()
       << std::endl;

    return os;
}
